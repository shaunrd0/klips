/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Driver program to test weighted graph implementation                ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "lib-graph.hpp"


int main (const int argc, const char * argv[])
{
  // We could initialize the graph with some localNodes...
  std::vector<Node> localNodes{
      {1, {{2, 0}, {5, 0}}}, // Node 1
      {2, {{1, 0}, {6, 0}}}, // Node 2
      {3, {{4, 0}, {6, 0}, {7, 0}}},
      {4, {{3, 0}, {7, 0}, {8, 0}}},
      {5, {{1, 0}}},
      {6, {{2, 0}, {3, 0}, {7, 0}}},
      {7, {{3, 0}, {4, 0}, {6, 0}, {8, 0}}},
      {8, {{4, 0}, {6, 0}}},
  };
  Graph bfsGraphInit(localNodes);


  std::cout << "\n\n##### Breadth First Search #####\n";
  // Or we could use an initializer list...
  // Initialize a example graph for Breadth First Search
  Graph bfsGraph(
      {
          {1, {{2, 0}, {5, 0}}}, // Node 1
          {2, {{1, 0}, {6, 0}}}, // Node 2...
          {3, {{4, 0}, {6, 0}, {7, 0}}},
          {4, {{3, 0}, {7, 0}, {8, 0}}},
          {5, {{1, 0}}},
          {6, {{2, 0}, {3, 0}, {7, 0}}},
          {7, {{3, 0}, {4, 0}, {6, 0}, {8, 0}}},
          {8, {{4, 0}, {6, 0}}},
      }
  );
  // The graph traversed in this example is seen in MIT Intro to Algorithms
  // + Chapter 22, Figure 22.3 on BFS
  bfsGraph.BFS(bfsGraph.GetNodeCopy(2));

  std::cout << "\nTesting finding a path between two nodes using BFS...\n";
  // Test finding a path between two nodes using BFS
  auto path = bfsGraph.PathBFS(
      bfsGraph.GetNodeCopy(1), bfsGraph.GetNodeCopy(7)
  );
  // If we were returned an empty path, it doesn't exist
  if (path.empty()) std::cout << "No valid path found!\n";
  else {
    // If we were returned a path, print it
    std::cout << "\nValid path from " << path.front().number
              << " to " << path.back().number << ": ";
    for (const auto &node : path) {
      std::cout << node.number << " ";
    }
    std::cout << std::endl;
  }


  std::cout << "\n\n##### Depth First Search #####\n";
  // Initialize an example graph for Depth First Search
  Graph dfsGraph(
      {
          {1, {{2, 0}, {4, 0}}},
          {2, {{5, 0}}},
          {3, {{5, 0}, {6, 0}}},
          {4, {{2, 0}}},
          {5, {{4, 0}}},
          {6, {{6, 0}}},
      }
  );
  // The graph traversed in this example is seen in MIT Intro to Algorithms
  // + Chapter 22, Figure 22.4 on DFS
  dfsGraph.DFS();


  std::cout << "\n\n##### Topological Sort #####\n";
  // Initialize an example graph for Depth First Search
  // + The order of initialization is important
  // + To produce the same result as seen in the book
  // ++ If the order is changed, other valid topological orders will be found
  // The book starts on the 'shirt' node (with the number 6, in this example)
  Graph topologicalGraph (
      {
          {1, {{4, 0}, {5, 0}}},  // undershorts
          {2, {{5, 0}}},          // socks
          {3, {}},                // watch
          {4, {{5, 0}, {7, 0}}},  // pants
          {5, {}},                // shoes
          {6, {{8, 0}, {7, 0}}},  // shirt
          {7, {{9, 0}}},          // belt
          {8, {{9, 0}}},          // tie
          {9, {}},                // jacket
      }
  );

  // The graph traversed in this example is seen in MIT Intro to Algorithms
  // + Chapter 22, Figure 22.4 on DFS
  // Unlike the simple-graph example, this final result matches MIT Algorithms
  // + Aside from the placement of the watch node, which is not connected
  // + This is because the node is visited after all other nodes are finished
  std::vector<Node> order =
      topologicalGraph.TopologicalSort(topologicalGraph.GetNodeCopy(6));
  std::cout << "\nTopological order: ";
  while (!order.empty()) {
    std::cout << order.back().number << " ";
    order.pop_back();
  }
  std::cout << std::endl << std::endl;

  // If we want the topological order to match what is seen in the book
  // + We have to initialize the graph carefully to get this result -
  Graph topologicalGraph2 (
      {
          {6, {{8, 0}, {7, 0}}},  // shirt
          {8, {{9, 0}}},          // tie
          {7, {{9, 0}}},          // belt
          {9, {}},                // jacket
          {3, {}},                // watch
          {1, {{4, 0}, {5, 0}}},  // undershorts
          {4, {{5, 0}, {7, 0}}},  // pants
          {5, {}},                // shoes
          {2, {{5, 0}}},          // socks
      }
  );
  auto order2 = topologicalGraph2.TopologicalSort(*topologicalGraph2.NodeBegin());
  std::cout << "\nTopological order: ";
  while (!order2.empty()) {
    std::cout << order2.back().number << " ";
    order2.pop_back();
  }
  std::cout << std::endl;


  std::cout << "\n\n##### Minimum Spanning Trees #####\n";
  // This example graph is seen in MIT Algorithms chapter 23, figure 23.4
  // + The result we produce is the same in total weight
  // + Differs only in the connection of nodes (2->3) *instead of* (8->1)
  // ++ Both of these edges have the same weight, and we do not create a cycle
  Graph graphMST(
      {
          {1, {{2, 4}}},
          {2, {{3, 8}}},
          {3, {{4, 7}}},
          {4, {{5, 9}}},
          {5, {{6, 10}}},
          {6, {{3, 4}, {4, 14}, {7, 2}}},
          {7, {{8, 1}}},
          {8, {{1, 8}, {2, 11}, {9, 7}}},
          {9, {{3, 2}, {7, 6}}}
      }
  );
  std::cout << "\nChecking weight traversing graph from node 1 using DFS...\n";
  InfoDFS resultDFS = graphMST.DFS(graphMST.GetNodeCopy(1));
  std::cout << "DFS total weight traversed: " << resultDFS.totalWeight << std::endl;

  std::cout << "\nChecking weight traversing graph from node 1 using BFS...\n";
  InfoBFS resultBFS = graphMST.BFS(graphMST.GetNodeCopy(1));
  std::cout << "BFS total weight traversed: " << resultBFS.totalWeight << std::endl;

  InfoMST resultMST = graphMST.KruskalMST();
  std::cout << "\n\nFinding MST using Kruskal's...\n\nMST result: \n";
  for (const auto &edge : resultMST.edgesMST) {
    std::cout << "Connected nodes: " << edge.second.first << "->"
              << edge.second.second << " with weight of " << edge.first << "\n";
  }
  std::cout << "Total MST weight: " << resultMST.totalWeight << std::endl;
}
