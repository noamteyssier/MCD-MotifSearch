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
  mutable std::mutex mutex;

public:
  void AddNode(Node node_name);
  const std::set<Node> GetSet();
};


class EdgeSet
{
private:
  std::set<Edge> edge_set;
  mutable std::mutex mutex;

public:
  void AddEdge(Edge e);
  const std::set<Edge> GetSet();
};


class Network
{
private:
  NodeSet node_set;
  EdgeSet edge_set;

public :
  void AddPair(Node node1, Node node2, int distance);
  void WriteNetwork(std::string output_fn);
};

#endif
