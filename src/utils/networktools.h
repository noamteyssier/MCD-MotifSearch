#ifndef NETWORKTOOLS
#define NETWORKTOOLS

#include <string>
#include <set>
#include <tuple>

using Node = std::string;
using Edge = std::tuple<Node, Node, int>;


class NodeSet
{
private:
  std::set<Node> node_set;

public:
  void AddNode(Node node_name);
  const std::set<Node> GetSet();
};


class EdgeSet
{
private:
  std::set<Edge> edge_set;

public:
  void AddEdge(Edge e);
  const std::set<Edge> GetSet();
};


class Network
{
public :
  void AddPair(Node node1, Node node2, int distance);
  void WriteNetwork(std::string output_fn);

private:
  NodeSet node_set;
  EdgeSet edge_set;
};

#endif
