#ifndef NETWORKTOOLS
#define NETWORKTOOLS

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <tuple>
#include "seqtools.hpp"
#include "kmertools.hpp"

using namespace std;

class Network
{

  set<string> node_set;
  set<tuple<string, string, int>> edge_set;

  public :

    void AddPair(string node1, string node2, int distance) {
      // add each node to the list and insert edge
      tuple<string, string, int> edge {node1, node2, distance};

      node_set.insert(node1);
      node_set.insert(node2);
      edge_set.insert(edge);

    }

    void WriteNetwork(string output_fn) {

      ofstream outfile;
      outfile.open(output_fn);


      outfile << "node1\tnode2\tdistance" << endl;
      for (auto & e : edge_set) {

        outfile << get<0>(e) << "\t" << get<1>(e) << "\t" << get<2>(e) << endl;

      }

      outfile.close();
    }

};

#endif
