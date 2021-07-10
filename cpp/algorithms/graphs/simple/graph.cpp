/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: Driver program to test a simple graph implementation                ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "lib-graph.hpp"


int main (const int argc, const char * argv[])
{
  // We could initialize the graph with some localNodes...
  std::unordered_map<int, std::unordered_set<int>> localNodes{
      {8, {6, 4}},
      {7, {8, 6, 4, 3}},
      {6, {7, 3, 2}},
      {5, {1}},
      {4, {8, 7, 3}},
      {3, {7, 6, 4}},
      {2, {6, 1}}, // Node 2...
      {1, {5, 2}}, // Node 1
  };
  Graph exampleGraph(localNodes);


  std::cout << "\n\n##### Breadth First Search #####\n";
  // Or we could use an initializer list...
  // Initialize a example graph for Breadth First Search
  Graph bfsGraph (
      {
          {8, {6, 4}},
          {7, {8, 6, 4, 3}},
          {6, {7, 3, 2}},
          {5, {1}},
          {4, {8, 7, 3}},
          {3, {7, 6, 4}},
          {2, {6, 1}}, // Node 2...
          {1, {5, 2}}, // Node 1
      }
  );
  // The graph traversed in this example is seen in MIT Intro to Algorithms
  // + Chapter 22, Figure 22.3 on BFS
  bfsGraph.BFS(2);


  std::cout << "\n\n##### Depth First Search #####\n";
  // Initialize an example graph for Depth First Search
  Graph dfsGraph (
      {
          {6, {6}},
          {5, {4}},
          {4, {2}},
          {3, {6, 5}},
          {2, {5}},
          {1, {4, 2}},
      }
  );
  // The graph traversed in this example is seen in MIT Intro to Algorithms
  // + Chapter 22, Figure 22.4 on DFS
  dfsGraph.DFS();


  std::cout << "\n\n##### Topological Sort #####\n";
  // Initialize an example graph for Topological Sort
  Graph topologicalGraph (
      {
          {9, {}},
          {8, {9}},
          {7, {9}},
          {6, {7, 8}},
          {5, {}},
          {4, {7, 5}},
          {3, {}},
          {2, {5}},
          {1, {5, 4}},
      }
  );
  auto order = topologicalGraph.TopologicalSort(topologicalGraph.GetNode(6));
  std::cout << "\nTopological order: ";
  while (!order.empty()) {
    std::cout << order.back() << " ";
    order.pop_back();
  }
  std::cout << std::endl << std::endl;

  //   If we want the topological order to match what is seen in the book
  // + We have to initialize the graph carefully to get this result -
  // Because this is an unordered_(map/set) initialization is reversed
  // + So the order of nodes on the container below is 6,7,8,9,3,1,4,5,2
  // + The same concept applies to their adjacent nodes (7,8 initializes to 8,7)
  // + In object-graph implementation, I use vectors this does not apply there
  Graph topologicalGraph2 (
      {
          {2, {5}},    // socks
          {5, {}},     // shoes
          {4, {7, 5}}, // pants
          {1, {5, 4}}, // undershorts
          {3, {}},     // watch
          {9, {}},     // jacket
          {7, {9}},    // belt
          {8, {9}},    // tie
          {6, {7, 8}}, // shirt
      }
  );

  // The graph traversed in this example is seen in MIT Intro to Algorithms
  // + Chapter 22, Figure 22.7 on Topological Sort
  // + Each node was replaced with a value from left-to-right, top-to-bottom
  // + Undershorts = 1, Socks = 2, Watch = 3, Pants = 4, etc...
  std::vector<int> order2 =
      topologicalGraph2.TopologicalSort(topologicalGraph2.NodeBegin());
  // Because this is a simple graph with no objects to store finishing time
  // + The result is only one example of valid topological order
  // + There are other valid orders; Final result differs from one in the book
  std::cout << "\nTopological order: ";
  while (!order2.empty()) {
    std::cout << order2.back() << " ";
    order2.pop_back();
  }
  std::cout << std::endl;

  std::cout << std::endl;

  return 0;
}
