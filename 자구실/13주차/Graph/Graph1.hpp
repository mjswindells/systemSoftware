#ifndef __GRAPH_H__
#define __GRAPH_H__
class Graph {
  public:
    Graph(int n);
    ~Graph();
    void add_edge(int source, int target);
    void remove_edge(int source, int target);
    void print_graph();

  private:
    bool **adjMatrix;
    int size;
};
#endif
