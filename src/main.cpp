
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "utils/seqtools.h"
#include "utils/kmertools.h"
#include "utils/networktools.h"


int main(int argc, char* argv[]){

  if (argc != 4) {
    std::cout
      << "Arguments Required : Input Fasta, Output Filename, Minimum Distance"
      << std::endl;

    return -1;
  }

  std::string input_fn = argv[1];
  std::string output_fn = argv[2];
  int minimum_distance = atoi(argv[3]);

  std::vector<KmerObj> kmer_vec = BuildKmerSet(input_fn);
  int num_records = kmer_vec.size();
  std::mutex mtx;


  std::vector<Network> NetworkVec;

  #pragma omp parallel for
  for (int i = 0; i < num_records; i++){
    Network n;

    for (int j = i + 1; j < num_records; j++){

      int min_dist = KmerDist(kmer_vec[i], kmer_vec[j], minimum_distance);

      if (min_dist <= minimum_distance) {

        n.AddPair(kmer_vec[i].get_header(), kmer_vec[j].get_header(), min_dist);

      }

    }

    // only append to vector if edges are found
    if (n.GetSize() > 0){
      mtx.lock();
      NetworkVec.push_back(n);
      mtx.unlock();
    }

  }


  std::ofstream outfile(output_fn, std::ofstream::out);
  outfile << "node1\tnode2\tdistance" << "\n";

  for (auto & n : NetworkVec)
  {
    n.WriteNetwork(outfile);
    outfile << "----" << std::endl;
  }

  outfile.close();


  return 0;
}
