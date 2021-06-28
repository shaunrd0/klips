/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: An example of a simple graph implementation                         ##
##        Algorithms in this example are found in MIT Intro to Algorithms     ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "lib-graph.hpp"


void Graph::BFS(int startNode)
{
  // Track the nodes we have discovered
  std::vector<bool> discovered(nodes_.size(), false);

  // Create a queue to visit discovered nodes in FIFO order
  std::queue<int> visitQueue;

  // Visit the startNode
  discovered[startNode - 1] = true;
  visitQueue.push(startNode);

  // Continue to visit nodes until there are none left in the graph
  while (!visitQueue.empty()) {
    std::cout << "Visiting node " << visitQueue.front() << std::endl;

    // Remove thisNode from the visitQueue, storing its vertex locally
    int thisNode = visitQueue.front();
    visitQueue.pop();

    // Check if we have already discovered all the adjacentNodes to thisNode
    // + Do not offset this by 1, since we are using the key value for a map
    for (const auto &adjacent : nodes_[thisNode]) {
      if (!discovered[adjacent - 1]) {
        std::cout << "Found undiscovered adjacentNode: " << adjacent << "\n";
        // Mark the adjacent node as discovered
        // + If this were done out of the for loop we could discover nodes twice
        // + This would result in visiting the node twice, since it appears
        //    In the visitQueue twice
        discovered[adjacent - 1] = true;
        // Add the discovered node the the visitQueue
        // + Since this value will later be used as a map key, dont offset by 1
        visitQueue.push(adjacent);
      }
    }

  }

}

void Graph::DFS()
{
  // Track the nodes we have discovered
  std::vector<bool> discovered(nodes_.size(), false);

  // Visit each node in the graph
  for (const auto &node : nodes_) {
    std::cout << "Visiting node " << node.first << std::endl;
    // If the node is undiscovered, visit it
    if (!discovered[node.first - 1]) {
      std::cout << "Found undiscovered node: " << node.first << std::endl;
      // Mark the node as visited so we don't visit it twice
      discovered[node.first - 1] = true;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(node.first, discovered);
    }
  }

}

void Graph::DFSVisit(int startNode, std::vector<bool> &discovered)
{
  // Check the adjacent nodes of the startNode
  // + Do not offset startNode by 1, since we use it as a key to a map
  for (auto &adjacent : nodes_[startNode]) {
    // If the adjacentNode is undiscovered, visit it
    if (!discovered[adjacent - 1]) {
      std::cout << "Found undiscovered adjacentNode: " << adjacent << std::endl;
      // Mark the node as visited so we don't visit it twice
      discovered[adjacent - 1] = true;

      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(adjacent, discovered);
    }
  }

}

std::vector<int> Graph::TopologicalSort()
{
  std::vector<int> topologicalOrder;

  // Track the nodes we have discovered
  std::vector<bool> discovered(nodes_.size(), false);

  // Visit each node in the graph
  for (const auto &node : nodes_) {
    std::cout << "Visiting node " << node.first << std::endl;
    // If the node is undiscovered, visit it
    // + Offset by 1 to account for 0 index of discovered vector
    if (!discovered[node.first - 1]) {
      std::cout << "Found undiscovered node: " << node.first << std::endl;

      // Visiting the undiscovered node will check it's adjacent nodes
      TopologicalVisit(node.first, discovered, topologicalOrder);
    }
  }

  // The topologicalOrder is read right-to-left in the final result
  // + Output is handled in main as FILO, similar to a stack
  return topologicalOrder;
}

void Graph::TopologicalVisit(
    int startNode, std::vector<bool> &discovered, std::vector<int> &order
)
{
  // Mark the node as visited so we don't visit it twice
  discovered[startNode - 1] = true;

  // Check the adjacent nodes of the startNode
  // + Do not offset by 1, since startNode is used as a key to the map
  for (auto &adjacent : nodes_[startNode]) {
    // If the adjacentNode is undiscovered, visit it
    if (!discovered[adjacent - 1]) {
      std::cout << "Found undiscovered adjacentNode: " << adjacent << std::endl;

      // Visiting the undiscovered node will check it's adjacent nodes
      TopologicalVisit(adjacent, discovered, order);
    }
  }

  // Add startNode to the topologicalOrder
  order.push_back(startNode);
}
