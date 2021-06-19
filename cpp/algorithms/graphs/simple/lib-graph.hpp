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


class Graph {
public:
  explicit Graph(std::map<int, std::set<int>> nodes) : nodes_(std::move(nodes)) {}
  std::map<int, std::set<int>> nodes_;

  void BFS(int startNode);

  void DFS();
  void DFSVisit(int startNode, std::vector<bool> &discovered);

  std::vector<int> TopologicalSort();
  void TopologicalVisit(
      int startNode, std::vector<bool> &discovered, std::vector<int> &order
  );
};

#endif // LIB_GRAPH_HPP
