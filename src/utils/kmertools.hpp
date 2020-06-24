#ifndef KMERTOOLS
#define KMERTOOLS

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <algorithm>
#include "seqtools.hpp"

using namespace std;


// Holds a Header, Sequence, and Kmer Set for a given kmer size
class KmerObj
{
  string header;
  string sequence;
  int kmer_size = 7;
  set<string> kmer_set;

  private :
    void build_set() {
      // Builds a set of unique kmers for a sequence
      int seq_size = sequence.length();

      for (int i = 0; i < seq_size - kmer_size + 1; i++){
        string kmer = sequence.substr(i, kmer_size);
        kmer_set.insert(kmer);
      }

    }

  public :

    KmerObj(string header, string sequence) :
      header(header), sequence(sequence) {
        build_set();
      }

    KmerObj(string header, string sequence, int kmer_size) :
      header(header), sequence(sequence), kmer_size(kmer_size) {
        build_set();
      }

    KmerObj(Record r) :
      header(r.header), sequence(r.sequence) {
        build_set();
      }

    KmerObj(Record r, int kmer_size) :
      header(r.header), sequence(r.sequence), kmer_size(kmer_size) {
        build_set();
      }

    set<string> get_kmerset() {
      return kmer_set;
    }

    string get_header() {
      return header;
    }

    void print() {
      // prints header, sequence, and kmerset
      cout << header << " : " << sequence << endl;

      for (auto & x : kmer_set){
        cout << x  << " ";
      }
      cout << endl;
    }
};

// Converts a vector of Records to a vector of KmerObjs
vector<KmerObj> Records_to_KmerObjs(vector<Record> record_vec){

  vector<KmerObj> kmer_vec;

  for (auto & record : record_vec){
    KmerObj kmerobj(record);
    kmer_vec.push_back(kmerobj);
  }

  return kmer_vec;

}

// Creates a kmer set for each record in a fasta file
vector<KmerObj> BuildKmerSet(string fn) {
  // Builds a kmer set from a file path

  ifstream fasta_stream(fn, std::ios_base::in);
  vector<Record> record_vec = read_stream(fasta_stream);
  vector<KmerObj> kmer_vec = Records_to_KmerObjs(record_vec);

  return kmer_vec;

}

//  Calculates the distance between two strings of equal length
int StringDist(string s1, string s2) {
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

// Calculates the minimum distance between two sets of kmers
int KmerDist(KmerObj k1, KmerObj k2) {
  // Returns the minimum distance between all kmer substrings

  set<int> string_distances;

  for (auto & s1 : k1.get_kmerset()) {

    for (auto & s2 : k2.get_kmerset()) {

      int strdist = StringDist(s1, s2);

      string_distances.insert(strdist);

    }
  }


  int minimum = *std::min_element(
    string_distances.begin(), string_distances.end()
  );

  return minimum;
}

#endif
