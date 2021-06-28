/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: Driver program to test object graph implementation                  ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "lib-graph.hpp"


void Graph::BFS(const Node& startNode) const
{
  // Track the nodes we have discovered
  //  TODO: Do this at the end to maintain the state instead of at beginning?
  for (const auto &node : nodes_) node.color = White;

  // Create a queue to visit discovered nodes in FIFO order
  std::queue<Node> visitQueue;

  // Mark the startNode as in progress until we finish checking adjacent nodes
  startNode.color = Gray;

  // Visit the startNode
  visitQueue.push(startNode);

  // Continue to visit nodes until there are none left in the graph
  while (!visitQueue.empty()) {
    // Remove thisNode from the visitQueue, storing its vertex locally
    Node thisNode = visitQueue.front();
    visitQueue.pop();
    std::cout << "Visiting node " << thisNode.number << std::endl;

    // Check if we have already discovered all the adjacentNodes to thisNode
    for (const auto &adjacent : thisNode.adjacent) {
      if (nodes_[adjacent - 1].color == White) {
        std::cout << "Found undiscovered adjacentNode: " << adjacent << "\n";
        // Mark the adjacent node as in progress
        nodes_[adjacent - 1].color = Gray;
        // Add the discovered node the the visitQueue
        visitQueue.push(nodes_[adjacent - 1]);
      }
    }
    // We are finished with this node and the adjacent nodes; Mark it discovered
    thisNode.color = Black;
  }

}

void Graph::DFS() const
{
  // Track the nodes we have discovered
  for (const auto &node : nodes_) node.color = White;
  int time = 0;

  // Visit each node in the graph
  for (const auto& node : nodes_) {
    std::cout << "Visiting node " << node.number << std::endl;
    // If the node is undiscovered, visit it
    if (node.color == White) {
      std::cout << "Found undiscovered node: " << node.number << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, node);
    }
  }

}

void Graph::DFSVisit(int &time, const Node& startNode) const
{
  startNode.color = Gray;
  time++;
  startNode.discoveryFinish.first = time;
  // Check the adjacent nodes of the startNode
  for (const auto &adjacent : startNode.adjacent) {
    auto iter = std::find(nodes_.begin(), nodes_.end(),
                          Node(adjacent, {}));
    // If the adjacentNode is undiscovered, visit it
    // + Offset by 1 to account for 0 index of discovered vector
    if (iter->color == White) {
      std::cout << "Found undiscovered adjacentNode: "
                << nodes_[adjacent - 1].number << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, *iter);
    }
  }
  startNode.color = Black;
  time++;
  startNode.discoveryFinish.second = time;
}

std::vector<Node> Graph::TopologicalSort() const
{
  DFS();
  std::vector<Node> topological(nodes_);

  std::sort(topological.begin(), topological.end(), Node::FinishedSort);

  // The topologicalOrder is read right-to-left in the final result
  // + Output is handled in main as FILO, similar to a stack
  return topological;
}
