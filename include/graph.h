#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>


using namespace std;

namespace graph {
	template <typename Vertex, typename Distance = double>
	class Graph {

		std::unordered_map <Vertex, std::vector<std::pair<Vertex, Distance>>> table;

	public:

		bool has_vertex(const Vertex& v) const {
			if (table.find(v) == table.end()) {
				return false;
			}
			return true;
		}

		void add_vertex(const Vertex& v) {
			table[v] = vector<pair<Vertex, Distance>>();
		}

		bool remove_vertex(const Vertex& v) {
			if (has_vertex(v)) {
				for (auto& ver : table) {
					for (auto it = ver.second.begin(); it != ver.second.end(); it++) {
						if (it->first == v) {
							ver.second.erase(it);
							break;
						}
					}
				}
				table.erase(v);
				return true;
			}
			return false;
		}

		vector<Vertex> vertices() const {
			vector<Vertex> result;
			for (const auto& ver : table) {
				result.push_back(ver.first);
			}
			return result;
		}

		void add_edge(const Vertex& v_from, const Vertex& v_to, const Distance& d) {
			if (!has_vertex(v_to)) {
				add_vertex(v_to);
			}
			table[v_from].push_back(make_pair(v_to, d));
		}

		bool has_edge(const Vertex& v_from, const Vertex& v_to) const {
			for (const auto& ver : table.at(v_from)) {
				if (ver.first == v_to)
					return true;
			}
			return false;
		}

		bool has_edge(const Vertex& v_from, const Vertex& v_to, const Distance& d) const {
			for (const auto& ver : table.at(v_from)) {
				if (ver.first == v_to && ver.second == d)
					return true;
			}
			return false;
		}

		bool remove_edge(const Vertex& from, const Vertex& to, const Distance& d) {
			if (has_edge(from, to)) {
				table[from].erase(remove(table[from].begin(), table[from].end(), make_pair(to, d)));
				return true;
			}
			return false;
		}

		bool remove_edge(const Vertex& from, const Vertex& to) {
			for (auto it = table[from].begin(); it != table[from].end(); it++) {
				if (it->first == to) {
					table[from].erase(it);
					return true;
				}
			}
			return false;
		}

		const vector<pair<Vertex, Distance>>& edges(const Vertex& vertex) const {
			return table.at(vertex);
		}

		ostream& print(ostream& os = std::cout) {
			for (auto& ver : table) {
				os << ver.first << " : ";
				for (auto edge : ver.second) {
					os << edge.first << " ";
				}
				os << endl;
			}
			return os;
		}

		size_t order() const {
			return table.size();
		}

		size_t degree(const Vertex& v) const {
			int sum = 0;
			for (auto [vertex, edges] : table) {
				for (auto p : edges) {
					if (vertex == v || p.first == v) {
						sum++;
					}
				}
			}
			return sum;
		}

		std::vector<pair<Vertex, Distance>> shortest_path(const Vertex& from, const Vertex& to) const {
			std::vector<pair<Vertex, Distance>> path;
			std::unordered_map<Vertex, Distance> distances;
			if (!has_vertex(from) || !has_vertex(to)) {
				return path;
			}
			for (const auto& vertex : table) {
				distances[vertex.first] = std::numeric_limits<Distance>::max();
			}
			distances[from] = 0;

			for (const auto& [vertex, edges] : table) {
				for (const auto& [to_ver, distance] : edges) {
					if (distances[vertex] + distance < distances[to_ver]) {
						distances[to_ver] = distances[vertex] + distance;
					}
				}
			}

			if (distances[to] != std::numeric_limits<Distance>::max()) {
				Vertex current = to;
				path.emplace_back(to, 0);
				while (current != from) {
					for (const auto& [vertex, edges] : table) {
						for (const auto& [neighbor, distance] : edges) {
							if (current == neighbor && distances[vertex] + distance == distances[current]) {
								path.emplace_back(vertex, distance);
								current = vertex;
								break;
							}
						}
					}
				}
			}

			reverse(path.begin(), path.end());
			return path;
		}

		void walk(const Vertex& start_vertex) const {
			unordered_set<Vertex> visited;
			stack<Vertex> st;
			st.push(start_vertex);
			while (!st.empty()) {
				auto cur = st.top();
				st.pop();
				if (visited.count(cur) > 0) {
					continue;
				}
				visited.insert(cur);
				cout << cur << endl;
				for (const auto& ver : table.at(cur)) {
					if (visited.count(ver.first) == 0) {
						st.push(ver.first);
					}
				}
			}
		}

		Vertex task() {
			Vertex remotest_vertex;
			double max_average_distance = -1;

			for (const auto& [vertex, edges] : table) {
				if (edges.empty()) {
					continue;
				}

				double total_distance = 0;
				for (const auto& vec : edges) {
					total_distance += vec.second;
				}

				double average_distance = total_distance / edges.size();

				if (average_distance > max_average_distance) {
					max_average_distance = average_distance;
					remotest_vertex = vertex;
				}
			}

			return remotest_vertex;
		}

	};
}