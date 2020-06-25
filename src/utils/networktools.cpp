
#include <fstream>

#include "networktools.h"

void Network::AddPair(Node node1, Node node2, int distance)
{
  Edge edge{node1, node2, distance};

  node_set.insert(node1);
  node_set.insert(node2);
  edge_set.insert(edge);
}

void Network::WriteNetwork(std::string output_fn)
{
  std::ofstream outfile(output_fn, std::ofstream::out);
  
  outfile << "node1\tnode2\tdistance" << "\n";
  
  for (const auto & e : edge_set) {
    outfile << std::get<0>(e) << "\t" << std::get<1>(e) << "\t" << std::get<2>(e) << "\n";
  }
  
  outfile.close();
}
