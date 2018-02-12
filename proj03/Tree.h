#ifndef CTREE_H
#define CTREE_H

#include <iostream>

using namespace std;

template<class T> class CTree
{
public:
    CTree() {m_root = 0;}
    ~CTree() {delete m_root;}

    //
    // class Node
    // The nested node class for objects in our tree.
    //

    class Node 
    {
    public:
        friend class CTree;

        Node() {m_ll = 0;  m_rl = 0;}
        Node(const T &t) {m_number = t;  m_ll = 0;  m_rl = 0;}
        ~Node() {delete m_ll;  delete m_rl;}

        T &Data() {return m_number;}
        const T &Data() const {return m_number;}

    private:
        Node    *m_ll;
        Node    *m_rl;
        T       m_number;

    };

    void Insert(const T &t) 
    {
      Node *in = new Node( t );
      if ( m_root == 0 ){ m_root = in; }
      else
      {
        Node *cmp = m_root;
        while ( true ) 
          if ( in->m_number < cmp->m_number )
          {
            if ( cmp->m_ll != 0){ cmp = cmp->m_ll; }
            else{ cmp->m_ll = in; break; }
          }
          else
          {
            if ( cmp->m_rl != 0 ){ cmp = cmp->m_rl; }
            else{ cmp->m_rl = in; break; }
          }
      }
    }
    void Preorder(std::ostream &p_str) 
    {   
      preorder( p_str, m_root ); 
      p_str << endl;
    }
    int Depth() 
    {
      return depth( m_root ); 
    }

    const Node *Find(const T &t) const { find(t); }
    Node *Find(const T &t) { find(t);}

    void Delete(const T &t)
    {
      del( t, m_root );
    }


private:
    Node *m_root;

    void preorder(std::ostream &p_str, Node *tmp)
    {
      p_str << tmp->m_number << " ";
      if (tmp->m_ll != 0){ preorder( p_str, tmp->m_ll); }
      if (tmp->m_rl != 0){ preorder( p_str, tmp->m_rl); }
    }

    int depth( Node *tmp )
    {
      int r;
      int l; 

      if (tmp->m_ll != 0){ l = depth(tmp->m_ll); }
      else{ l = 0; };
      if (tmp->m_rl != 0){ r = depth(tmp->m_rl); }
      else{ r = 0; };

      if (r > l){ return (r+1); }
      else{ return (l+1); }
    }

    Node *find(const T &t)
    {
      Node *tmp = m_root;
      while (tmp)
      {
        if (tmp->Data() == t)
        {
          return tmp;
        }
        else if (tmp->m_number < t)
        {
          tmp = tmp->m_rl;
        }
        else
        {
          tmp = tmp->m_ll;
        }
      }
    }

    void del(const T &t, Node *&tmp)
    {
      if( tmp == 0 )
      {
        //do nothing not found
      }
      else if( t < tmp->m_number )
      {
        del( t, tmp->m_ll );
      }
      else if( tmp->m_number < t )
      {
        del( t, tmp->m_rl );
      }
      else if( (tmp->m_ll != 0) && (tmp->m_rl != 0))
      {
        tmp->m_number = (findMin( tmp->m_rl )->m_number);
        del( tmp->m_number, tmp->m_rl );
      }
      else
      {
        Node *old = tmp;
        if ( tmp->m_ll != 0 )
        {
          tmp = tmp->m_ll;
        }
        else
        {
          tmp = tmp->m_rl;
        }

        old = 0;
      }
    }

    Node *findMin( Node *p )
    {
      if ( p == 0 ){ return 0; }
      if ( p->m_ll == 0 ){ return p; }
      return findMin( p->m_ll );
    }
};


#endif
