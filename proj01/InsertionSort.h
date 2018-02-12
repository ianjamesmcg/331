#ifndef _INSERTIONSORT_H_
#define _INSERTIONSORT_H_
#include <vector>
using namespace std;

// insertion sort here

long long insertionSort( vector<int> &infile ){
  long long cmp = 0; 

  for( int p = 1; p < infile.size(); ++p ){
    int tmp = infile[ p ];  

    int j;
    
    for( j = p; j > 0 && tmp < infile[ j - 1 ]; --j ){
      infile[ j ] = infile[ j - 1 ];
      cmp +=1;
    };

    infile[ j ] = tmp;
  };

  return cmp;
};

#endif
