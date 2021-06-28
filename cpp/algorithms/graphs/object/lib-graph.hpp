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
#include <set>
#include <utility>
#include <vector>
#include <queue>

// A vertex can also be referred to as a node
// + ... Unless you are a mathematician ^.^
struct Vertex {
  // This vertex's number
  int number;
  // A set of all vertices adjacent to this vertex
  std::set<int> adjacent;
};

enum Color {White, Gray, Black};

struct Node {
public:
  Node(int num, std::set<int> adj) : number(num), adjacent(std::move(adj)) {}
  int number;
  std::set<int> adjacent;
  // Mutable so we can update the color of the nodes during traversal
  mutable Color color = White;
  std::vector<int> predecessors;

//  bool operator<(const Node &node1) const { return number < node1.number;}
  inline void setColor(Color newColor) const { color = newColor;}
};

class Graph {
public:
  explicit Graph(std::vector<Node> nodes) : nodes_(std::move(nodes)) {}
  std::vector<Node> nodes_;

  void BFS(const Node& startNode) const;
  void DFS() const;
  void DFSVisit(const Node& startNode) const;
  std::vector<Node> TopologicalSort() const;
  void TopologicalVisit(const Node &startNode, std::vector<Node> &order) const;

};

#endif // LIB_GRAPH_HPP
