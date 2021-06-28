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

enum Color {White, Gray, Black};

struct Node {
public:
  Node(const Node &rhs) = default;
  Node & operator=(Node rhs) {
    if (this == &rhs) return *this;
    swap(*this, rhs);
    return *this;
  }
  friend void swap(Node &a, Node &b) {
    std::swap(a.number, b.number);
    std::swap(a.adjacent, b.adjacent);
    std::swap(a.color, b.color);
    std::swap(a.discoveryFinish, b.discoveryFinish);
  }

  Node(int num, std::vector<int> adj) :
      number(num), adjacent(std::move(adj)) {}
  int number;
  std::vector<int> adjacent;
  // Mutable so we can update the color of the nodes during traversal
  mutable Color color = White;
  // Create a pair to track discovery / finish time
  // + Discovery time is the iteration the node is first discovered
  // + Finish time is the iteration the node has been checked completely
  // ++ A finished node has considered all adjacent nodes
  mutable std::pair<int, int> discoveryFinish;

  // Define a comparator for std::sort
  // + This will help to sort nodes by finished time after traversal
  static bool FinishedSort(const Node &node1, const Node &node2)
      { return node1.discoveryFinish.second < node2.discoveryFinish.second;}


  // Define operator== for std::find
  bool operator==(const Node &b) const { return this->number == b.number;}
};

class Graph {
public:
  explicit Graph(std::vector<Node> nodes) : nodes_(std::move(nodes)) {}
  std::vector<Node> nodes_;

  void BFS(const Node& startNode) const;
  void DFS() const;
  void DFSVisit(int &time, const Node& startNode) const;
  std::vector<Node> TopologicalSort() const;
};

#endif // LIB_GRAPH_HPP
