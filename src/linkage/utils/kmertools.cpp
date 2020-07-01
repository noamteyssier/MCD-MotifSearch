#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#include "kmertools.h"


// KmerObj Class Methods

KmerObj::KmerObj(std::string header, std::string sequence) : header(header), sequence(sequence)
{
  build_set();
}


KmerObj::KmerObj(std::string header, std::string sequence, int kmer_size) : header(header), sequence(sequence), kmer_size(kmer_size)
{
  build_set();
};


KmerObj::KmerObj(Record r) : KmerObj(r.header, r.sequence) {};


KmerObj::KmerObj(Record r, int kmer_size) : KmerObj(r.header, r.sequence, kmer_size) {};


void KmerObj::build_set()
{
  // Builds a set of all kmers for a sequence
  const int seq_size = sequence.length();
  const int array_size = seq_size - kmer_size + 1;

  // std::vector<std::string> kmer_array;
  kmer_vec.reserve(array_size);

  for (int i = 0; i < array_size; i++)
  {
    std::string kmer = sequence.substr(i, kmer_size);
    kmer_vec.push_back(kmer);
  }

}

const std::vector<std::string>& KmerObj::get_kmervec() const
{
  return kmer_vec;
}

const std::string KmerObj::get_header() const
{
  return header;
}

void KmerObj::print()
{
  // prints header, sequence, and kmerset
  std::cout << header << " : " << sequence << '\n';

  for (auto & x : kmer_vec)
  {
    std::cout << x  << " ";
  }
  std::cout << '\n';
}


// Functional methods


// Converts a vector of Records to a vector of KmerObjs
std::vector<KmerObj> Records_to_KmerObjs(std::vector<Record> record_vec)
{

  std::vector<KmerObj> kmer_vec;

  for (const auto & record : record_vec)
  {
    kmer_vec.emplace_back(record);
  }

  return kmer_vec;

}

// Creates a kmer set for each record in a fasta file
std::vector<KmerObj> BuildKmerSet(std::string fn)
{
  // Builds a kmer set from a file path

  std::ifstream fasta_stream(fn, std::ios_base::in);
  std::vector<Record> record_vec = read_stream(fasta_stream);
  std::vector<KmerObj> kmer_vec = Records_to_KmerObjs(record_vec);

  return kmer_vec;

}

//  Calculates the distance between two strings of equal length
int StringDist(const std::string& s1, const std::string& s2) {
  // int strlen = s1.length();
  // int dist = strlen;
  // int strlen = 7;
  int dist = 7;

  for (int i = 0; i < 7; i++) {

    if (s1[i] == s2[i]){
      dist--;
    }

  }

  return dist;
}

int KmerDist(KmerObj k1, KmerObj k2)
{
  std::set<int> string_distances;

  for (const auto & s1 : k1.get_kmervec()) {

    for (const auto & s2 : k2.get_kmervec()) {

      int strdist = StringDist(s1, s2);

      string_distances.insert(strdist);

    }
  }

  // returns first element of ordered set
  int minimum = *std::next(string_distances.begin(), 0);

  return minimum;
}

// Calculates the minimum distance between two sets of kmers
int KmerDist(KmerObj k1, KmerObj k2, int minimum_distance)
{
  // Returns the minimum distance between all kmer substrings

  // std::set<int> string_distances;
  int strdist;
  int current_minimum = 1000;

  for (const auto & s1 : k1.get_kmervec()) {

    for (const auto & s2 : k2.get_kmervec()) {

      strdist = StringDist(s1, s2);

      if (strdist <= minimum_distance) {
        return strdist;
      }
      else if (strdist < current_minimum) {
        current_minimum = strdist;
      }

    }
  }

  return current_minimum;
}
