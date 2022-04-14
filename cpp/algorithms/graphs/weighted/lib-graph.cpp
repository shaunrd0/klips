/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example of a weighted graph implementation                       ##
##        Algorithms in this example are found in MIT Intro to Algorithms     ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "lib-graph.hpp"


InfoBFS Graph::BFS(const Node& startNode) const
{
  // Create local object to track the information gathered during traversal
  InfoBFS searchInfo;

  // Create a queue to visit discovered nodes in FIFO order
  std::queue<const Node *> visitQueue;

  // Mark the startNode as in progress until we finish checking adjacent nodes
  searchInfo[startNode.number].discovered = Gray;

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
      if (searchInfo[adjacent.first].discovered == White) {
        std::cout << "Found undiscovered adjacentNode: " << adjacent.first
                  << "\n";
        // Mark the adjacent node as in progress
        searchInfo[adjacent.first].discovered = Gray;
        searchInfo[adjacent.first].distance =
            searchInfo[thisNode->number].distance + 1;
        searchInfo[adjacent.first].predecessor =
            &GetNode(thisNode->number);

        // Add the discovered node the the visitQueue
        visitQueue.push(&GetNode(adjacent.first));
      }
    }
    // We are finished with this node and the adjacent nodes; Mark it discovered
    searchInfo[thisNode->number].discovered = Black;
  }

  // Return the information gathered from this search, JIC caller needs it
  return searchInfo;
}

std::deque<Node> Graph::PathBFS(const Node &start, const Node &finish) const
{
  // Store the path as copies of each node
  // + If the caller modifies these, it will not impact the graph's data
  std::deque<Node> path;

  InfoBFS searchInfo = BFS(start);
  const Node * next = searchInfo[finish.number].predecessor;
  bool isValid = false;
  do {
    // If we have reached the start node, we have found a valid path
    if (*next == Node(start)) isValid = true;

    // Add the node to the path as we check each node
    // + Use emplace_front to call the Node copy constructor
    path.emplace_front(*next);

    // Move to the next node
    next = searchInfo[next->number].predecessor;
  } while (next != nullptr);
  // Use emplace_back to call Node copy constructor
  path.emplace_back(finish);

  // If we never found a valid path, erase all contents of the path
  if (!isValid) path.erase(path.begin(), path.end());

  // Return the path, the caller should handle empty paths accordingly
  return path;
}

InfoDFS Graph::DFS() const
{
  // Track the nodes we have discovered
  InfoDFS searchInfo;
  int time = 0;

  // Visit each node in the graph
  for (const auto& node : nodes_) {
    std::cout << "Visiting node " << node.number << std::endl;
    // If the node is undiscovered, visit it
    if (searchInfo[node.number].discovered == White) {
      std::cout << "Found undiscovered node: " << node.number << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, node, searchInfo);
    }
  }

  return searchInfo;
}

InfoDFS Graph::DFS(const Node &startNode) const
{
  // Track the nodes we have discovered
  InfoDFS searchInfo;
  int time = 0;

  auto startIter = std::find(nodes_.begin(), nodes_.end(),
                             Node(startNode.number, {})
  );

  // beginning at startNode, visit each node in the graph until we reach the end
  while (startIter != nodes_.end()) {
    std::cout << "Visiting node " << startIter->number << std::endl;
    // If the startIter is undiscovered, visit it
    if (searchInfo[startIter->number].discovered == White) {
      std::cout << "Found undiscovered node: " << startIter->number << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, *startIter, searchInfo);
    }
    startIter++;
  }

  // Once we reach the last node, check the beginning for unchecked nodes
  startIter = nodes_.begin();

  // Once we reach the initial startNode, we have checked all nodes
  while (*startIter != startNode) {
    std::cout << "Visiting node " << startIter->number << std::endl;
    // If the startIter is undiscovered, visit it
    if (searchInfo[startIter->number].discovered == White) {
      std::cout << "Found undiscovered node: " << startIter->number << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, *startIter, searchInfo);
    }
    startIter++;
  }

  return searchInfo;
}

void Graph::DFSVisit(int &time, const Node& startNode, InfoDFS &searchInfo) const
{
  searchInfo[startNode.number].discovered = Gray;
  time++;
  searchInfo[startNode.number].discoveryFinish.first = time;

  // Check the adjacent nodes of the startNode
  for (const auto &adjacent : startNode.adjacent) {
    auto iter = std::find(nodes_.begin(), nodes_.end(),
                          Node(adjacent.first, {}));
    // If the adjacentNode is undiscovered, visit it
    // + Offset by 1 to account for 0 index of discovered vector
    if (searchInfo[iter->number].discovered == White) {
      std::cout << "Found undiscovered adjacentNode: "
                << GetNode(adjacent.first).number << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, *iter, searchInfo);
    }
  }
  searchInfo[startNode.number].discovered = Black;
  time++;
  searchInfo[startNode.number].discoveryFinish.second = time;
}

std::vector<Node> Graph::TopologicalSort(const Node &startNode) const
{
  InfoDFS topological = DFS(GetNode(startNode.number));

  std::vector<Node> order(nodes_);

  auto comp = [&topological](const Node &a, const Node &b) {
    return (topological[a.number].discoveryFinish.second <
      topological[b.number].discoveryFinish.second);
  };

  std::sort(order.begin(), order.end(), comp);

  // The topologicalOrder is read right-to-left in the final result
  // + Output is handled in main as FILO, similar to a stack
  return order;
}

InfoMST Graph::KruskalMST() const
{
  InfoMST searchInfo(nodes_);
  // The ctor for InfoMST initializes all edges within the graph into a multimap
  // + Key for multimap is edge weight, so they're already sorted in ascending

  // For each edge in the graph, check if they are part of the same tree
  // + Since we do not want to create a cycle in the MST forest -
  // + we don't connect nodes that are part of the same tree
  for (const auto &edge : searchInfo.edges) {
    // Two integers representing the node.number for the connected nodes
    const int u = edge.second.first;
    const int v = edge.second.second;
    // Check if the nodes are of the same tree
    if (searchInfo.FindSet(u) != searchInfo.FindSet(v)) {
      // If they are not, add the edge to our MST
      searchInfo.edgesMST.emplace(edge);
      searchInfo.weightMST += edge.first;
      // Update the forest to reflect this change
      searchInfo.Union(u, v);
    }
  }

  return searchInfo;
}
