#pragma once
#include <numeric>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

#include "IGraph.h"

namespace Graph {

template <typename Vertix>
class Graph : public IGraph<Vertix> {
 public:
  using VerticiesPointers =IGraph<Vertix>::VerticiesPointers;
  using Verticies = IGraph<Vertix>::Verticies;
  using AdjacencyList = IGraph<Vertix>::AdjacencyList;
  using Edge = IGraph<Vertix>::Edge;
  using Edges = IGraph<Vertix>::Edges;
  using Path = std::list<Vertix>;

  Graph() = default;
  Graph(const AdjacencyList& adjacency_list);
  Graph(const Edges& edges, const Verticies& verticies = Verticies());
  size_t VerticiesCount() const;
  AdjacencyList GetAdjacencyList() const;
  void InsertEdge(const Edge& edge);
  Verticies GetConnectedVerticies(const Vertix& vertix) const;
  bool Contains(const Vertix& vertix) const;
  bool Contains(const Edge& edge) const;
  bool DeleteEdge(const Edge& edge);
  auto InsertVertix(Vertix vertix);
  // DeleteVertix(Vertix vertix);
  Path SearchBreadthFirst(Vertix target_vertix, Vertix root = NULL) const;
  bool SearchDepthFirst(Vertix target_vertix, Vertix root) const;

  ~Graph() = default;

 private:
  struct VertixWithParent {
    Vertix vertix;
    Vertix parent = vertix;

    bool operator==(const VertixWithParent& rhs) const {
      return vertix == rhs.vertix;
    }
  };

  struct VertixWithParentHasher {
    std::size_t operator()(const VertixWithParent& e) const noexcept {
      return std::hash<Vertix>{}(e.vertix);
    }
  };

  using VerticiesWithParent =
      std::unordered_set<VertixWithParent, VertixWithParentHasher,
                         std::equal_to<VertixWithParent>>;

  Path SearchBreadthFirst(const Vertix& target_vertix,
                          std::queue<Vertix>&& queue,
                          VerticiesWithParent&& visited_verticies,
                          Path&& search_path) const;
  bool SearchDepthFirst(const Vertix& target_vertix,
                        std::stack<Vertix>&& visit_stack,
                        VerticiesWithParent&& visited_verticies) const;
  AdjacencyList m_adjacency_list = AdjacencyList();
  Path GetShortestPath(VerticiesWithParent&& visited_verticies,
                       const Vertix& root, const Vertix& target) const;
};

template <typename Vertix>
Graph<Vertix>::Graph(const Edges& edges, const Verticies& verticies) {
  for (auto vertix : verticies) {
    InsertVertix(vertix);
  }

  for (auto edge : edges) {
    InsertEdge(edge);
  }
}

template <typename Vertix>
Graph<Vertix>::Graph(const AdjacencyList& adjacency_list)
    : m_adjacency_list(adjacency_list) {}

template <typename Vertix>
size_t Graph<Vertix>::VerticiesCount() const {
  return m_adjacency_list.size();
}

template <typename Vertix>
Graph<Vertix>::AdjacencyList Graph<Vertix>::GetAdjacencyList() const {
  return m_adjacency_list;
}

template <typename Vertix>
bool Graph<Vertix>::Contains(const Vertix& vertix) const {
  return m_adjacency_list.contains(vertix);
}

template <typename Vertix>
bool Graph<Vertix>::Contains(const Edge& edge) const {
  return GetConnectedVerticies(edge.vertix_1).contains(edge.vertix_2);
}

template <typename Vertix>
Graph<Vertix>::Verticies Graph<Vertix>::GetConnectedVerticies(
    const Vertix& vertix) const {
  auto connected_verticies = m_adjacency_list.find(vertix);
  if (connected_verticies == m_adjacency_list.end()) {
    return {};
  }
  return connected_verticies->second;
}

template <typename Vertix>
void Graph<Vertix>::InsertEdge(const Edge& edge) {
  InsertVertix(edge.vertix_1);
  InsertVertix(edge.vertix_2);
  m_adjacency_list[edge.vertix_1].insert(edge.vertix_2);
}

template <typename Vertix>
auto Graph<Vertix>::InsertVertix(Vertix vertix) {
  return m_adjacency_list.insert({vertix, {}});
}

template <typename Vertix>
bool Graph<Vertix>::DeleteEdge(const Edge& edge) {
  auto connected_verticies = m_adjacency_list.find(edge.vertix_1);
  if (connected_verticies == m_adjacency_list.end()) {
    return false;
  }
  return static_cast<bool>(connected_verticies->second.erase(edge.vertix_2));
}

template <typename Vertix>
Graph<Vertix>::Path Graph<Vertix>::GetShortestPath(
    VerticiesWithParent&& visited_verticies, const Vertix& root,
    const Vertix& target) const {
  auto path = Path();
  path.push_front(target);
  do {
    auto parent = visited_verticies.find({path.front()})->parent;
    path.push_front(parent);
  } while (path.front() != root);
  return path;
}

template <typename Vertix>
Graph<Vertix>::Path Graph<Vertix>::SearchBreadthFirst(
    const Vertix& target_vertix, std::queue<Vertix>&& visit_queue,
    VerticiesWithParent&& visited_verticies, Path&& search_path) const {
  // check if queue is empty
  if (visit_queue.empty()) return search_path;

  // pop and check
  auto cur_vertix = visit_queue.front();
  visit_queue.pop();
  search_path.push_back(cur_vertix);
  if (cur_vertix == target_vertix) {
    return GetShortestPath(std::move(visited_verticies), search_path.front(),
                           target_vertix);
  }
  visited_verticies.emplace(cur_vertix);

  // push non visited neighbors
  for (auto connected_vertix : m_adjacency_list.at(cur_vertix)) {
    if (visited_verticies.contains({connected_vertix})) {
      continue;
    }
    visit_queue.emplace(connected_vertix);
    // link cur_vertix with connected_vertix for shortestpath
    visited_verticies.emplace(connected_vertix, cur_vertix);
  }
  // recurse
  return SearchBreadthFirst(target_vertix, std::move(visit_queue),
                            std::move(visited_verticies),
                            std::move(search_path));
}

template <typename Vertix>
Graph<Vertix>::Path Graph<Vertix>::SearchBreadthFirst(Vertix target_vertix,
                                                      Vertix root) const {
  if (m_adjacency_list.empty()) return {};
  if (root == NULL) {
    auto max = std::max_element(
        m_adjacency_list.begin(), m_adjacency_list.end(),
        [](auto a, auto b) { return a.second.size() < b.second.size(); });
    root = max->first;
  }

  auto visit_queue = std::queue<Vertix>();
  visit_queue.emplace(root);

  return SearchBreadthFirst(target_vertix, std::move(visit_queue),
                            std::move(VerticiesWithParent()),
                            std::move(Path()));
}

template <typename Vertix>
bool Graph<Vertix>::SearchDepthFirst(
    const Vertix& target_vertix, std::stack<Vertix>&& visit_stack,
    VerticiesWithParent&& visited_verticies) const {
  if (visit_stack.empty()) {
    return false;
  }

  auto cur_vertix = visit_stack.top();
  if (cur_vertix == target_vertix) {
    return true;
  }
  visited_verticies.emplace(cur_vertix);

  for (auto connected_vertix : m_adjacency_list.at(cur_vertix)) {
    if (visited_verticies.contains({connected_vertix})) {
      continue;
    }
    visit_stack.emplace(connected_vertix);
    if (SearchDepthFirst(target_vertix, std::move(visit_stack),
                         std::move(visited_verticies))) {
      return true;
    }
  }
  if (visit_stack.empty()) {
    return false;
  }
  visit_stack.pop();
  return SearchDepthFirst(target_vertix, std::move(visit_stack),
                          std::move(visited_verticies));
}

template <typename Vertix>
bool Graph<Vertix>::SearchDepthFirst(Vertix target_vertix, Vertix root) const {
  auto visit_stack = std::stack<Vertix>();
  visit_stack.emplace(root);

  return SearchDepthFirst(target_vertix, std::move(visit_stack),
                          std::move(VerticiesWithParent()));
}
}  // namespace Graph