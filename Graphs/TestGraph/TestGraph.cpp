#include "pch.h"
#include "Graph.h"

namespace Graph {
class custom {
 public:
  int i = 0;
  int j = 0;
  custom()=default;
  custom(const int& i, const int& j) {
    this->i = i;
    this->j = j;
  }

  bool operator==(const custom& rhs) const {
    return this->i == rhs.i;
  }
};

TEST(CreateVerticiesPointers, HasherAndEqualOperatorsWorkAsexpected) {
  auto pointers_set = IGraph<custom>::VerticiesPointers{
      std::make_shared<custom>(1,1),
      std::make_shared<custom>(2,2),
      std::make_shared<custom>(3, 3),
      std::make_shared<custom>(1,4)};
}

TEST(CreateAdjacencyList, RepeatedVerticiesReturnsFirstValuepassed) {
  auto adjacency_list =
      Graph<int>::AdjacencyList{{1, {2}}, {1, {}}, {1, {2, 3}}};
  EXPECT_EQ(adjacency_list.size(), 1);
  EXPECT_EQ(adjacency_list[1], Graph<int>::Verticies{2});
}

TEST(CreateAdjacencyList, VerticiesAndAjacentVeticiesAreSet) {
  auto adjacency_list = Graph<int>::AdjacencyList{
      {1, {2}},
      {2, {3}},
      {3, {2, 4}},  // undirected (2,3)(3,2) exists
      {4, {4}},     // Self reference
      {5, {}}       // single vertex / disconnected graphs
  };
  EXPECT_EQ(adjacency_list.size(), 5);
  EXPECT_EQ(adjacency_list[1], Graph<int>::Verticies{2});
  EXPECT_EQ(adjacency_list[2], Graph<int>::Verticies{3});
  EXPECT_EQ(adjacency_list[3], (Graph<int>::Verticies{2, 4}));
  EXPECT_EQ(adjacency_list[4], Graph<int>::Verticies{4});
  EXPECT_EQ(adjacency_list[5], Graph<int>::Verticies{});
}

TEST(CreateGraph, AddEdgesCreatesVerticies) {
  auto graph = Graph<char>(Graph<char>::Edges{{'a', 'b'}, {'b', 'c'}});
  EXPECT_EQ((graph.VerticiesCount()), 3);

  auto adjacency_list = graph.GetAdjacencyList();
  auto expected_adjacency_list =
      Graph<char>::AdjacencyList{{'a', {'b'}}, {'b', {'c'}}, {'c', {}}};
  EXPECT_EQ(adjacency_list, expected_adjacency_list);

  graph.InsertEdge(Graph<char>::Edge{'c', 'd'});
  auto connected_verticies = graph.GetConnectedVerticies('c');
  EXPECT_EQ(connected_verticies, Graph<char>::Verticies{'d'});
}

TEST(CreateGraph, InsertNewVertixSucceeds) {
  auto graph = Graph<char>({Graph<char>::Edge{'a', 'b'}});
  auto pair = graph.InsertVertix('c');
  EXPECT_TRUE(pair.second);
}

TEST(CreateGraph, InsertExistigVertixDoesNotOverwriteConnectedVerticies) {
  auto graph = Graph<char>(Graph<char>::Edges{{'a', 'b'}, {'b', 'c'}});
  auto pair = graph.InsertVertix('b');
  EXPECT_FALSE(pair.second);
}

TEST(DeleteEdge, DeleteEdgeSuccess) {
  auto graph = Graph<char>(Graph<char>::Edges{{'a', 'b'}, {'b', 'c'}});
  EXPECT_TRUE(graph.Contains({'a', 'b'}));
  EXPECT_TRUE(graph.DeleteEdge({'a', 'b'}));
  EXPECT_FALSE(graph.Contains({'a', 'b'}));
}

TEST(DeleteEdge, DeleteEdgeFail) {
  auto graph = Graph<char>(Graph<char>::Edges{{'a', 'b'}, {'b', 'c'}});
  EXPECT_FALSE(graph.DeleteEdge({'c', 'b'}));
  EXPECT_TRUE(graph.Contains({'a', 'b'}));
  EXPECT_TRUE(graph.Contains({'b', 'c'}));
}

class GraphTest : public ::testing::Test {
 protected:
  void SetUp() override {
    m_undirected_graph = Graph<char>({{'a', {'b', 'e'}},
                                {'b', {'a', 'f'}},
                                {'c', {'d', 'g', 'f'}},
                                {'d', {'c', 'g', 'h'}},
                                {'e', {'a'}},
                                {'f', {'b', 'c', 'g'}},
                                {'g', {'c', 'd', 'f', 'h'}},
                                {'h', {'d', 'g'}}});

    m_directed_graph = Graph<char>({{'a', {'b', 'c', 'g'}},
                                    {'b', {'d', 'e'}},
                                    {'c', {'d'}},
                                    {'d', {'f','e'}},
                                    {'e', {}},
                                    {'f', {'g'}},
                                    {'g', {'c'}}});
  }

  Graph<char> m_undirected_graph;
  Graph<char> m_directed_graph;
};

TEST_F(GraphTest, BredthFirstSearchFailReturnPathAllNodes) {
  auto vertix = m_undirected_graph.SearchBreadthFirst('z', 'b');
  auto expected_search_path =
      Graph<char>::Path{'b', 'a', 'f', 'e', 'c', 'g', 'd', 'h'};
  EXPECT_EQ(vertix, expected_search_path);
}

TEST_F(GraphTest, BredthFirstSearchFindsShortestPath) {
  auto shortest_path = m_undirected_graph.SearchBreadthFirst('h', 'b');
  auto expected_search_path = Graph<char>::Path{'b', 'f', 'g', 'h'};
  EXPECT_EQ(shortest_path, expected_search_path);
}

TEST_F(GraphTest, BredthFirstSearchFindsShortestPathToNodeInMiddle) {
  auto shortest_path = m_undirected_graph.SearchBreadthFirst('c', 'b');
  auto expected_search_path = Graph<char>::Path{'b', 'f', 'c'};
  EXPECT_EQ(shortest_path, expected_search_path);
}

TEST_F(GraphTest, DepthFirstSearchCannotFindPath) {
  EXPECT_FALSE(m_directed_graph.SearchDepthFirst('z', 'a'));
}

TEST_F(GraphTest, DepthFirstSearchFindsPath) {
  EXPECT_TRUE(m_directed_graph.SearchDepthFirst('e', 'a'));
}

}  // namespace Graph

// Specialize std::hash
// https://stackoverflow.com/questions/8157937/how-to-specialize-stdhashkeyoperator-for-user-defined-type-in-unordered
namespace std {
template<>
struct hash<Graph::custom> {
  std::size_t operator()(const Graph::custom& e) const noexcept {
    return std::hash<int>{}(e.i);// we chose to use i member only for hashing to test overwrite
  }
};
}  // namespace std
