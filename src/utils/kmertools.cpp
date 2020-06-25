#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#include "kmertools.h"


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
  // Builds a set of unique kmers for a sequence
  int seq_size = sequence.length();

  for (int i = 0; i < seq_size - kmer_size + 1; i++) 
  {
    std::string kmer = sequence.substr(i, kmer_size);
    kmer_set.insert(kmer);
  }
}

std::set<std::string> KmerObj::get_kmerset() 
{
  return kmer_set;
}

std::string KmerObj::get_header() 
{
  return header;
}

void KmerObj::print() 
{
  // prints header, sequence, and kmerset
  std::cout << header << " : " << sequence << '\n';

  for (auto & x : kmer_set)
  {
    std::cout << x  << " ";
  }
  std::cout << '\n';
}


// Converts a vector of Records to a vector of KmerObjs
std::vector<KmerObj> Records_to_KmerObjs(std::vector<Record> record_vec) 
{

  std::vector<KmerObj> kmer_vec;

  for (const auto & record : record_vec) 
  {
    KmerObj kmerobj(record);
    kmer_vec.push_back(kmerobj);
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
int StringDist(std::string s1, std::string s2) {
  // distance between two strings of same length
  int strlen = s1.length();
  int dist = strlen;

  for (int i = 0; i < strlen; i++) {
    if (s1[i] == s2[i]){
      dist--;
    }
  }

  return dist;
}

int KmerDist(KmerObj k1, KmerObj k2) 
{
  std::set<int> string_distances;

  for (const auto & s1 : k1.get_kmerset()) {

    for (const auto & s2 : k2.get_kmerset()) {

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

  std::set<int> string_distances;

  for (auto & s1 : k1.get_kmerset()) {

    for (auto & s2 : k2.get_kmerset()) {

      int strdist = StringDist(s1, s2);

      string_distances.insert(strdist);

      if (strdist <= minimum_distance) {
        return strdist;
      }

    }
  }

  // returns first element of ordered set
  int minimum = *std::next(string_distances.begin(), 0);

  return minimum;
}



