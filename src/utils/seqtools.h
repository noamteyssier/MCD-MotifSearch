#ifndef SEQTOOLS
#define SEQTOOLS

#include <string>
#include <vector>


struct Record
{
  std::string header;
  std::string sequence;
};

template <class Reader>
std::vector<Record> read_stream(Reader& stream){
  /*
  Reads stream into a vector of records and returns vector
  */

  std::vector<Record> record_vec;

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
