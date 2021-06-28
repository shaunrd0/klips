/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: An example of an object graph implementation                        ##
##        Algorithms in this example are found in MIT Intro to Algorithms     ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "lib-graph.hpp"


int main (const int argc, const char * argv[])
{
  // We could initialize the graph with some localNodes...
  std::map<int, std::vector<int>> localNodes{
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
          {Node(1, {2, 5})}, // Node 1
          {Node(2, {1, 6})}, // Node 2...
          {Node(3, {4, 6, 7})},
          {Node(4, {3, 7, 8})},
          {Node(5, {1})},
          {Node(6, {2, 3, 7})},
          {Node(7, {3, 4, 6, 8})},
          {Node(8, {4, 6})},
      }
  );
  // The graph traversed in this example is seen in MIT Intro to Algorithms
  // + Chapter 22, Figure 22.3 on BFS
  auto iter = bfsGraph.nodes_.begin();
  std::advance(iter, 1);
  bfsGraph.BFS(*iter);


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
  // Initialize an example graph for Depth First Search
  Graph topologicalGraph (
      {
          {6, {8, 7}}, // shirt
          {8, {9}},    // tie
          {7, {9}},    // belt
          {9, {}},     // jacket
          {3, {}},     // watch
          {1, {4, 5}}, // undershorts
          {4, {5, 7}}, // pants
          {5, {}},     // shoes
          {2, {5}},    // socks
      }
  );
  // The graph traversed in this example is seen in MIT Intro to Algorithms
  // + Chapter 22, Figure 22.4 on DFS
  // Unlike the simple-graph example, this final result matches MIT Algorithms
  std::vector<Node> order = topologicalGraph.TopologicalSort();
  std::cout << "\n\nTopological order: ";
  while (!order.empty()) {
    std::cout << order.back().number << " ";
    order.pop_back();
  }
  std::cout << std::endl;

}
