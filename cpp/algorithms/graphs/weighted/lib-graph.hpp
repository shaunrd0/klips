/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: An example of an object graph implementation                        ##
##        Algorithms in this example are found in MIT Intro to Algorithms     ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/
#ifndef LIB_GRAPH_HPP
#define LIB_GRAPH_HPP

#include <iostream>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>


/******************************************************************************/
// Structures for tracking information gathered from various traversals
struct Node;
// Color represents the discovery status of any given node
// + White is undiscovered, Gray is in progress, Black is fully discovered
enum Color {White, Gray, Black};

// Information used in all searches
struct SearchInfo {
  // Coloring of the nodes is used in both DFS and BFS
  Color discovered = White;
};

// Information that is only used in BFS
struct BFS : SearchInfo {
  // Used to represent distance from start node
  int distance = 0;
  // Used to represent the parent node that discovered this node
  // + If we use this node as the starting point, this will remain a nullptr
  const Node *predecessor = nullptr;
};

// Information that is only used in DFS
struct DFS : SearchInfo {
  // Create a pair to track discovery / finish time
  // + Discovery time is the iteration the node is first discovered
  // + Finish time is the iteration the node has been checked completely
  // ++ A finished node has considered all adjacent nodes
  std::pair<int, int> discoveryFinish;
};

struct MST : SearchInfo {
  int32_t parent = INT32_MIN;
  int rank = 0;
};

// Store search information in unordered_maps so we can pass it around easily
// + Allows each node to store relative information on the traversal
using InfoBFS = std::unordered_map<int, struct BFS>;
using InfoDFS = std::unordered_map<int, struct DFS>;


/******************************************************************************/
// Node structure for representing a graph

struct Node {
public:
  // Constructors
  Node(const Node &rhs) = default;
  Node & operator=(Node rhs) {
    if (this == &rhs) return *this;
    swap(*this, rhs);
    return *this;
  }
  Node(int num, const std::vector<std::pair<int, int>> &adj) : number(num)
  {
    // Place each adjacent node in vector into our unordered_map of edges
    for (const auto &i : adj) adjacent.emplace(i.first, i.second);
  }

  friend void swap(Node &a, Node &b) {
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

using Edges = std::multimap<int, std::pair<int, int>>;
struct InfoMST {
  explicit InfoMST(const std::vector<Node> &nodes) {
    for (const auto &node : nodes){
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

  std::unordered_map<int, struct MST> searchInfo;
  // All of the edges within our graph
  // + Since each node stores its own edges, this is initialized in InfoMST ctor
  Edges edges;

  // A multimap of the edges found for our MST
  Edges edgesMST;
  // The total weight of our resulting MST
  int weightMST = 0;

  void MakeSet(int x)
  {
    searchInfo[x].parent = x;
    searchInfo[x].rank = 0;
  }

  void Union(int x, int y)
  {
    Link(FindSet(x), FindSet(y));
  }

  void Link(int x, int y)
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

  int FindSet(int x)
  {
    if (x != searchInfo[x].parent) {
      searchInfo[x].parent = FindSet(searchInfo[x].parent);
    }
    return searchInfo[x].parent;
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
  void DFSVisit(int &time, const Node& startNode, InfoDFS &searchInfo) const;
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
