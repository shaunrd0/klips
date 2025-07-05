/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example of a templated object graph implementation               ##
##        Algorithms in this example are found in MIT Intro to Algorithms     ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/
#ifndef LIB_GRAPH_HPP
#define LIB_GRAPH_HPP

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cstdint>


/******************************************************************************/
// Node structure for representing a graph

template <typename T>
struct Node {
public:
  template <typename> friend class Graph;
  template <typename> friend class InfoMST;

  // Constructors
  Node(const Node &rhs) = default;
  Node & operator=(Node rhs)
  {
    if (this == &rhs) return *this;
    swap(*this, rhs);
    return *this;
  }
  Node(T data, const std::vector<std::pair<T, int>> &adj) : data_(data)
  {
    // Place each adjacent node in vector into our unordered_map of edges
    for (const auto &i : adj) adjacent_.emplace(i.first, i.second);
  }

  friend void swap(Node &a, Node &b)
  {
    std::swap(a.data_, b.data_);
    std::swap(a.adjacent_, b.adjacent_);
  }

  // Operators
  // Define operator== for std::find; And comparisons between nodes
  bool operator==(const Node<T> &b) const { return this->data_ == b.data_;}
  // Define an operator!= for comparing nodes for inequality
  bool operator!=(const Node<T> &b) const { return this->data_ != b.data_;}

  // Accessors
  inline T GetData() const { return data_;}
  inline std::unordered_map<int, int> GetAdjacent() const { return adjacent_;}

private:
  T data_;
  // Adjacent stored in an unordered_map<adj.number, edgeWeight>
  std::unordered_map<T, int> adjacent_;
};


/******************************************************************************/
// Base struct for storing traversal information on all nodes

// Color represents the discovery status of any given node
enum Color {
  // Node is marked as undiscovered
  White,
  // Node discovery is in progress; Some adjacent nodes have not been checked
  Gray,
  // Node has been discovered; All adjacent nodes have been checked
  Black
};

// Information used in all searches tracked for each node
struct NodeInfo {
  // Coloring of the nodes is used in both DFS and BFS
  Color discovered = White;
};


/******************************************************************************/
// BFS search information struct

// Node information that is only used in BFS
template <typename T>
struct BFS : NodeInfo {
  // Used to represent distance from start node
  int distance = 0;
  // Used to represent the parent node that discovered this node
  // + If we use this node as the starting point, this will remain a nullptr
  const Node<T> *predecessor = nullptr;
};

// Store search information in unordered_maps so we can pass it around easily
// + Allows each node to store relative information on the traversal
template <typename T> using InfoBFS = std::unordered_map<T, struct BFS<T>>;


/******************************************************************************/
// DFS search information struct

// Node information that is only used in DFS
struct DFS : NodeInfo {
  // Create a pair to track discovery / finish time
  // + Discovery time is the iteration the node is first discovered
  // + Finish time is the iteration the node has been checked completely
  // ++ A finished node has considered all adjacent nodes
  std::pair<int, int> discoveryFinish;
};

template <typename T> using InfoDFS = std::unordered_map<T, struct DFS>;


/******************************************************************************/
// MST search information struct

// Edges stored as multimap<weight, pair<nodeA.data_, nodeB.data_>>
template <typename T> using Edges = std::multimap<int, std::pair<T, T>>;

struct MST : NodeInfo {
  int32_t parent = INT32_MIN;
  int rank = 0;
};

template <typename T>
struct InfoMST {
  template <typename> friend class Graph;

  explicit InfoMST(const std::vector<Node<T>> &nodes)
  {
    for (const auto &node : nodes) {
      // Initialize the default values for forest tracked by this struct
      // + This data is used in KruskalMST() to find the MST
      MakeSet(node.data_);
      for (const auto adj : node.adjacent_) {
        // node.number is the number that represents this node
        // adj.first is the node number that is connected to this node
        // adj.second is the weight of the connected edge
        edges_.emplace(adj.second, std::make_pair(node.data_, adj.first));
        // So we initialize the multimap<weight, <nodeA.number, nodeB.number>>
        // + Since a multimap sorts by key, we have sorted our edges by weight
      }
    }
  }

  void Print()
  {
    std::cout << "MST result: \n";
    for (const auto &edge : edgesMST_) {
      std::cout << "Connected nodes: " << edge.second.first << "->"
                << edge.second.second << " with weight of " << edge.first << "\n";
    }
    std::cout << "Total MST weight: " << weightMST_ << std::endl;
  }

  void MakeSet(T x)
  {
    searchInfo[x].parent = x;
    searchInfo[x].rank = 0;
  }

  void Union(T x, T y)
  {
    Link(FindSet(x), FindSet(y));
  }

  void Link(T x, T y)
  {
    if (searchInfo[x].rank > searchInfo[y].rank) {
      searchInfo[y].parent = x;
    }
    else {
      searchInfo[x].parent = y;
      if (searchInfo[x].rank == searchInfo[y].rank) {
        searchInfo[y].rank += 1;
      }
    }
  }

  T FindSet(T x)
  {
    if (x != searchInfo[x].parent) {
      searchInfo[x].parent = FindSet(searchInfo[x].parent);
    }
    return searchInfo[x].parent;
  }

private:
  std::unordered_map<T, struct MST> searchInfo;
  // All of the edges within our graph
  // + Since each node stores its own edges, this is initialized in InfoMST ctor
  Edges<T> edges_;

  // A multimap of the edges found for our MST
  Edges<T> edgesMST_;
  // The total weight of our resulting MST
  int weightMST_ = 0;
};


/******************************************************************************/
// Templated graph class

template <class T>
class Graph {
public:
  // Constructor
  explicit Graph(std::vector<Node<T>> nodes) : nodes_(std::move(nodes)) {}

  // Breadth First Search
  InfoBFS<T> BFS(const Node<T>& startNode) const;

  std::deque<Node<T>> PathBFS(const Node<T> &start, const Node<T> &finish) const;

  // Depth First Search
  InfoDFS<T> DFS() const;
  // An alternate DFS that checks each node of the graph beginning at startNode
  InfoDFS<T> DFS(const Node<T> &startNode) const;
  // Visit function is used in both versions of DFS
  void DFSVisit(int &time, const Node<T>& startNode, InfoDFS<T> &searchInfo) const;
  // Topological sort, using DFS
  std::vector<Node<T>> TopologicalSort(const Node<T> &startNode) const;
  // Kruskal's MST
  InfoMST<T> KruskalMST() const;

  // Returns a copy of a node with the number i within the graph
  // + This uses the private, non-const accessor GetNode() and returns a copy
  inline Node<T> GetNodeCopy(T i) { return GetNode(i);}
  // Return a constant iterator for reading node values
  inline typename std::vector<Node<T>>::const_iterator NodeBegin()
  { return nodes_.cbegin();}

private:
  // A non-const accessor for direct access to a node with the number value i
  inline Node<T> & GetNode(T i)
  { return *std::find(nodes_.begin(), nodes_.end(), Node<T>(i, {}));}
  // For grabbing a const qualified node
  inline const Node<T> & GetNode(T i) const
  { return *std::find(nodes_.begin(), nodes_.end(), Node<T>(i, {}));}

  std::vector<Node<T>> nodes_;
};


/******************************************************************************/
// Graph class member function definitions

template <typename T>
InfoBFS<T> Graph<T>::BFS(const Node<T> &startNode) const
{
  // Create local object to track the information gathered during traversal
  InfoBFS<T> searchInfo;

  // Create a queue to visit discovered nodes in FIFO order
  std::queue<const Node<T> *> visitQueue;

  // Mark the startNode as in progress until we finish checking adjacent nodes
  searchInfo[startNode.data_].discovered = Gray;

  // Visit the startNode
  visitQueue.push(&startNode);

  // Continue to visit nodes until there are none left in the graph
  while (!visitQueue.empty()) {
    // Remove thisNode from the visitQueue, storing its vertex locally
    const Node<T> * thisNode = visitQueue.front();
    visitQueue.pop();
    std::cout << "Visiting node " << thisNode->data_ << std::endl;

    // Check if we have already discovered all the adjacentNodes to thisNode
    for (const auto &adjacent : thisNode->adjacent_) {
      if (searchInfo[adjacent.first].discovered == White) {
        std::cout << "Found undiscovered adjacentNode: " << adjacent.first
                  << "\n";
        // Mark the adjacent node as in progress
        searchInfo[adjacent.first].discovered = Gray;
        searchInfo[adjacent.first].distance =
            searchInfo[thisNode->data_].distance + 1;
        searchInfo[adjacent.first].predecessor =
            &GetNode(thisNode->data_);

        // Add the discovered node the the visitQueue
        visitQueue.push(&GetNode(adjacent.first));
      }
    }
    // We are finished with this node and the adjacent nodes; Mark it discovered
    searchInfo[thisNode->data_].discovered = Black;
  }

  // Return the information gathered from this search, JIC caller needs it
  return searchInfo;
}

template <typename T>
std::deque<Node<T>> Graph<T>::PathBFS(const Node<T> &start,
                                      const Node<T> &finish) const
{
  // Store the path as copies of each node
  // + If the caller modifies these, it will not impact the graph's data
  std::deque<Node<T>> path;

  InfoBFS<T> searchInfo = BFS(start);
  const Node<T> * next = searchInfo[finish.data_].predecessor;
  bool isValid = false;
  do {
    // If we have reached the start node, we have found a valid path
    if (*next == Node<T>(start)) isValid = true;

    // Add the node to the path as we check each node
    // + Use emplace_front to call the Node copy constructor
    path.emplace_front(*next);

    // Move to the next node
    next = searchInfo[next->data_].predecessor;
  } while (next != nullptr);
  // Use emplace_back to call Node copy constructor
  path.emplace_back(finish);

  // If we never found a valid path, erase all contents of the path
  if (!isValid) path.erase(path.begin(), path.end());

  // Return the path, the caller should handle empty paths accordingly
  return path;
}

template <typename T>
InfoDFS<T> Graph<T>::DFS() const
{
  // Track the nodes we have discovered
  InfoDFS<T> searchInfo;
  int time = 0;

  // Visit each node in the graph
  for (const auto& node : nodes_) {
    std::cout << "Visiting node " << node.data_ << std::endl;
    // If the node is undiscovered, visit it
    if (searchInfo[node.data_].discovered == White) {
      std::cout << "Found undiscovered node: " << node.data_ << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, node, searchInfo);
    }
  }

  return searchInfo;
}

template <typename T>
InfoDFS<T> Graph<T>::DFS(const Node<T> &startNode) const
{
  // Track the nodes we have discovered
  InfoDFS<T> searchInfo;
  int time = 0;

  auto startIter = std::find(nodes_.begin(), nodes_.end(),
                             Node<T>(startNode.data_, {})
  );

  // beginning at startNode, visit each node in the graph until we reach the end
  while (startIter != nodes_.end()) {
    std::cout << "Visiting node " << startIter->data_ << std::endl;
    // If the startIter is undiscovered, visit it
    if (searchInfo[startIter->data_].discovered == White) {
      std::cout << "Found undiscovered node: " << startIter->data_ << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, *startIter, searchInfo);
    }
    startIter++;
  }

  // Once we reach the last node, check the beginning for unchecked nodes
  startIter = nodes_.begin();

  // Once we reach the initial startNode, we have checked all nodes
  while (*startIter != startNode) {
    std::cout << "Visiting node " << startIter->data_ << std::endl;
    // If the startIter is undiscovered, visit it
    if (searchInfo[startIter->data_].discovered == White) {
      std::cout << "Found undiscovered node: " << startIter->data_ << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, *startIter, searchInfo);
    }
    startIter++;
  }

  return searchInfo;
}

template <typename T>
void Graph<T>::DFSVisit(int &time, const Node<T>& startNode,
                        InfoDFS<T> &searchInfo) const
{
  searchInfo[startNode.data_].discovered = Gray;
  time++;
  searchInfo[startNode.data_].discoveryFinish.first = time;

  // Check the adjacent nodes of the startNode
  for (const auto &adjacent : startNode.adjacent_) {
    auto iter = std::find(nodes_.begin(), nodes_.end(),
                          Node<T>(adjacent.first, {}));
    // If the adjacentNode is undiscovered, visit it
    // + Offset by 1 to account for 0 index of discovered vector
    if (searchInfo[iter->data_].discovered == White) {
      std::cout << "Found undiscovered adjacentNode: "
                << GetNode(adjacent.first).data_ << std::endl;
      // Visiting the undiscovered node will check it's adjacent nodes
      DFSVisit(time, *iter, searchInfo);
    }
  }
  searchInfo[startNode.data_].discovered = Black;
  time++;
  searchInfo[startNode.data_].discoveryFinish.second = time;
}

template <typename T>
std::vector<Node<T>> Graph<T>::TopologicalSort(const Node<T> &startNode) const
{
  InfoDFS<T> topological = DFS(GetNode(startNode.data_));

  std::vector<Node<T>> order(nodes_);

  auto comp = [&topological](const Node<T> &a, const Node<T> &b) {
    return (topological[a.data_].discoveryFinish.second <
            topological[b.data_].discoveryFinish.second);
  };

  std::sort(order.begin(), order.end(), comp);

  // The topologicalOrder is read right-to-left in the final result
  // + Output is handled in main as FILO, similar to a stack
  return order;
}

template <typename T>
InfoMST<T> Graph<T>::KruskalMST() const
{
  InfoMST<T> searchInfo(nodes_);
  // The ctor for InfoMST initializes all edges within the graph into a multimap
  // + Key for multimap is edge weight, so they're already sorted in ascending

  // For each edge in the graph, check if they are part of the same tree
  // + Since we do not want to create a cycle in the MST forest -
  // + we don't connect nodes that are part of the same tree
  for (const auto &edge : searchInfo.edges_) {
    // Two integers representing the node.number for the connected nodes
    const int u = edge.second.first;
    const int v = edge.second.second;
    // Check if the nodes are of the same tree
    if (searchInfo.FindSet(u) != searchInfo.FindSet(v)) {
      // If they are not, add the edge to our MST
      searchInfo.edgesMST_.emplace(edge);
      searchInfo.weightMST_ += edge.first;
      // Update the forest to reflect this change
      searchInfo.Union(u, v);
    }
  }

  return searchInfo;
}

#endif // LIB_GRAPH_HPP
