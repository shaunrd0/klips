/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: Driver program to test a simple graph implementation               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-graph.hpp"


int main (const int argc, const char * argv[])
{
  // We could initialize the graph with some localNodes...
  std::map<int, std::set<int>> localNodes{
      {1, {2, 5}}, // Node 1
      {2, {1, 6}}, // Node 2
      {3, {4, 6, 7}},
      {4, {3, 7, 8}},
      {5, {1}},
      {6, {2, 3, 7}},
      {7, {3, 4, 6, 8}},
      {8, {4, 6}},
  };
//  Graph bfsGraph(localNodes);


  std::cout << "\n\n##### Breadth First Search #####\n";
  // Or we could use an initializer list...
  // Initialize a example graph for Breadth First Search
  Graph bfsGraph (
      {
          {1, {2, 5}}, // Node 1
          {2, {1, 6}}, // Node 2...
          {3, {4, 6, 7}},
          {4, {3, 7, 8}},
          {5, {1}},
          {6, {2, 3, 7}},
          {7, {3, 4, 6, 8}},
          {8, {4, 6}},
      }
  );
  // The graph traversed in this example is seen in MIT Intro to Algorithms
  // + Chapter 22, Figure 22.3 on BFS
  bfsGraph.BFS(2);


  std::cout << "\n\n##### Depth First Search #####\n";
  // Initialize an example graph for Depth First Search
  Graph dfsGraph (
      {
          {1, {2, 4}},
          {2, {5}},
          {3, {5, 6}},
          {4, {2}},
          {5, {4}},
          {6, {6}},
      }
  );
  // The graph traversed in this example is seen in MIT Intro to Algorithms
  // + Chapter 22, Figure 22.4 on DFS
  dfsGraph.DFS();


  std::cout << "\n\n##### Topological Sort #####\n";
  // Initialize an example graph for Topological Sort
  Graph topologicalGraph (
      {
          {1, {4, 5}},
          {2, {5}},
          {3, {}},
          {4, {5, 7}},
          {5, {}},
          {6, {7, 8}},
          {7, {9}},
          {8, {9}},
          {9, {}},
      }
  );
  // The graph traversed in this example is seen in MIT Intro to Algorithms
  // + Chapter 22, Figure 22.7 on Topological Sort
  // + Each node was replaced with a value from left-to-right, top-to-bottom
  // + Undershorts = 1, Socks = 2, Watch = 3, Pants = 4, etc...
  std::vector<int> order = topologicalGraph.TopologicalSort();
  // Because this is a simple graph with no objects to store finishing time
  // + The result is only one example of valid topological order
  // + There are other valid orders; Final result differs from one in the book
  std::cout << "\n\nTopological order: ";
  while (!order.empty()) {
    std::cout << order.back() << " ";
    order.pop_back();
  }
  std::cout << std::endl;

}
