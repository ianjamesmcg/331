#ifndef _VERIFYSORT_H_
#define _VERIFYSORT_H_
#include <vector>
using namespace std;

//your verify sort here

int verifySort( vector<int> infile ){

  for( int p = 1; p < infile.size(); ++p){

    if( infile[ p ] < infile[ p - 1 ] ){
      return 0;
    };
  
  };
  
  return 1;
};

#endif
