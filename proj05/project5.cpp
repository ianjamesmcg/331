#include <iostream>
#include "WeightedGraph.h"
using namespace std;

int main(int argc, char*argv[])
{
  cout << endl;
  if (argc != 4)
  { 
    cout << "Error: prog accepts 3 arguments" << endl;
    return EXIT_FAILURE;
  }

  WGraph mygraph( argv[1] );

  int src = atoi(argv[2]);
  int dest = atoi(argv[3]);

  if (!mygraph.Dijkstra(src, dest)){ cout << endl; return EXIT_FAILURE;}

  cout << endl;
  return EXIT_SUCCESS;
}

