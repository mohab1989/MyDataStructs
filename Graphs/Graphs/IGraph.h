#pragma once
#include <memory>
namespace Graph {

template <typename Vertex>
class IGraph {
 public:
  using Verticies =
      std::unordered_set<Vertex, std::hash<Vertex>, std::equal_to<Vertex>>;

  struct VertexPointerHasher {
    std::size_t operator()(const std::shared_ptr<Vertex>& e) const noexcept {
      return std::hash<Vertex>{}(*e);
    }
  };

  struct VertexPointerEqual {
    bool operator()(const std::shared_ptr<Vertex>& lhs,
                    const std::shared_ptr<Vertex>& rhs) const {
      if (*lhs == *rhs) {
        throw std::runtime_error("Value already exists in set.");
      }
      return false;
    }
  };

  using VerticiesPointers =
      std::unordered_set<std::shared_ptr<Vertex>, VertexPointerHasher,
                         VertexPointerEqual>;

  using AdjacencyList = std::unordered_map<Vertex, Verticies>;

  struct Edge {
    Vertex vertix_1;
    Vertex vertix_2;

    bool operator==(const Edge& rhs) const {
      return vertix_1 == rhs.vertix_1 && vertix_2 == rhs.vertix_2;
    }
  };

  struct EdgeHasher {
    std::size_t operator()(const Edge& e) const noexcept {
      return std::hash<Vertex>{}(e.vertix_1) ^ std::hash<Vertex>{}(e.vertix_2);
    }
  };

  using Edges = std::unordered_set<Edge, EdgeHasher>;

  virtual size_t VerticiesCount() const = 0;
  virtual AdjacencyList GetAdjacencyList() const = 0;
  void InsertEdge(const Edge& edge);
  Verticies GetConnectedVerticies(const Vertex& vertix) const;
  //IGraph(const Verticies&);

  protected:
  Verticies verticies_ = {};
};
//template <typename Vertex>
//IGraph<Vertex>::IGraph(const Verticies& vertecies) {
//  verticies_ = vertecies;
//}

}  // namespace Graph

