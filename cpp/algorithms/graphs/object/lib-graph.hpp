/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: An example of an object graph implementation                        ##
##        Algorithms in this example are found in MIT Intro to Algorithms     ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/
#ifndef LIB_GRAPH_HPP
#define LIB_GRAPH_HPP

#include <iostream>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>
#include <queue>
#include <unordered_set>

// Color represents the discovery status of any given node
// + White is undiscovered, Gray is in progress, Black is fully discovered
enum Color {White, Gray, Black};

/******************************************************************************/
// Node structure for representing a graph
struct Node {
public:
  // Constructors
  Node(const Node &rhs) = default;
  Node & operator=(Node rhs) {
    if (this == &rhs) return *this;
    swap(*this, rhs);
    return *this;
  }
  Node(int num, std::vector<int> adj) : number(num), adjacent(std::move(adj)) {}

  friend void swap(Node &a, Node &b) {
    std::swap(a.number, b.number);
    std::swap(a.adjacent, b.adjacent);
    std::swap(a.color, b.color);
    std::swap(a.discoveryFinish, b.discoveryFinish);
  }

  // Don't allow anyone to change these values when using a const reference
  int number;
  std::vector<int> adjacent;

  // Mutable members so we can update these values when using a const reference
  // + Since they need to be modified during traversals

  // Coloring of the nodes are used in both DFS and BFS
  mutable Color color = White;

  // Used in BFS to represent distance from start node
  mutable int distance = 0;
  // Used in BFS to represent the parent node that discovered this node
  // + If we use this node as the starting point, this will remain a nullptr
  mutable const Node *predecessor = nullptr;

  // Create a pair to track discovery / finish time when using DFS
  // + Discovery time is the iteration the node is first discovered
  // + Finish time is the iteration the node has been checked completely
  // ++ A finished node has considered all adjacent nodes
  mutable std::pair<int, int> discoveryFinish;

  // Define a comparator for std::sort
  // + This will help to sort nodes by finished time after traversal
  static bool FinishedSort(const Node &node1, const Node &node2)
  { return node1.discoveryFinish.second < node2.discoveryFinish.second;}

  // Define operator== for std::find; And comparisons between nodes
  bool operator==(const Node &b) const { return this->number == b.number;}
  // Define an operator!= for comparing nodes for inequality
  bool operator!=(const Node &b) const { return this->number != b.number;}
};


/******************************************************************************/
// Graph class declaration
class Graph {
public:
  // Constructor
  explicit Graph(std::vector<Node> nodes) : nodes_(std::move(nodes)) {}


  // Breadth First Search
  void BFS(const Node& startNode) const;
  std::deque<Node> PathBFS(const Node &start, const Node &finish) const;


  // Depth First Search
  void DFS() const;
  // An alternate DFS that checks each node of the graph beginning at startNode
  void DFS(const Node &startNode) const;
  // Visit function is used in both versions of DFS
  void DFSVisit(int &time, const Node& startNode) const;
  // Topological sort, using DFS
  std::vector<Node> TopologicalSort(const Node &startNode) const;


  // Returns a copy of a node with the number i within the graph
  // + This uses the private, non-const accessor GetNode()
  inline Node GetNodeCopy(int i) { return GetNode(i);}
  // Return a constant iterator for reading node values
  inline std::vector<Node>::const_iterator NodeBegin() { return nodes_.cbegin();}

private:
  // A non-const accessor for direct access to a node with the number value i
  inline Node & GetNode(int i)
  { return *std::find(nodes_.begin(), nodes_.end(), Node(i, {}));}
  // For use with const member functions to access mutable values
  inline const Node & GetNode(int i) const
  { return *std::find(nodes_.begin(), nodes_.end(), Node(i, {}));}

  std::vector<Node> nodes_;
};

#endif // LIB_GRAPH_HPP
