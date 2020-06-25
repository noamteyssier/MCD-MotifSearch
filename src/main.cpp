
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

  Network n;

  // #pragma omp parallel for
  for (int i = 0; i < num_records; i++){

    for (int j = i + 1; j < num_records; j++){

      int min_dist = KmerDist(kmer_vec[i], kmer_vec[j], minimum_distance);

      if (min_dist <= minimum_distance) {

        n.AddPair(
          kmer_vec[i].get_header(), kmer_vec[j].get_header(), min_dist
        );
      }
    }

  }

  n.WriteNetwork(output_fn);

  return 0;
}
