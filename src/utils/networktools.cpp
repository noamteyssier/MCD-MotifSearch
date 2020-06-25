#include <iostream>
#include <fstream>
#include <mutex>
#include "networktools.h"



/*-------------------------*/
// NodeSet Class Functions //
/*-------------------------*/

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

void NodeSet::Print()
{
  for (auto & x : node_set){
    std::cout << x << std::endl;
  }
}

NodeSet NodeSet::operator+(NodeSet& other_nodeset)
{
  NodeSet new_nodeset;

  for (const auto & n : this->node_set) {
    new_nodeset.AddNode(n);
  }


  for (const auto & n : other_nodeset.GetSet()) {
    new_nodeset.AddNode(n);
  }

  return new_nodeset;
}

/*-------------------------*/
// EdgeSet Class Functions //
/*-------------------------*/

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

void EdgeSet::Print()
{
  for (auto & x : edge_set){

    std::cout <<
      std::get<0>(x) << ", " <<
      std::get<1>(x) << ", " <<
      std::get<2>(x) << std::endl;
  }
}

int EdgeSet::GetSize()
{
  return edge_set.size();
}

EdgeSet EdgeSet::operator+(EdgeSet& other_edgeset)
{
  EdgeSet new_edgeset;

  for (const auto & e : this->edge_set) {
    new_edgeset.AddEdge(e);
  }


  for (const auto & e : other_edgeset.GetSet()) {
    new_edgeset.AddEdge(e);
  }

  return new_edgeset;
}

/*-------------------------*/
// Network Class Functions //
/*-------------------------*/

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
    outfile <<
      std::get<0>(e) << "\t" <<
      std::get<1>(e) << "\t" <<
      std::get<2>(e) << std::endl;
  }

  outfile.close();
}

void Network::WriteNetwork(std::ostream& stream)
{
  for (const auto & e : edge_set.GetSet())
  {
    stream <<
      std::get<0>(e) << "\t" <<
      std::get<1>(e) << "\t" <<
      std::get<2>(e) << std::endl;
  }
}

const NodeSet Network::GetNodes() const
{
  return node_set;
}

const EdgeSet Network::GetEdges() const
{
  return edge_set;
}

void Network::AddNodes(NodeSet& n)
{
  node_set = node_set + n;
}

void Network::AddEdges(EdgeSet& e)
{
  edge_set = edge_set + e;
}

void Network::PrintEdges()
{
  edge_set.Print();
}

int Network::GetSize()
{
  return edge_set.GetSize();
}

Network Network::operator+(Network& other_network)
{
  Network new_network;
  NodeSet other_nodes = other_network.GetNodes();
  EdgeSet other_edges = other_network.GetEdges();

  new_network.AddEdges(edge_set);
  new_network.AddEdges(other_edges);

  return new_network;
}
