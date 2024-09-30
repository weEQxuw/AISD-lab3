#include <iostream>
#include <graph.h>

using namespace std;
using namespace graph;

int main() {
	setlocale(LC_ALL, "Rus");
	/*
	Graph<int> a;
	a.add_vertex(1);
	a.add_vertex(2);
	a.add_vertex(3);
	a.add_vertex(4);
	a.add_vertex(5);
	a.add_vertex(6);
	a.add_vertex(7);
	a.add_vertex(8);
	a.add_vertex(9);
	a.add_edge(1, 2, 2);
	a.add_edge(1, 3, 6);
	a.add_edge(1, 4, 8);
	a.add_edge(1, 7, 3);
	a.add_edge(2, 3, 9);
	a.add_edge(2, 4, 3);
	a.add_edge(2, 6, 4);
	a.add_edge(2, 7, 9);
	a.add_edge(3, 4, 7);
	a.add_edge(4, 5, 5);
	a.add_edge(4, 6, 5);
	a.add_edge(5, 7, 8);
	a.add_edge(5, 8, 9);
	a.add_edge(6, 8, 2);
	a.add_edge(6, 9, 4);
	a.add_edge(8, 9, 1);


	a.print() << endl << endl;
	cout << a.has_vertex(3) << " " << "Есть ли вершина 3" << endl;
	cout << a.has_edge(4, 5, 6) << " " << "Есть ли связь между 4-5 " << endl;
	a.remove_edge(1, 4, 8);

	vector<pair<int, double>> b = a.shortest_path(1, 9);
	for (auto& vec : b) {
		cout << vec.first << " " << vec.second << endl;
	}*/
	
	Graph<int> a;
	a.add_vertex(1);
	a.add_vertex(2);
	a.add_vertex(3);
	a.add_vertex(4);
	a.add_vertex(5);

	a.add_edge(1, 2, 7);
	a.add_edge(1, 4, 5);
	a.add_edge(1, 5, 3);
	a.add_edge(2, 1, 7);
	a.add_edge(2, 3, 3);
	a.add_edge(3, 2, 3);
	a.add_edge(3, 4, 2);
	a.add_edge(3, 5, 20);
	a.add_edge(4, 1, 5);
	a.add_edge(4, 3, 2);
	a.add_edge(5, 3, 20);
	a.add_edge(5, 1, 3);

	cout << "Самый дальний травмпункт:"<< a.task();
	
	return 0;
}