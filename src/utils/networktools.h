#ifndef NETWORKTOOLS
#define NETWORKTOOLS

#include <string>
#include <set>
#include <tuple>

using Node = std::string;
using Edge = std::tuple<Node, Node, int>;

class Network
{
public :
  void AddPair(Node node1, Node node2, int distance);
  void WriteNetwork(std::string output_fn);

private:
  std::set<Node> node_set{};
  std::set<Edge> edge_set{};
};

#endif