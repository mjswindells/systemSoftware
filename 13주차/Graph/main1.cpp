#include "Graph1.hpp"
#include <iostream>
using namespace std;
int main() {
    Graph g(4);
    g.add_edge(0, 3);
    g.add_edge(0, 1);
    g.add_edge(1, 3);
    g.add_edge(1, 2);
    g.add_edge(1, 0);
    g.add_edge(2, 3);
    g.add_edge(2, 1);
    g.add_edge(3, 2);
    g.add_edge(3, 1);
    g.add_edge(3, 0);
    cout << "--- Adjacency Matrix ---" << endl;
    g.print_graph();
    return 0;
}
