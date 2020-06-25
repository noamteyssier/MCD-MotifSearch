
#include <fstream>
#include <mutex>
#include "networktools.h"



// NodeSet Class Functions

NodeSet::NodeSet()
{
  mutex = new std::mutex();
}


void NodeSet::AddNode(Node node_name)
{
  mutex->lock();
  node_set.insert(node_name);
  mutex->unlock();
}


const std::set<Node> NodeSet::GetSet()
{
  return node_set;
}


// Edge Class Functions

EdgeSet::EdgeSet()
{
  mutex = new std::mutex();
}

void EdgeSet::AddEdge(Edge e)
{
  mutex->lock();
  edge_set.insert(e);
  mutex->unlock();
}

const std::set<Edge> EdgeSet::GetSet()
{
  return edge_set;
}


// Network Class Functions

void Network::AddPair(Node node1, Node node2, int distance)
{
  Edge edge{node1, node2, distance};

  node_set.AddNode(node1);
  node_set.AddNode(node2);
  edge_set.AddEdge(edge);
}

void Network::WriteNetwork(std::string output_fn)
{
  std::ofstream outfile(output_fn, std::ofstream::out);

  outfile << "node1\tnode2\tdistance" << "\n";

  for (const auto & e : edge_set.GetSet()) {
    outfile << std::get<0>(e) << "\t" << std::get<1>(e) << "\t" << std::get<2>(e) << "\n";
  }

  outfile.close();
}
