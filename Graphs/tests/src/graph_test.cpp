/**
Copyright (c) <2018> <Mohab Meshref>
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the Software), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <gtest/gtest.h>
#include "Graph.h"

class TestAddEdge : public ::testing::Test
{
    public:
    const int verticesCount = 4;
    Graph m_graph  = Graph(verticesCount);
    int input;
    TestAddEdge()
    {
    }

    ~TestAddEdge()
    {
    }
};

TEST_F (TestAddEdge, AddEdgesThenPrint)
{
    m_graph.addEdge(0, 1);
    m_graph.addEdge(0, 2);
    m_graph.addEdge(1, 3);
    m_graph.addEdge(2, 3);
    m_graph.printGraph();
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc,argv);

    return RUN_ALL_TESTS();
}

