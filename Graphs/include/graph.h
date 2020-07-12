#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

class Graph
{
private:
//Total number of vertices
	int m_verticesCount = 0;
	//definining an array which can hold multiple LinkedLists equal to the number of vertices in the graph
	std::vector<std::list<int>> m_linkedLists;
public:

	Graph(int verticesCount)
		: m_verticesCount(verticesCount)
	{
		//Creating a new LinkedList for each vertex/index of the array
		m_linkedLists.resize(verticesCount);
	}

	void printGraph() {
		for (auto sourceVertex = 0; sourceVertex < m_linkedLists.size(); ++sourceVertex) {
			std::cout << "|" << sourceVertex << "| => ";
			const auto& list = m_linkedLists.at(sourceVertex);
			for (const auto& destinationVertex : list) {
				std::cout << "[" << destinationVertex << "] -> ";
			}
			std::cout << "NULL" << std::endl;
		}

	}

	void addEdge(int source, int destination) {
		auto& list = m_linkedLists.at(source);
		list.insert(list.end(), destination);
	}
};