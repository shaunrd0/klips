/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Driver program to test templated object graph implementation        ##
##        Algorithms in this example are found in MIT Intro to Algorithms     ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "lib-graph.hpp"


int main (const int argc, const char * argv[])
{
  // We could initialize the graph with some localNodes...
  std::vector<Node<char>> localNodes{
      {'a', {{'b', 0}, {'e', 0}}}, // Node a
      {'b', {{'a', 0}, {'f', 0}}}, // Node b
      {'c', {{'d', 0}, {'f', 0}, {'g', 0}}},
      {'d', {{'c', 0}, {'g', 0}, {'h', 0}}},
      {'e', {{'a', 0}}},
      {'f', {{'b', 0}, {'c', 0}, {'g', 0}}},
      {'g', {{'c', 0}, {'d', 0}, {'f', 0}, {'h', 0}}},
      {'h', {{'d', 0}, {'f', 0}}},
  };
  Graph<char> bfsGraphInit(localNodes);


  std::cout << "\n\n##### Breadth First Search #####\n";
  // Or we could use an initializer list...
  // Initialize a example graph for Breadth First Search
  Graph<char> bfsGraph(
      {
          {'a', {{'b', 0}, {'e', 0}}}, // Node a
          {'b', {{'a', 0}, {'f', 0}}}, // Node b
          {'c', {{'d', 0}, {'f', 0}, {'g', 0}}},
          {'d', {{'c', 0}, {'g', 0}, {'h', 0}}},
          {'e', {{'a', 0}}},
          {'f', {{'b', 0}, {'c', 0}, {'g', 0}}},
          {'g', {{'c', 0}, {'d', 0}, {'f', 0}, {'h', 0}}},
          {'h', {{'d', 0}, {'f', 0}}},
      }
  );
  // The graph traversed in this example is seen in MIT Intro to Algorithms
  // + Chapter 22, Figure 22.3 on BFS
  bfsGraph.BFS(bfsGraph.GetNodeCopy('b'));

  std::cout << "\nTesting finding a path between two nodes using BFS...\n";
  // Test finding a path between two nodes using BFS
  auto path = bfsGraph.PathBFS(
      bfsGraph.GetNodeCopy('a'), bfsGraph.GetNodeCopy('g')
  );
  // If we were returned an empty path, it doesn't exist
  if (path.empty()) std::cout << "No valid path found!\n";
  else {
    // If we were returned a path, print it
    std::cout << "\nValid path from " << path.front().GetData()
              << " to " << path.back().GetData() << ": ";
    for (const auto &node : path) {
      std::cout << node.GetData() << " ";
    }
    std::cout << std::endl;
  }


  std::cout << "\n\n##### Depth First Search #####\n";
  // Initialize an example graph for Depth First Search
  Graph<char> dfsGraph(
      {
          {'a', {{'b', 0}, {'d', 0}}},
          {'b', {{'e', 0}}},
          {'c', {{'e', 0}, {'f', 0}}},
          {'d', {{'b', 0}}},
          {'e', {{'d', 0}}},
          {'f', {{'f', 0}}},
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
  Graph<std::string> topologicalGraph (
      {
          {"undershorts", {{"pants", 0}, {"shoes", 0}}},
          {"socks", {{"shoes", 0}}},
          {"watch", {}},
          {"pants", {{"shoes", 0}, {"belt", 0}}},
          {"shoes", {}},
          {"shirt", {{"tie", 0}, {"belt", 0}}},
          {"belt", {{"jacket", 0}}},
          {"tie", {{"jacket", 0}}},
          {"jacket", {}},
      }
  );

  // The graph traversed in this example is seen in MIT Intro to Algorithms
  // + Chapter 22, Figure 22.4 on DFS
  // Unlike the simple-graph example, this final result matches MIT Algorithms
  // + Aside from the placement of the watch node, which is not connected
  // +  This is because the node is visited after all other nodes are finished
  std::vector<Node<std::string>> order =
      topologicalGraph.TopologicalSort(topologicalGraph.GetNodeCopy("shirt"));
  std::cout << "\nTopological order: ";
  while (!order.empty()) {
    std::cout << order.back().GetData() << " ";
    order.pop_back();
  }
  std::cout << std::endl << std::endl;

  // If we want the topological order to match what is seen in the book
  // + We have to initialize the graph carefully to get this result -
  Graph<std::string> topologicalGraph2 (
      {
          {"shirt", {{"tie", 0}, {"belt", 0}}},
          {"tie", {{"jacket", 0}}},
          {"belt", {{"jacket", 0}}},
          {"jacket", {}},
          {"watch", {}},
          {"undershorts", {{"pants", 0}, {"shoes", 0}}},
          {"pants", {{"shoes", 0}, {"belt", 0}}},
          {"shoes", {}},
          {"socks", {{"shoes", 0}}},
      }
  );
  auto order2 = topologicalGraph2.TopologicalSort(*topologicalGraph2.NodeBegin());
  std::cout << "\nTopological order: ";
  while (!order2.empty()) {
    std::cout << order2.back().GetData() << " ";
    order2.pop_back();
  }
  std::cout << std::endl;


  std::cout << "\n\n##### Minimum Spanning Trees #####\n";
  // This example graph is seen in MIT Algorithms chapter 23, figure 23.4
  // + The result we produce is the same in total weight
  // + Differs only in the connection of nodes (b->c) *instead of* (h->a)
  // ++ Both of these edges have the same weight, and we do not create a cycle
  Graph<char> graphMST(
      {
          {'a', {{'b', 4}}},
          {'b', {{'c', 8}}},
          {'c', {{'d', 7}}},
          {'d', {{'e', 9}}},
          {'e', {{'f', 10}}},
          {'f', {{'c', 4}, {'d', 14}, {'g', 2}}},
          {'g', {{'h', 1}}},
          {'h', {{'a', 8}, {'b', 11}, {'i', 7}}},
          {'i', {{'c', 2}, {'g', 6}}}
      }
  );
  InfoMST<char> resultMST = graphMST.KruskalMST();
  std::cout << "Finding MST using Kruskal's...\n\n";
  resultMST.Print();
}
