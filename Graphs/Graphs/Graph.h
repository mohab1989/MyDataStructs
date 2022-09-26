#pragma once
#include <unordered_set>
#include <unordered_map>
namespace Graph {

	template <typename Vertix>
	class Graph
	{
	public:
		struct Edge
		{
			Vertix vertix_1;
			Vertix vertix_2;

			bool operator==(const Edge& rhs) const {
				return vertix_1 == rhs.vertix_1 && vertix_2 == rhs.vertix_2;
			}
		};

		struct EdgeHasher
		{
			std::size_t operator()(const Edge& e) const noexcept
			{
				return std::hash<Vertix>{}(e.vertix_1) ^ std::hash<Vertix>{}(e.vertix_2);
			}
		};
		
		using Edges = std::unordered_set<Edge, EdgeHasher>;
		using Verticies = std::unordered_set<Vertix,std::hash<Vertix>,std::equal_to<Vertix>>;
		using AdjacencyList = std::unordered_map<Vertix, Verticies>;

		Graph()=default;
		Graph(const Edges& edges, const Verticies& verticies = Verticies());
		int VerticiesCount() const;
		AdjacencyList GetAdjacencyList() const;
		void InsertEdge(const Edge& edge);
		Verticies GetConnectedVerticies(const Vertix& vertix) const;
		bool Contains(const Vertix& vertix) const;
		bool Contains(const Edge& edge) const;
		bool DeleteEdge(const Edge& edge);
		auto InsertVertix(Vertix vertix);
		//DeleteVertix(Vertix vertix);
		//SearchBreadthFirst(Vertix vertix);
		//SearchDepthFirst(Vertix vertix);

		~Graph()=default;

	private:
		AdjacencyList m_adjacency_list = AdjacencyList();
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
	int Graph<Vertix>::VerticiesCount() const {
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
	Graph<Vertix>::Verticies Graph<Vertix>::GetConnectedVerticies(const Vertix& vertix) const {
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
		return m_adjacency_list.insert({ vertix , {}});
	}

	template <typename Vertix>
	bool Graph<Vertix>::DeleteEdge(const Edge& edge) {
		auto connected_verticies = m_adjacency_list.find(edge.vertix_1);
		if (connected_verticies == m_adjacency_list.end()) {
			return false;
		}
		return static_cast<bool>(connected_verticies->second.erase(edge.vertix_2));
	}
}