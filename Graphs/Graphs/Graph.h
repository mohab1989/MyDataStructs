#pragma once
#include <numeric>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

#include "IGraph.h"

namespace Graph {

template <typename Vertex>
class Graph : public IGraph<Vertex> {
 public:
  using VerticiesPointers =IGraph<Vertex>::VerticiesPointers;
  using Verticies = IGraph<Vertex>::Verticies;
  using AdjacencyList = IGraph<Vertex>::AdjacencyList;
  using Edge = IGraph<Vertex>::Edge;
  using Edges = IGraph<Vertex>::Edges;
  using Path = std::list<Vertex>;

  Graph() = default;
  Graph(const AdjacencyList& adjacency_list);
  Graph(const Edges& edges, const Verticies& verticies = Verticies());
  size_t VerticiesCount() const;
  AdjacencyList GetAdjacencyList() const;
  void InsertEdge(const Edge& edge);
  Verticies GetConnectedVerticies(const Vertex& vertix) const;
  bool Contains(const Vertex& vertix) const;
  bool Contains(const Edge& edge) const;
  bool DeleteEdge(const Edge& edge);
  auto InsertVertex(Vertex vertix);
  // DeleteVertex(Vertex vertix);
  Path SearchBreadthFirst(Vertex target_vertix, Vertex root = NULL) const;
  bool SearchDepthFirst(Vertex target_vertix, Vertex root) const;

  ~Graph() = default;

 private:
  struct VertexWithParent {
    Vertex vertix;
    Vertex parent = vertix;

    bool operator==(const VertexWithParent& rhs) const {
      return vertix == rhs.vertix;
    }
  };

  struct VertexWithParentHasher {
    std::size_t operator()(const VertexWithParent& e) const noexcept {
      return std::hash<Vertex>{}(e.vertix);
    }
  };

  using VerticiesWithParent =
      std::unordered_set<VertexWithParent, VertexWithParentHasher,
                         std::equal_to<VertexWithParent>>;

  Path SearchBreadthFirst(const Vertex& target_vertix,
                          std::queue<Vertex>&& queue,
                          VerticiesWithParent&& visited_verticies,
                          Path&& search_path) const;
  bool SearchDepthFirst(const Vertex& target_vertix,
                        std::stack<Vertex>&& visit_stack,
                        VerticiesWithParent&& visited_verticies) const;
  AdjacencyList m_adjacency_list = AdjacencyList();
  Path GetShortestPath(VerticiesWithParent&& visited_verticies,
                       const Vertex& root, const Vertex& target) const;
};

template <typename Vertex>
Graph<Vertex>::Graph(const Edges& edges, const Verticies& verticies) {
  for (auto vertix : verticies) {
    InsertVertex(vertix);
  }

  for (auto edge : edges) {
    InsertEdge(edge);
  }
}

template <typename Vertex>
Graph<Vertex>::Graph(const AdjacencyList& adjacency_list)
    : m_adjacency_list(adjacency_list) {}

template <typename Vertex>
size_t Graph<Vertex>::VerticiesCount() const {
  return m_adjacency_list.size();
}

template <typename Vertex>
Graph<Vertex>::AdjacencyList Graph<Vertex>::GetAdjacencyList() const {
  return m_adjacency_list;
}

template <typename Vertex>
bool Graph<Vertex>::Contains(const Vertex& vertix) const {
  return m_adjacency_list.contains(vertix);
}

template <typename Vertex>
bool Graph<Vertex>::Contains(const Edge& edge) const {
  return GetConnectedVerticies(edge.vertix_1).contains(edge.vertix_2);
}

template <typename Vertex>
Graph<Vertex>::Verticies Graph<Vertex>::GetConnectedVerticies(
    const Vertex& vertix) const {
  auto connected_verticies = m_adjacency_list.find(vertix);
  if (connected_verticies == m_adjacency_list.end()) {
    return {};
  }
  return connected_verticies->second;
}

template <typename Vertex>
void Graph<Vertex>::InsertEdge(const Edge& edge) {
  InsertVertex(edge.vertix_1);
  InsertVertex(edge.vertix_2);
  m_adjacency_list[edge.vertix_1].insert(edge.vertix_2);
}

template <typename Vertex>
auto Graph<Vertex>::InsertVertex(Vertex vertix) {
  return m_adjacency_list.insert({vertix, {}});
}

template <typename Vertex>
bool Graph<Vertex>::DeleteEdge(const Edge& edge) {
  auto connected_verticies = m_adjacency_list.find(edge.vertix_1);
  if (connected_verticies == m_adjacency_list.end()) {
    return false;
  }
  return static_cast<bool>(connected_verticies->second.erase(edge.vertix_2));
}

template <typename Vertex>
Graph<Vertex>::Path Graph<Vertex>::GetShortestPath(
    VerticiesWithParent&& visited_verticies, const Vertex& root,
    const Vertex& target) const {
  auto path = Path();
  path.push_front(target);
  do {
    auto parent = visited_verticies.find({path.front()})->parent;
    path.push_front(parent);
  } while (path.front() != root);
  return path;
}

template <typename Vertex>
Graph<Vertex>::Path Graph<Vertex>::SearchBreadthFirst(
    const Vertex& target_vertix, std::queue<Vertex>&& visit_queue,
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

template <typename Vertex>
Graph<Vertex>::Path Graph<Vertex>::SearchBreadthFirst(Vertex target_vertix,
                                                      Vertex root) const {
  if (m_adjacency_list.empty()) return {};
  if (root == NULL) {
    auto max = std::max_element(
        m_adjacency_list.begin(), m_adjacency_list.end(),
        [](auto a, auto b) { return a.second.size() < b.second.size(); });
    root = max->first;
  }

  auto visit_queue = std::queue<Vertex>();
  visit_queue.emplace(root);

  return SearchBreadthFirst(target_vertix, std::move(visit_queue),
                            std::move(VerticiesWithParent()),
                            std::move(Path()));
}

template <typename Vertex>
bool Graph<Vertex>::SearchDepthFirst(
    const Vertex& target_vertix, std::stack<Vertex>&& visit_stack,
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

template <typename Vertex>
bool Graph<Vertex>::SearchDepthFirst(Vertex target_vertix, Vertex root) const {
  auto visit_stack = std::stack<Vertex>();
  visit_stack.emplace(root);

  return SearchDepthFirst(target_vertix, std::move(visit_stack),
                          std::move(VerticiesWithParent()));
}
}  // namespace Graph