#pragma once
#include <memory>
namespace Graph {

template <typename Vertix>
class IGraph {
 public:
  using Verticies =
      std::unordered_set<Vertix, std::hash<Vertix>, std::equal_to<Vertix>>;

  struct VertixPointerHasher {
    std::size_t operator()(const std::shared_ptr<Vertix>& e) const noexcept {
      return std::hash<Vertix>{}(*e);
    }
  };

  struct VertixPointerEqual {
    bool operator()(const std::shared_ptr<Vertix>& lhs,
                    const std::shared_ptr<Vertix>& rhs) const {
      return *lhs == *rhs;
    }
  };

  using VerticiesPointers =
      std::unordered_set<std::shared_ptr<Vertix>, VertixPointerHasher,
                         VertixPointerEqual>;

  using AdjacencyList = std::unordered_map<Vertix, Verticies>;

  struct Edge {
    Vertix vertix_1;
    Vertix vertix_2;

    bool operator==(const Edge& rhs) const {
      return vertix_1 == rhs.vertix_1 && vertix_2 == rhs.vertix_2;
    }
  };

  struct EdgeHasher {
    std::size_t operator()(const Edge& e) const noexcept {
      return std::hash<Vertix>{}(e.vertix_1) ^ std::hash<Vertix>{}(e.vertix_2);
    }
  };

  using Edges = std::unordered_set<Edge, EdgeHasher>;

  virtual size_t VerticiesCount() const = 0;
  virtual AdjacencyList GetAdjacencyList() const = 0;
  void InsertEdge(const Edge& edge);
  Verticies GetConnectedVerticies(const Vertix& vertix) const;
};
}  // namespace Graph

