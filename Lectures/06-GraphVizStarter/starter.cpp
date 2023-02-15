/**
 * This code defines a Graph class with a constructor that takes
 * the number of vertices V and initializes an empty adjacency
 * list for each vertex. The addEdge function adds an undirected
 * edge between two vertices. The printGraph function prints out
 * the adjacency list for each vertex, showing the nodes that are
 * connected to it. The main function creates a new Graph object
 * with 5 vertices, adds several edges between them, and then prints
 * out the graph.
 */

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Edge {
protected:
  map<string, string> att;

public:
  Edge() {
    att["color"] = "black";
    att["arrow_type"] = "vee";
  }
  string print() {
    return "[color=" + att["color"] + ",arrow_type=" + att["arrow_type"] + "]";
  }
  void updateAttribute(string key, string val) { att[key] = val; }

  void updateAttribute(map<string, string> atts) {
    for (auto const &x : att) {
      std::cout << x.first         // string (key)
                << ':' << x.second // string's value
                << std::endl;
      att[x.first] = x.second;
    }
  }
  friend ostream &operator<<(ostream &os, Edge &e) { return os << e.print(); }
};

struct Node {
  string color;
  string shape;
  Node() {
    color = "black";
    shape = "box";
  }
};

class Graph {
protected:
  int V;                   // number of vertices
  bool directed;           // id graph directed or undirected
  vector<vector<int>> adj; // adjacency list

  void checkResize(int v) {
    if (v >= this->V - 1) {
      adj.resize(v + 1);
      this->V = v + 1;
    }
  }

public:
  // Default constructor
  // Params:
  //    bool directed : is graph directed or not
  Graph(bool directed = true) {
    this->V = 0;
    this->directed = directed;
  }

  // Overloaded constructor
  // Params:
  //   int V : number of nodes to be in graph
  //   bool directed : is graph directed or not
  Graph(int V, bool directed = true) {
    this->V = V;
    adj.resize(V);
    this->directed = directed;
  }

  virtual void addEdge(int v, int w) {
    checkResize(v);
    checkResize(w);

    // add connection from v to w
    adj[v].push_back(w);

    // if undirected, we add an edge
    // gong from w to v as well.
    if (!directed) {
      adj[w].push_back(v);
    }
  }

  virtual void printGraph() {
    for (int v = 0; v < V; v++) {
      cout << "Node " << v << " is connected to: ";
      for (auto i : adj[v]) {
        cout << i << " "
             << " ";
      }

      cout << endl;
    }
  }
};

class GraphViz : public Graph {
  map<string, Edge *> edges; // container of edge types
  // Creates a string id se we can look up edges
  // in our graph class.
  string makeEid(int v, int w) { return to_string(v) + "-" + to_string(w); }

public:
  GraphViz() {}
  GraphViz(int V) : Graph(V) {}
  void addEdge(int v, int w) {
    checkResize(v);
    checkResize(w);

    // add connection from v to w
    adj[v].push_back(w);

    // if undirected, we add an edge
    // gong from w to v as well.
    if (!directed) {
      adj[w].push_back(v);
    }

    // add an edge type for graphviz
    edges[makeEid(v, w)] = new Edge();
  }
  void printGraph() {
    for (int v = 0; v < V; v++) {
      cout << "Node " << v << " is connected to: ";
      for (auto i : adj[v]) {
        cout << i << " " << *edges[makeEid(v, i)] << " ";
      }

      cout << endl;
    }
  }
  void editEdge(int from, int to, string key, string val) {
    editEdge(makeEid(from, to), key, val);
  }
  void editEdge(string eid, string key, string val) {
    edges[eid]->updateAttribute(key, val);
  }
};

int main() {
  GraphViz g;
  g.addEdge(0, 1);
  g.addEdge(0, 4);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);
  g.addEdge(2, 3);
  g.addEdge(3, 4);
  g.addEdge(9, 10);
  g.addEdge(4, 9);
  g.editEdge(4, 9, "color", "red");
  g.editEdge(4, 9, "arrow_type", "block");
  g.printGraph();
  return 0;
}