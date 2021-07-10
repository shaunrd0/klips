/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example of a simple graph implementation                        ##
##        Algorithms in this example are found in MIT Intro to Algorithms    ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/
#ifndef LIB_GRAPH_HPP
#define LIB_GRAPH_HPP

#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>


class Graph {
public:
  using Node = std::unordered_map<int, std::unordered_set<int>>;
  explicit Graph(Node nodes) : nodes_(std::move(nodes))
  {
    discoveryTime.resize(nodes_.size());
    finishTime.resize(nodes_.size(), std::make_pair(0,0));
  }

  void BFS(int startNode);

  void DFS();
  void DFS(Node::iterator startNode);
  void DFSVisit(int &time, int startNode, std::vector<bool> &discovered);

  std::vector<int> TopologicalSort(Node::iterator startNode);
  void TopologicalVisit(
      int startNode, std::vector<bool> &discovered, std::vector<int> &order
  );

  // Define a comparator for std::sort
  // + This will help to sort nodes by finished time after traversal
  static bool FinishedSort(std::pair<int, int> &node1, decltype(node1) &node2)
  { return node1.second < node2.second;}

  inline Node::iterator NodeBegin() { return nodes_.begin();}
  // A non-const accessor for direct access to a node with the number value i
  inline Node::iterator GetNode(int i) { return nodes_.find(i);}

private:
  // Unordered to avoid container reorganizing elements
  // + Since this would alter the order nodes are traversed in
  Node nodes_;

  // Where the first element in the following two pairs is the node number
  // And the second element is the discovery / finish time
  std::vector<std::pair<int, int>> discoveryTime;
  std::vector<std::pair<int, int>> finishTime;
};

#endif // LIB_GRAPH_HPP
