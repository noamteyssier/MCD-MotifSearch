#ifndef KMERTOOLS
#define KMERTOOLS

#include <set>

#include "seqtools.h"

class KmerObj
{
public :

    KmerObj(std::string header, std::string sequence);

    KmerObj(std::string header, std::string sequence, int kmer_size);

    KmerObj(Record r);

    KmerObj(Record r, int kmer_size);

    const std::vector<std::string>& get_kmervec() const;

    const std::string get_header() const;

    void print();

private:
    const std::string header;
    const std::string sequence;
    const int kmer_size = 7;
    const int arr_size = (sequence.length() - kmer_size + 1);
    std::vector<std::string> kmer_vec;
    void build_set();
};

// Converts a vector of Records to a vector of KmerObjs
std::vector<KmerObj> Records_to_KmerObjs(std::vector<Record> record_vec);

// Creates a kmer set for each record in a fasta file
std::vector<KmerObj> BuildKmerSet(std::string fn);

//  Calculates the distance between two strings of equal length
int StringDist(const std::string& s1, const std::string& s2);

// Calculates the minimum distance between two sets of kmers
int KmerDist(KmerObj k1, KmerObj k2);

// Overloaded with minimum distance provided to exit when condition met
int KmerDist(KmerObj k1, KmerObj k2, int minimum_dist);


#endif
