/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example of a simple graph implementation                         ##
##        Algorithms in this example are found in MIT Intro to Algorithms     ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include <algorithm>
#include "lib-graph.hpp"


void Graph::BFS(int startNode)
{
  // Track the nodes we have discovered
  std::vector<bool> discovered(nodes_.size(), false);
  // Reset values of predecessor and distance JIC there was a previous traversal
  for (auto &p : predecessor) p = std::make_pair(0, INT32_MIN);
  for (auto &d : distance) d = std::make_pair(0, 0);

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

        // Update the distance from the start node
        distance[adjacent - 1] =
            std::make_pair(adjacent, distance[thisNode - 1].second + 1);
        // Update the predecessor for the adjacent node when we discover it
        // + The node that first discovers the adjacent is the predecessor
        predecessor[adjacent - 1] = std::make_pair(adjacent, thisNode);

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

std::deque<int> Graph::PathBFS(int start, int finish)
{
  // Store the path as a deque of integers so we can push to the front and back
  std::deque<int> path;
  // Perform BFS on the start node, updating all possible predecessors
  BFS(start);
  // Begin at the finish node's predecessor
  int next = predecessor[finish - 1].second;
  bool isValid = false;
  do {
    // If the next node is the start node, we have found a valid path
    if (next == start) isValid = true;
    // Add the next node to the path
    path.push_front(next);
    // Move to the predecessor of the next node
    next = predecessor[next - 1].second;
  } while (next != INT32_MIN); // If we hit a node with no predecessor, break
  // Push the finish node the end of the path
  // + We could do this prior to the loop with push_front.. but, deques :)
  path.push_back(finish);
  // If we never found a valid path, erase the path
  if (!isValid) path.erase(path.begin(), path.end());
  // Return the path, the caller should handle the case where the path is empty
  return path;
}

void Graph::DFS()
{
  // Track the nodes we have discovered
  std::vector<bool> discovered(nodes_.size(), false);
  int time = 0;

  // Visit each node in the graph
  for (const auto &node : nodes_) {
    std::cout << "Visiting node " << node.first << std::endl;
    // If the node is undiscovered, visit it
    if (!discovered[node.first - 1]) {
      std::cout << "Found undiscovered node: " << node.first << std::endl;
      // Mark the node as visited so we don't visit it twice
      discovered[node.first - 1] = true;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, node.first, discovered);
    }
  }

}

void Graph::DFS(Node::iterator startIter)
{
  // Track the nodes we have discovered
  std::vector<bool> discovered(nodes_.size(), false);
  int time = 0;

  auto startNode = GetNode(startIter->first);

  // beginning at startNode, visit each node in the graph until we reach the end
  while (startIter != nodes_.end()) {
    std::cout << "Visiting node " << startIter->first << std::endl;
    // If the startIter is undiscovered, visit it
    if (!discovered[startIter->first - 1]) {
      std::cout << "Found undiscovered node: " << startIter->first << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      discovered[startIter->first - 1] = true;
      DFSVisit(time, startIter->first, discovered);
    }
    startIter++;
  }

  // Once we reach the last node, check the beginning for unchecked nodes
  startIter = nodes_.begin();

  // Once we reach the initial startNode, we have checked all nodes
  while (startIter->first != startNode->first) {
    std::cout << "Visiting node " << startIter->first << std::endl;
    // If the startIter is undiscovered, visit it
    if (!discovered[startIter->first - 1]) {
      std::cout << "Found undiscovered node: " << startIter->first << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      discovered[startIter->first - 1] = true;
      DFSVisit(time, startIter->first, discovered);
    }
    startIter++;
  }
}

void Graph::DFSVisit(int &time, int startNode, std::vector<bool> &discovered)
{
  time++;
  discoveryTime[startNode - 1] = std::make_pair(startNode, time);

  // Check the adjacent nodes of the startNode
  // + Do not offset startNode by 1, since we use it as a key to a map
  for (auto &adjacent : nodes_[startNode]) {
    // If the adjacentNode is undiscovered, visit it
    if (!discovered[adjacent - 1]) {
      std::cout << "Found undiscovered adjacentNode: " << adjacent << std::endl;
      // Mark the node as visited so we don't visit it twice
      discovered[adjacent - 1] = true;

      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, adjacent, discovered);
    }
  }

  time++;
  finishTime[startNode - 1] = std::make_pair(startNode, time);
}

std::vector<int> Graph::TopologicalSort(Node::iterator startNode)
{
  DFS(startNode);

  std::vector<int> topologicalOrder;

  std::vector<std::pair<int, int>> finishOrder(finishTime);

  std::sort(finishOrder.begin(), finishOrder.end(), Graph::FinishedSort);

  for (const auto &node : finishOrder) topologicalOrder.push_back(node.first);

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
