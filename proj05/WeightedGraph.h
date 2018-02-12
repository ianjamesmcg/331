#include <iostream>
#include <iomanip>
#include <float.h>
#include <map>
#include <vector>
#include <stack>
#include <fstream>
using namespace std;

class WGraph
{
public:
  WGraph( char *filename )
  {
    Build( filename );
  }

  int Dijkstra( int src, int dest);
  int Traverse(int v);

  struct Vertex
  {
  public:
    friend class WGraph;

    Vertex(){ known = false; cost = FLT_MAX; }
    Vertex(int inid){ id = inid; known = false; cost = FLT_MAX; }

  private:
    int id;
    bool known;
    float cost;
    Vertex *prev;
    map<int, float> adjList;
  };

private:
  map<int, Vertex> vlist;

  void Build( char *filename );
};


int WGraph::Dijkstra( int src, int dest)
{
  if (vlist.find(src) == vlist.end())
  {
    cout << "Source vertex not in map" << endl;
    return 0;
  }
  else if (vlist.find(dest) == vlist.end())
  {
    cout << "Destination vertex not in map" << endl;
    return 0;
  }

  vlist[src].cost = 0;
  Traverse(src);

  if (vlist[dest].cost == FLT_MAX)
  {
    cout << "NO PATH FOUND" << endl;
    return 0;
  }

  Vertex *tmp = &vlist[dest];
  stack<int> path;
  while ( tmp != &vlist[src] )
  {
    path.push(tmp->id);
    tmp = tmp->prev;
  }
  cout << src;
  while ( !path.empty() )
  {
    cout << "->" << path.top();
    path.pop();
  }
  cout << fixed;
  cout << " " << setprecision(2) << vlist[dest].cost << endl;

  return 1;
} 

int WGraph::Traverse(int v)
{
  vlist[v].known = true;
  vector<int> travorder; 
  vector<int>::iterator vit; 

  map<int, float>::iterator it;
  for (it = vlist[v].adjList.begin(); it != vlist[v].adjList.end(); it++)
  {
    //adjust if cost is less than current
    if ((vlist[v].cost + it->second) < (vlist[it->first].cost))
    {
      vlist[it->first].prev = &vlist[v];
      vlist[it->first].cost = vlist[v].cost + it->second;
    }

    //add index to traversal list, sorted by cost
    for (vit = travorder.begin(); vit != travorder.end(); vit++)
    {
      if (vlist[it->first].cost < vlist[*vit].cost)
      {
        break;
      }
    }
    travorder.insert(vit, it->first);
  }

  for (vit = travorder.begin(); vit != travorder.end(); vit++)
  {
    Traverse(*vit);
  }
}

void WGraph::Build( char *filename )
{
  ifstream infile(filename);
  string line;

  int index;
  int adjacent;
  float weight;

  while (getline(infile, line))
  {
    index = line[0] - '0';
    adjacent = line[2] - '0';    
    weight = atof( line.substr(4).c_str() );

    if (vlist.find(index) == vlist.end())
    {
      vlist.insert( pair<int, Vertex>(index, Vertex(index)));
    }

    if (vlist.find(adjacent) == vlist.end())
    {
      vlist.insert( pair<int, Vertex>(adjacent, Vertex(adjacent)));
    }

    vlist[index].adjList.insert( pair<int, float>(adjacent, weight) );
  }
}
