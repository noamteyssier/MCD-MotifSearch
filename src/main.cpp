#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "utils/seqtools.hpp"
#include "utils/kmertools.hpp"
#include "utils/networktools.hpp"
using namespace std;

int main(int argc, char* argv[]){

  if (argc != 4) {
    cout
      << "Arguments Required : Input Fasta, Output Filename, Minimum Distance"
      << endl;

    return -1;
  }

  string input_fn = argv[1];
  string output_fn = argv[2];
  int minimum_distance = atoi(argv[3]);

  vector<KmerObj> kmer_vec = BuildKmerSet(input_fn);
  int num_records = kmer_vec.size();

  Network n;

  #pragma omp parallel
  for (int i = 0; i < num_records; i++){

    #pragma omp parallel
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
