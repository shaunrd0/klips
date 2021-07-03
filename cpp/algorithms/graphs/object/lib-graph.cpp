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
  // Track the nodes we have discovered by their Color
  for (const auto &node : nodes_) {
    node.color = White;
    // Track distance from the startNode
    node.distance = 0;
    // Track predecessor using node that discovers this node
    // + If this is the startNode, predecessor remains nullptr
    node.predecessor = nullptr;
  }

  // Create a queue to visit discovered nodes in FIFO order
  std::queue<const Node *> visitQueue;

  // Mark the startNode as in progress until we finish checking adjacent nodes
  startNode.color = Gray;

  // Visit the startNode
  visitQueue.push(&startNode);

  // Continue to visit nodes until there are none left in the graph
  while (!visitQueue.empty()) {
    // Remove thisNode from the visitQueue, storing its vertex locally
    const Node * thisNode = visitQueue.front();
    visitQueue.pop();
    std::cout << "Visiting node " << thisNode->number << std::endl;

    // Check if we have already discovered all the adjacentNodes to thisNode
    for (const auto &adjacent : thisNode->adjacent) {
      if (GetNode(adjacent).color == White) {
        std::cout << "Found undiscovered adjacentNode: " << adjacent << "\n";
        // Mark the adjacent node as in progress
        GetNode(adjacent).color = Gray;
        GetNode(adjacent).distance = thisNode->distance + 1;
        GetNode(adjacent).predecessor = &GetNode(thisNode->number);

        // Add the discovered node the the visitQueue
        visitQueue.push(&GetNode(adjacent));
      }
    }
    // We are finished with this node and the adjacent nodes; Mark it discovered
    GetNode(thisNode->number).color = Black;
  }
}

std::deque<Node> Graph::PathBFS(const Node &start, const Node &finish) const
{
  // Store the path as copies of each node
  // + If the caller modifies these, it will not impact the graph's data
  std::deque<Node> path;

  BFS(start);
  const Node * next = finish.predecessor;
  bool isValid = false;
  do {
    // If we have reached the start node, we have found a valid path
    if (*next == Node(start)) isValid = true;

    // Add the node to the path as we check each node
    // + Use emplace_front to call the Node copy constructor
    path.emplace_front(*next);

    // Move to the next node
    next = next->predecessor;
  } while (next != nullptr);
  // Use emplace_back to call Node copy constructor
  path.emplace_back(finish);

  // If we never found a valid path, erase all contents of the path
  if (!isValid) path.erase(path.begin(), path.end());

  // Return the path, the caller should handle empty paths accordingly
  return path;
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

void Graph::DFS(const Node &startNode) const
{
  // Track the nodes we have discovered
  for (const auto &node : nodes_) node.color = White;
  int time = 0;

  auto startIter = std::find(nodes_.begin(), nodes_.end(),
                             Node(startNode.number, {})
  );

  // beginning at startNode, visit each node in the graph until we reach the end
  while (startIter != nodes_.end()) {
    std::cout << "Visiting node " << startIter->number << std::endl;
    // If the startIter is undiscovered, visit it
    if (startIter->color == White) {
      std::cout << "Found undiscovered node: " << startIter->number << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, *startIter);
    }
    startIter++;
  }

  // Once we reach the last node, check the beginning for unchecked nodes
  startIter = nodes_.begin();

  // Once we reach the initial startNode, we have checked all nodes
  while (*startIter != startNode) {
    std::cout << "Visiting node " << startIter->number << std::endl;
    // If the startIter is undiscovered, visit it
    if (startIter->color == White) {
      std::cout << "Found undiscovered node: " << startIter->number << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, *startIter);
    }
    startIter++;
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
                << GetNode(adjacent).number << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, *iter);
    }
  }
  startNode.color = Black;
  time++;
  startNode.discoveryFinish.second = time;
}

std::vector<Node> Graph::TopologicalSort(const Node &startNode) const
{
  DFS(GetNode(startNode.number));
  std::vector<Node> topological(nodes_);

  std::sort(topological.begin(), topological.end(), Node::FinishedSort);

  // The topologicalOrder is read right-to-left in the final result
  // + Output is handled in main as FILO, similar to a stack
  return topological;
}
