#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_
#include <vector>
#include "InsertionSort.h"
using namespace std;

//your quick sort here

long long quickSort( vector<int> &infile ){
  
  long long cmp; 

  if( infile.size() > 1 ){
    cmp += (infile.size() - 1);
    
    vector<int> smaller;
    vector<int> same;
    vector<int> larger;

//    int chosenItem = infile[ 0 ];
    int chosenItem = infile[ infile.size() / 2 ];

    for( int  &i : infile ){
      if( i < chosenItem )
        smaller.push_back( std::move( i ) );
      else if( chosenItem < i )
        larger.push_back( std::move( i ) );
      else
        same.push_back( std::move( i ) );
    };

    cmp += quickSort( smaller );
    cmp += quickSort( larger );
     
    std::move( begin( smaller ), end( smaller ), begin( infile ) );
    std::move( begin( same ), end( same ), begin( infile ) + smaller.size() );
    std::move( begin( larger ), end( larger ), end( infile ) - larger.size() );
    };
  
  return cmp;
  };
  
 

#endif

