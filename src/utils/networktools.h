#ifndef NETWORKTOOLS
#define NETWORKTOOLS

#include <string>
#include <set>
#include <tuple>
#include <mutex>

using Node = std::string;
using Edge = std::tuple<Node, Node, int>;


class NodeSet
{
private:
  std::set<Node> node_set;
  std::mutex * mutex;

public:
  NodeSet();
  void AddNode(Node node_name);
  const std::set<Node> GetSet();
  void Print();
  NodeSet operator+(NodeSet& other_nodeset);
};


class EdgeSet
{
private:
  std::set<Edge> edge_set;
  std::mutex * mutex;

public:
  EdgeSet();
  void AddEdge(Edge e);
  const std::set<Edge> GetSet();
  void Print();
  int GetSize();
  EdgeSet operator+(EdgeSet& other_edgeset);
};


class Network
{
private:
  NodeSet node_set;
  EdgeSet edge_set;

public :
  void AddPair(Node node1, Node node2, int distance);
  void WriteNetwork(std::string output_fn);
  void WriteNetwork(std::ostream& stream);
  const NodeSet GetNodes() const;
  const EdgeSet GetEdges() const;
  void AddNodes(NodeSet& n);
  void AddEdges(EdgeSet& e);
  void PrintEdges();
  int GetSize();
  Network operator+(Network& other_network);
};

#endif
