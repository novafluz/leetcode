// Graph Implementation Template
// Based on concepts from 07_graphs.pdf
// Instructions: Implement the missing function definitions for each class.
// Each function has comments indicating what it should do.

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>

//-------------------- GRAPH BASE CLASS --------------------
class Graph {
protected:
  int numVertices;
  bool directed;

public:
  // Constructor
  Graph(int vertices, bool isDirected = false)
      : numVertices(vertices), directed(isDirected) {}

  // Virtual destructor for proper inheritance
  virtual ~Graph() {}

  // Check if graph is directed
  bool isDirected() const { return directed; }

  // Get number of vertices
  int getNumVertices() const { return numVertices; }

  // Pure virtual functions - to be implemented by derived classes
  // source, dest is row, col respectively.
  virtual void addEdge(int source, int destination) = 0;
  virtual bool hasEdge(int source, int destination) const = 0;
  virtual std::vector<int> getNeighbors(int vertex) const = 0;
  virtual void printGraph() const = 0;
};

//-------------------- ADJACENCY MATRIX IMPLEMENTATION --------------------
class AdjacencyMatrixGraph : public Graph {
private:
  std::vector<std::vector<bool>> matrix;

public:
  // Constructor: Initialize matrix with given size
  AdjacencyMatrixGraph(int vertices, bool isDirected = false)
      : Graph(vertices, isDirected) { // call constructor of parent class
    // TODO: Initialize the adjacency matrix
    // Hint: Create a numVertices x numVertices matrix initialized with false
    for (int i = 0; i < numVertices; i++) {
      matrix.push_back(std::vector<bool>(numVertices, false));
    }
  }

  // Add an edge from source to destination
  void addEdge(int source, int destination) override {
    // TODO: Add an edge from source to destination
    // If the graph is undirected, also add an edge from destination to source
    // Validate that source and destination are within bounds
    if (source >= 0 && source < numVertices && destination >= 0 &&
        destination < numVertices) {
      matrix[source][destination] = true;
      if (!isDirected()) {
        matrix[destination][source] = true;
      }
    }
  }

  // Check if there is an edge from source to destination
  bool hasEdge(int source, int destination) const override {
    // TODO: Check if there is an edge from source to destination
    // Return false if source or destination is out of bounds
    if (source >= 0 && source < numVertices && destination >= 0 &&
        destination < numVertices) {
      return matrix[source][destination];
    }
    return false;
  }

  // Get all neighbors (vertices connected by an edge) of a vertex
  std::vector<int> getNeighbors(int vertex) const override {
    // TODO: Return a vector containing all vertices that are adjacent to the
    // given vertex Return empty vector if vertex is out of bounds
    std::vector<int> neighbors;
    if (vertex >= 0 && vertex < numVertices) {
      for (int i{0}; i < numVertices; i++) {
        if (matrix[vertex][i]) {
          neighbors.push_back(i);
        }
      }
    }
    return neighbors;
  }

  // Print the adjacency matrix
  void printGraph() const override {
    // TODO: Print the adjacency matrix in a readable format
    // Example:
    //   0 1 2 3
    // 0 0 1 0 0
    // 1 1 0 1 0
    // 2 0 1 0 1
    // 3 0 0 1 0
    std::cout << "  ";
    for (int i{0}; i < numVertices; i++) {
      std::cout << i;
      if (i < numVertices - 1)
        std::cout << " ";
    }
    std::cout << "\n";
    for (int i{0}; i < numVertices; i++) {
      std::cout << i;
      for (int j{0}; j < numVertices; j++) {
        if (j < numVertices)
          std::cout << " ";
        std::cout << (matrix[i][j] ? 1 : 0);
      }
      std::cout << "\n";
    }
  }
};

//-------------------- ADJACENCY LIST IMPLEMENTATION --------------------
class AdjacencyListGraph : public Graph {
private:
  std::vector<std::vector<int>> adjacencyList;

public:
  // Constructor: Initialize adjacency list with given size
  AdjacencyListGraph(int vertices, bool isDirected = false)
      : Graph(vertices, isDirected) {
    // TODO: Initialize the adjacency list
    // Hint: Create a vector of vectors with size numVertices
    adjacencyList.resize(numVertices);
  }

  // Add an edge from source to destination
  void addEdge(int source, int destination) override {
    // TODO: Add an edge from source to destination
    // If the graph is undirected, also add an edge from destination to source
    // Validate that source and destination are within bounds
    // Check if the edge already exists
    // Check if the reverse edge already exists
    if (source >= 0 && source < numVertices && destination >= 0 &&
        destination < numVertices) {
      adjacencyList[source].push_back(destination);
      if (!directed)
        adjacencyList[destination].push_back(source);
    }
  }

  // Check if there is an edge from source to destination
  bool hasEdge(int source, int destination) const override {
    // TODO: Check if there is an edge from source to destination
    // This requires searching through the adjacency list
    // Return false if source or destination is out of bounds
    if (source >= 0 && source < numVertices && destination >= 0 &&
        destination < numVertices) {
      for (int neighbor : adjacencyList[source]) {
        if (neighbor == destination)
          return true;
      }
    }
    return false;
  }

  // Get all neighbors (vertices connected by an edge) of a vertex
  std::vector<int> getNeighbors(int vertex) const override {
    // TODO: Return a vector containing all vertices that are adjacent to the
    // given vertex For adjacency list, this is simply the list at index
    // 'vertex' Return empty vector if vertex is out of bounds
    if (vertex >= 0 && vertex < numVertices) {
      return adjacencyList[vertex];
    }
    return {};
  }

  // Print the adjacency list
  void printGraph() const override {
    // TODO: Print the adjacency list in a readable format
    // Example:
    // 0 -> 1
    // 1 -> 0 -> 2
    // 2 -> 1 -> 3
    // 3 -> 2
    for (int i{0}; i < numVertices; i++) {
      std::cout << i;
      for (int neighbor : adjacencyList[i]) {
        std::cout << " -> " << neighbor;
      }
      std::cout << "\n";
    }
  }
};

//-------------------- GRAPH TRAVERSAL ALGORITHMS --------------------
class GraphAlgorithms {
public:
  // Depth-First Search (DFS) implementation
  static void DFS(const Graph &graph, int startVertex,
                  std::vector<bool> &visited) {
    // TODO: Implement DFS
    // 1. Mark startVertex as visited
    // 2. For each unvisited neighbor of startVertex, recursively call DFS
    visited[startVertex] = true;
    std::cout << startVertex << " ";
    for (int neighbor : graph.getNeighbors(startVertex)) {
      if (!visited[neighbor]) {
        DFS(graph, neighbor, visited);
      }
    }

    // Hint: Use the following structure
  }

  // Iterative DFS using a stack
  static void DFSIterative(const Graph &graph, int startVertex) {
    // TODO: Implement iterative DFS using a stack
    // 1. Create a stack and push startVertex
    // 2. Create a visited array initialized to false
    // 3. While stack is not empty:
    //    a. Pop a vertex from stack
    //    b. If not visited, mark as visited and process it
    //    c. Push all unvisited neighbors to stack
    std::stack<int> st;
    std::vector<bool> visited(graph.getNumVertices(), false);
    st.push(startVertex);
    while (!st.empty()) {
      int vertex = st.top();
      st.pop();
      if (!visited[vertex]) {
        visited[vertex] = true;
        std::cout << vertex << " ";
        std::vector<int> neighbors = graph.getNeighbors(vertex);
        for (int i = neighbors.size() - 1; i >= 0; i--) {
          st.push(neighbors[i]);
        }
      }
    }
  }

  // Breadth-First Search (BFS) implementation
  static void BFS(const Graph &graph, int startVertex) {
    // TODO: Implement BFS
    // 1. Create a queue and enqueue startVertex
    // 2. Create a visited array initialized to false
    // 3. Mark startVertex as visited
    // 4. While queue is not empty:
    //    a. Dequeue a vertex
    //    b. Process it
    //    c. Enqueue all unvisited neighbors and mark them as visited
    std::queue<int> q;
    std::vector<bool> visited(graph.getNumVertices(), false);
    q.push(startVertex);
    visited[startVertex] = true;
    while (!q.empty()) {
      int vertex = q.front();
      q.pop();

      std::cout << vertex << " ";
      for (int neighbor : graph.getNeighbors(vertex)) {
        if (!visited[neighbor]) {
          visited[neighbor] = true;
          q.push(neighbor);
        }
      }
    }
  }

  // Find connected components in an undirected graph
  static int findConnectedComponents(const Graph &graph) {
    // TODO: Implement connected components finder
    // 1. Initialize all vertices as unvisited
    // 2. For each unvisited vertex, run DFS and count it as a new component
    // 3. Return the total count of components
    std::vector<bool> visited(graph.getNumVertices(), false);
    int cnt = 0;
    for (int i{0}; i < graph.getNumVertices(); i++) {
      if (!visited[i]) {
        DFS(graph, i, visited);
        cnt++;
      }
    }
    return cnt;
  }

  // Check if a graph is bipartite
  static bool isBipartite(const Graph &graph) {
    // TODO: Implement bipartite check using BFS
    // 1. Initialize all vertices with no color (-1)
    // 2. Start BFS from any vertex, coloring it with 0
    // 3. For each neighbor, color it with the opposite color (1-color)
    // 4. If any adjacent vertices have the same color, return false
    // 5. If all vertices can be colored without conflicts, return true
    std::vector<int> color(graph.getNumVertices(), -1);
    for (int i{0}; i < graph.getNumVertices(); i++) {
      if (color[i] == -1) {
        std::queue<int> q;
        q.push(i);
        color[i] = 0;
        while (!q.empty()) {
          int u = q.front();
          q.pop();
          for (int v : graph.getNeighbors(u)) {
            if (color[v] == -1) {
              color[v] = 1 - color[u];
              q.push(v);
            } else if (color[v] == color[u]) {
              return false;
            }
          }
        }
      }
    }
    return true;
  }

  // Find shortest path between two vertices (unweighted graph)
  static std::vector<int> findShortestPath(const Graph &graph, int startVertex,
                                           int endVertex) {
    // TODO: Implement shortest path finder using BFS
    // 1. Run BFS from startVertex
    // 2. Keep track of parent/previous vertex for each visited vertex
    // 3. Once endVertex is reached, reconstruct the path by following parents
    // backwards
    // 4. Return the path (or empty vector if no path exists)
    std::queue<int> q;
    std::vector<int> parent(graph.getNumVertices(), -1);
    std::vector<bool> visited(graph.getNumVertices(), false);
    q.push(startVertex);
    visited[startVertex] = true;
    // setup the path, BFS warrants shortest path.
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (u == endVertex)
        break;
      for (int v : graph.getNeighbors(u)) {
        if (!visited[v]) {
          visited[v] = true;
          parent[v] = u;
          q.push(v);
        }
      }
    }
    std::vector<int> path;
    if (!visited[endVertex])
      return path;                                        // no path found
    for (int at = endVertex; at != -1; at = parent[at]) { // backtracking
      path.push_back(at);
    }
    std::reverse(path.begin(), path.end()); // algorithm lib
    return path;
  }

  // Topological sort (for directed acyclic graphs)
  static std::vector<int> topologicalSort(const Graph &graph) {
    // TODO: Implement topological sort using DFS
    // 1. Run DFS on each unvisited vertex
    // 2. After exploring all neighbors of a vertex, add it to the front of the
    // result list
    // 3. Return the result list (in reverse order of completion time)
    std::vector<bool> visited(graph.getNumVertices(), false);
    std::vector<int> result;
    // DFS post-order traversal.
    // recursive lambda function
    auto topoDFS = [&](auto &self, int v) -> void {
      visited[v] = true;
      for (int neighbor : graph.getNeighbors(v)) {
        if (!visited[neighbor]) {
          self(self, neighbor);
        }
      }
      result.push_back(v);
    };

    for (int i = 0; i < graph.getNumVertices(); i++) {
      if (!visited[i]) {
        topoDFS(topoDFS, i);
      }
    }

    std::reverse(result.begin(), result.end());
    return result;
  }
  // Helper function for first DFS pass in Kosaraju's algorithm
  static void kosarajuFirstDFS(const Graph &graph, int vertex,
                               std::vector<bool> &visited,
                               std::stack<int> &finishOrder) {
    // TODO: Implement first DFS pass of Kosaraju's algorithm
    // 1. Mark current vertex as visited
    // 2. Recursively visit all unvisited neighbors
    // 3. After processing all neighbors, push current vertex to finishOrder
    // stack (This creates a stack with vertices ordered by decreasing finish
    // time)
    visited[vertex] = true;
    for (int neighbor : graph.getNeighbors(vertex)) {
      if (!visited[neighbor]) {
        kosarajuFirstDFS(graph, neighbor, visited, finishOrder);
      }
    }
    finishOrder.push(vertex);
  }

  // Helper function for second DFS pass in Kosaraju's algorithm
  static void kosarajuSecondDFS(const Graph &graph, int vertex,
                                std::vector<bool> &visited,
                                std::vector<int> &component) {
    // TODO: Implement second DFS pass of Kosaraju's algorithm
    // 1. Mark current vertex as visited
    // 2. Add current vertex to the current component
    // 3. Recursively visit all unvisited neighbors
    // (This identifies vertices in the current strongly connected component)
    visited[vertex] = true;
    component.push_back(vertex);
    for (int neighbor : graph.getNeighbors(vertex)) {
      if (!visited[neighbor]) {
        kosarajuSecondDFS(graph, neighbor, visited, component);
      }
    }
  }

  // Find strongly connected components using Kosaraju's algorithm
  static std::vector<std::vector<int>>
  findStronglyConnectedComponents(const Graph &graph) {
    // TODO: Implement Kosaraju's algorithm for finding SCCs
    // 1. Check if graph is directed (algorithm only works for directed graphs)
    // 2. First DFS pass:
    //    a. For each unvisited vertex, run kosarajuFirstDFS
    //    b. This fills the stack with vertices in order of decreasing finish
    //    times
    // 3. Create a reversed graph by reversing all edges
    // 4. Second DFS pass:
    //    a. Process vertices in order from the stack (decreasing finish time)
    //    b. For each unvisited vertex, run kosarajuSecondDFS to find a
    //    component c. Add each component to the result
    // 5. Return the list of strongly connected components
    std::vector<std::vector<int>> sccs;
    if (!graph.isDirected())
      return sccs;
    int n = graph.getNumVertices();
    std::stack<int> finsishOrder;
    std::vector<bool> visited(n, false);
    for (int i{0}; i < n; i++) {
      if (!visited[i]) {
        kosarajuFirstDFS(graph, i, visited, finsishOrder);
      }
    }
    AdjacencyListGraph reversedGraph(n, true);
    for (int i{0}; i < n; i++) {
      for (int neighbor : graph.getNeighbors(i)) {
        reversedGraph.addEdge(neighbor, i);
      }
    }
    // reset visited for DFS2 on reversed graph
    std::fill(visited.begin(), visited.end(), false);
    while (!finsishOrder.empty()) {
      int v = finsishOrder.top();
      finsishOrder.pop();
      if (!visited[v]) {
        std::vector<int> component;
        kosarajuSecondDFS(reversedGraph, v, visited, component);
        sccs.push_back(component);
      }
    }
    return sccs; // Placeholder
  }
};

//-------------------- TESTING FUNCTION --------------------
void testGraphImplementations() {
  // Test Adjacency Matrix (Undirected)
  std::cout << "======= Testing Undirected Adjacency Matrix Graph =======\n";
  AdjacencyMatrixGraph matrixGraph(5);

  // Add edges
  matrixGraph.addEdge(0, 1);
  matrixGraph.addEdge(0, 4);
  matrixGraph.addEdge(1, 2);
  matrixGraph.addEdge(1, 3);
  matrixGraph.addEdge(1, 4);
  matrixGraph.addEdge(2, 3);
  matrixGraph.addEdge(3, 4);

  // Print the graph
  std::cout << "Adjacency Matrix:\n";
  matrixGraph.printGraph();

  // Test edge existence
  std::cout << "Edge (0,1): "
            << (matrixGraph.hasEdge(0, 1) ? "exists" : "doesn't exist")
            << std::endl;
  std::cout << "Edge (2,4): "
            << (matrixGraph.hasEdge(2, 4) ? "exists" : "doesn't exist")
            << std::endl;

  // Test neighbors
  std::cout << "Neighbors of vertex 1: ";
  std::vector<int> neighbors = matrixGraph.getNeighbors(1);
  for (int neighbor : neighbors) {
    std::cout << neighbor << " ";
  }
  std::cout << std::endl;

  // Test Adjacency List (Directed)
  std::cout << "\n======= Testing Directed Adjacency List Graph =======\n";
  AdjacencyListGraph listGraph(5, true);

  // Add edges
  listGraph.addEdge(0, 1);
  listGraph.addEdge(0, 4);
  listGraph.addEdge(1, 2);
  listGraph.addEdge(1, 3);
  listGraph.addEdge(1, 4);
  listGraph.addEdge(2, 3);
  listGraph.addEdge(3, 4);

  // Print the graph
  std::cout << "Adjacency List:\n";
  listGraph.printGraph();

  // Test edge existence
  std::cout << "Edge (0,1): "
            << (listGraph.hasEdge(0, 1) ? "exists" : "doesn't exist")
            << std::endl;
  std::cout << "Edge (4,0): "
            << (listGraph.hasEdge(4, 0) ? "exists" : "doesn't exist")
            << std::endl;

  // Test graph traversal algorithms
  std::cout << "\n======= Testing Graph Algorithms =======\n";

  // DFS
  std::cout << "DFS starting from vertex 0:\n";
  std::vector<bool> visited(5, false);
  // GraphAlgorithms::DFS(listGraph, 0, visited);
  GraphAlgorithms::DFSIterative(listGraph, 0);

  // BFS
  std::cout << "\nBFS starting from vertex 0:\n";
  GraphAlgorithms::BFS(listGraph, 0);

  // Connected Components (using undirected graph)
  std::cout << "\nConnected Components in undirected graph: "
            << GraphAlgorithms::findConnectedComponents(matrixGraph)
            << std::endl;

  // Bipartite Check
  std::cout << "Is the undirected graph bipartite? "
            << (GraphAlgorithms::isBipartite(matrixGraph) ? "Yes" : "No")
            << std::endl;

  // Shortest Path
  std::cout << "\nShortest path from vertex 0 to 3:\n";
  std::vector<int> path = GraphAlgorithms::findShortestPath(matrixGraph, 0, 3);
  for (int vertex : path) {
    std::cout << vertex << " ";
  }
  std::cout << std::endl;

  // Topological Sort (using directed graph)
  std::cout << "\nTopological Sort of the directed graph:\n";
  std::vector<int> topoOrder = GraphAlgorithms::topologicalSort(listGraph);
  for (int vertex : topoOrder) {
    std::cout << vertex << " ";
  }
  std::cout << std::endl;
  // Test Strongly Connected Components (using directed graph)
  std::cout << "\n======= Testing Strongly Connected Components =======\n";
  AdjacencyListGraph sccGraph(8, true);

  // Add edges to create SCCs as shown in the PDF example
  sccGraph.addEdge(0, 1);
  sccGraph.addEdge(1, 2);
  sccGraph.addEdge(2, 0);
  sccGraph.addEdge(2, 3);
  sccGraph.addEdge(3, 4);
  sccGraph.addEdge(4, 5);
  sccGraph.addEdge(5, 3);
  sccGraph.addEdge(6, 5);
  sccGraph.addEdge(6, 7);
  sccGraph.addEdge(7, 6);

  std::cout << "Graph for SCC test:\n";
  sccGraph.printGraph();

  std::vector<std::vector<int>> sccs =
      GraphAlgorithms::findStronglyConnectedComponents(sccGraph);

  std::cout << "Strongly Connected Components:\n";
  for (size_t i = 0; i < sccs.size(); i++) {
    std::cout << "Component " << i + 1 << ": ";
    for (int vertex : sccs[i]) {
      std::cout << vertex << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  testGraphImplementations();
  return 0;
}
