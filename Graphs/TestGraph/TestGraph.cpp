#include "pch.h"
#include "Graph.h"

namespace Graph {
    TEST(CreateAdjacencyList, RepeatedVerticiesReturnsFirstValuepassed) {
        auto adjacency_list = Graph<int>::AdjacencyList{ {1,{2}} , {1,{}}, {1,{2,3}} };
        EXPECT_EQ(adjacency_list.size(), 1);
        EXPECT_EQ(adjacency_list[1], Graph<int>::Verticies{ 2 });
        //std::vector<char> verticies = std::vector{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
        //std::pai
        //AdjacencyList adjacency_list = AdjacencyList(std::vector{})
        //Graph graph = Graph();
    }

    TEST(CreateAdjacencyList, VerticiesAndAjacentVeticiesAreSet) {
        auto adjacency_list = Graph<int>::AdjacencyList{
            {1,{2}},
            {2,{3}},
            {3,{2,4}}, // undirected (2,3)(3,2) exists
            {4,{4}},   // Self reference
            {5,{}}     // single vertex / disconnected graphs
        };
        EXPECT_EQ(adjacency_list.size(), 5);
        EXPECT_EQ(adjacency_list[1], Graph<int>::Verticies{2});
        EXPECT_EQ(adjacency_list[2], Graph<int>::Verticies{3});
        EXPECT_EQ(adjacency_list[3], (Graph<int>::Verticies{ 2,4 }));
        EXPECT_EQ(adjacency_list[4], Graph<int>::Verticies{4});
        EXPECT_EQ(adjacency_list[5], Graph<int>::Verticies{});
    }

    TEST(CreateGraph, AddEdgesCreatesVerticies) {
        auto graph = Graph<char>({ Graph<char>::Edge{'a', 'b'},
            Graph<char>::Edge{'b', 'c'} });
        EXPECT_EQ((graph.VerticiesCount()), 3);

        auto adjacency_list = graph.GetAdjacencyList();
        auto expected_adjacency_list = Graph<char>::AdjacencyList{
            {'a', {'b'}},
            {'b', {'c'}},
            {'c', {}}
        };
        EXPECT_EQ(adjacency_list, expected_adjacency_list);

        graph.InsertEdge(Graph<char>::Edge{ 'c', 'd' });
        auto connected_verticies = graph.GetConnectedVerticies('c');
        EXPECT_EQ(connected_verticies, Graph<char>::Verticies{'d'});
    }

    TEST(CreateGraph, InsertNewVertixSucceeds) {
        auto graph = Graph<char>({ Graph<char>::Edge{'a', 'b'} });
        auto pair = graph.InsertVertix('c');
        EXPECT_TRUE(pair.second);
    }

    TEST(CreateGraph, InsertExistigVertixDoesNotOverwriteConnectedVerticies) {
        auto graph = Graph<char>({ Graph<char>::Edge{'a', 'b'},
            Graph<char>::Edge{'b', 'c'} });
        auto pair = graph.InsertVertix('b');
        EXPECT_FALSE(pair.second);
    }

    TEST(DeleteEdge, DeleteEdgeSuccess) {
        auto graph = Graph<char>({ Graph<char>::Edge{'a', 'b'},
            Graph<char>::Edge{'b', 'c'} });
        EXPECT_TRUE(graph.DeleteEdge({ 'a' , 'b' }));
        auto verticies =  graph.GetConnectedVerticies('b');
        EXPECT_EQ(verticies.size(), 1);
    }

    TEST(DeleteEdge, DeleteEdgeFail) {
        auto graph = Graph<char>({ Graph<char>::Edge{'a', 'b'},
            Graph<char>::Edge{'b', 'c'} });
        EXPECT_FALSE(graph.DeleteEdge({ 'c' , 'b' }));
        auto verticies = graph.GetConnectedVerticies('b');
        EXPECT_EQ(verticies.size(), 1);
    }

}