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
};

#endif
