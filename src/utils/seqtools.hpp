#ifndef SEQTOOLS
#define SEQTOOLS

#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct Record
{
  string header;
  string sequence;
};

template <class Reader>
vector<Record> read_stream(Reader& stream){
  /*
  Reads stream into a vector of records and returns vector
  */

  vector<Record> record_vec;

  while (true){
    Record r;
    if (!getline(stream, r.header)){
      break;
    }
    getline(stream, r.sequence);

    r.header.erase(0, 1);  // remove carat from header

    record_vec.push_back(r);
  }

  return record_vec;
}


#endif
