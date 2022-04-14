/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example of a weighted graph implementation                       ##
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


/******************************************************************************/
// Node structure for representing a graph

struct Node {
public:
  // Constructors
  Node(const Node &rhs) = default;
  Node & operator=(Node rhs)
  {
    if (this == &rhs) return *this;
    swap(*this, rhs);
    return *this;
  }
  Node(int num, const std::vector<std::pair<int, int>> &adj) : number(num)
  {
    // Place each adjacent node in vector into our unordered_map of edges
    for (const auto &i : adj) adjacent.emplace(i.first, i.second);
  }

  friend void swap(Node &a, Node &b)
  {
    std::swap(a.number, b.number);
    std::swap(a.adjacent, b.adjacent);
  }

  int number;
  // Adjacent stored in an unordered_map<adj.number, edgeWeight>
  std::unordered_map<int, int> adjacent;

  // Define operator== for std::find; And comparisons between nodes
  bool operator==(const Node &b) const { return this->number == b.number;}
  // Define an operator!= for comparing nodes for inequality
  bool operator!=(const Node &b) const { return this->number != b.number;}
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

// Template for tracking graph information gathered during traversals
// + Used for DFS, BFS, and MST
template <typename T>
struct GraphInfo {
  // Store search information in unordered_maps so we can pass it around easily
  // + Allows each node to store relative information on the traversal
  std::unordered_map<int, T> nodeInfo;
  // Track total weight for all traversals
  int totalWeight = 0;
};


/******************************************************************************/
// BFS search information struct

// Node search information that is only used in BFS
struct BFS : NodeInfo {
  // Used to represent distance from start node
  int distance = 0;
  // Used to represent the parent node that discovered this node
  // + If we use this node as the starting point, this will remain a nullptr
  const Node *predecessor = nullptr;
};

struct InfoBFS : GraphInfo<BFS> {/* Members inherited from GraphInfo */};


/******************************************************************************/
// DFS search information struct

// Information that is only used in DFS
struct DFS : NodeInfo {
  // Create a pair to track discovery / finish time
  // + Discovery time is the iteration the node is first discovered
  // + Finish time is the iteration the node has been checked completely
  // ++ A finished node has considered all adjacent nodes
  std::pair<int, int> discoveryFinish;
};

struct InfoDFS : GraphInfo<DFS> {/* Members inherited from GraphInfo */};


/******************************************************************************/
// MST search information struct

struct MST : NodeInfo {
  int32_t parent = INT32_MIN;
  int rank = 0;
};

using Edges = std::multimap<int, std::pair<int, int>>;
struct InfoMST : GraphInfo<MST>{
  explicit InfoMST(const std::vector<Node> &nodes)
  {
    for (const auto &node : nodes) {
      // Initialize the default values for forest tracked by this struct
      // + This data is used in KruskalMST() to find the MST
      MakeSet(node.number);
      for (const auto adj : node.adjacent) {
        // node.number is the number that represents this node
        // adj.first is the node number that is connected to this node
        // adj.second is the weight of the connected edge
        edges.emplace(adj.second, std::make_pair(node.number, adj.first));
        // So we initialize the multimap<weight, <nodeA.number, nodeB.number>>
        // + Since a multimap sorts by key, we have sorted our edges by weight
      }
    }
  }

  // All of the edges within our graph
  // + Since each node stores its own edges, this is initialized in InfoMST ctor
  Edges edges;

  // A multimap of the edges found for our MST
  Edges edgesMST;

  void MakeSet(int x)
  {
    nodeInfo[x].parent = x;
    nodeInfo[x].rank = 0;
  }

  void Union(int x, int y)
  {
    Link(FindSet(x), FindSet(y));
  }

  void Link(int x, int y)
  {
    if (nodeInfo[x].rank > nodeInfo[y].rank) {
      nodeInfo[y].parent = x;
    }
    else {
      nodeInfo[x].parent = y;
      if (nodeInfo[x].rank == nodeInfo[y].rank) {
        nodeInfo[y].rank += 1;
      }
    }
  }

  int FindSet(int x)
  {
    if (x != nodeInfo[x].parent) {
      nodeInfo[x].parent = FindSet(nodeInfo[x].parent);
    }
    return nodeInfo[x].parent;
  }
};


/******************************************************************************/
// Graph class declaration

class Graph {
public:
  // Constructor
  explicit Graph(std::vector<Node> nodes) : nodes_(std::move(nodes)) {}

  // Breadth First Search
  InfoBFS BFS(const Node& startNode) const;
  std::deque<Node> PathBFS(const Node &start, const Node &finish) const;

  // Depth First Search
  InfoDFS DFS() const;
  // An alternate DFS that checks each node of the graph beginning at startNode
  InfoDFS DFS(const Node &startNode) const;
  // Visit function is used in both versions of DFS
  void DFSVisit(int &time, const Node& startNode, InfoDFS &dfs) const;
  // Topological sort, using DFS
  std::vector<Node> TopologicalSort(const Node &startNode) const;
  // Kruskal's MST
  InfoMST KruskalMST() const;

  // Returns a copy of a node with the number i within the graph
  // + This uses the private, non-const accessor GetNode() and returns a copy
  inline Node GetNodeCopy(int i) { return GetNode(i);}
  // Return a constant iterator for reading node values
  inline std::vector<Node>::const_iterator NodeBegin() { return nodes_.cbegin();}

private:
  // A non-const accessor for direct access to a node with the number value i
  inline Node & GetNode(int i)
  { return *std::find(nodes_.begin(), nodes_.end(), Node(i, {}));}
  // For grabbing a const qualified node
  inline const Node & GetNode(int i) const
  { return *std::find(nodes_.begin(), nodes_.end(), Node(i, {}));}

  std::vector<Node> nodes_;
};

#endif // LIB_GRAPH_HPP
