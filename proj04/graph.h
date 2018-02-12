/*
 Class Graph is a mockup class, thus you must not assume that this is a completed implementation. 
 Please add codes/comments to complete this class and where you think there is a need.
*/
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

class Graph
{
private:
  int size;
  
  class Vertex
  {
    private:
      int isVisited;
      int color;
      vector<int> connections; 
    public:
      friend class Graph;
      Vertex(){ isVisited=color=0;};
  };

  vector<Vertex> vertices;

public:
	Graph(char* filename) 
  {
    readFile(filename);
  }

	~Graph() {} 

	// function to determine whether a graph is bipartite
	// start traverse a graph from node u
	// return true if a graph is bipartite. Otherwise, return false
	bool isBipartitePrintTraversePath(int u);
  void readFile(char* filename);
};

// function to determine whether a graph is bipartite
// start traverse a graph from node u
// return true if a graph is bipartite. Otherwise, return false
bool Graph::isBipartitePrintTraversePath(int u) {
  int conflict = 0;
  int currentColor;
  if(vertices[u].color)
  {
    currentColor = vertices[u].color; 
  }
  else // first vertex visited
  {
    if(u % 2){currentColor = vertices[u].color = -1;} //odd -> black
    else{currentColor = vertices[u].color = 1;} // even -> white
  }

  if(!vertices[u].isVisited)
  {
    vertices[u].isVisited = 1;
    cout << u;
    if(vertices[u].color > 0){cout << " WHITE" << endl;}
    else if(vertices[u].color < 0){cout << " BLACK" << endl;}

    for(int j = 0; j < vertices[u].connections.size(); j++)
    { 
      if(vertices[vertices[u].connections[j]].color)
      {
        if(vertices[vertices[u].connections[j]].color == currentColor)
        {
          cout << "CONFLICT " << u << " " << vertices[u].connections[j] << endl;
          return false;
        }
      }
      else
      {
        vertices[vertices[u].connections[j]].color = -1*currentColor;
      }

      if(isBipartitePrintTraversePath(vertices[u].connections[j]) == false)
      {
        return false;
      };
    }
  }
  return true;
}

void Graph:: readFile(char* filename)
{
  ifstream infile(filename);
  std::string line;
  char* cLine;
  char* ch;

  int pindex = 0;

  while(getline(infile, line))
  {
    size++;
    cLine = &line[0];

    int pindex = 0;
    int setp = 1;

    ch = strtok(cLine, " ");
    while(ch != NULL)
    {
      if(setp)
      {
        pindex = atoi(ch);
        vertices.push_back(Vertex());
        setp = 0;
      } 
      else
      {
        vertices[pindex].connections.push_back(atoi(ch));
      }
      ch = strtok(NULL, " ");
    }    
  }
}
