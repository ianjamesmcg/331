//
// Name :         RevList.h
// Description :  Simple doubly linked list with reversing feature.
//

#ifndef REVLIST_H
#define REVLIST_H

//#include <iostream>
//using namespace std;

template<class T> class CRevList
{

public:
  // Constructor.  Sets to an empty list.
  CRevList() 
  {
    init();
  }

  // Destructor.  Deletes everything in the list.
  ~CRevList()
  {
    Clear();
    delete m_head;
  }

  // Copy constructor.  Copies another list.
  CRevList(const CRevList &b)
  {
    init();
    Node const *tmp = new Node();
    tmp = b.Begin();

    while( tmp != Next(b.End()) )
    {
      PushBack( tmp->Data() );
      tmp = Next(tmp);
    } 
  }

  // Assignment operator.  Copies another list.
  void operator=(const CRevList &b);

  // Clear the list.
  void Clear()
  {  
    for (unsigned i = 0; i < theSize; i--)
    {
      Delete( m_head->m_next );   
    }
  }


  //
  // class Node
  // The nested node class for objects in our linked list.
  //
  // YOU MAY NOT MODIFY THIS CLASS!
  class Node 
  {
  public:
    friend class CRevList;
  
    Node() {m_next = 0;  m_prev = 0;}
    Node(const T &t) {m_payload = t;  m_next = 0;  m_prev = 0;}
  
    T Data() {return m_payload;}
    const T Data() const {return m_payload;}
  
  private:
    Node    *m_next;
    Node    *m_prev;
    T       m_payload;
  };
  
  // Determines if the list is empty
  bool IsEmpty() const { return !theSize; }

  //methods to add data to the front or the back of the list
  void PushFront(const T &t) 
  {
    ++theSize;
    Node *newNode = new Node(t);

    if ( reversed < 0 )
    {
      newNode->m_next = m_head->m_next;
      newNode->m_prev = m_head;
      m_head->m_next = newNode;
      newNode->m_next->m_prev = newNode;
    }
    else
    {  
      newNode->m_prev = m_head->m_prev;
      newNode->m_next = m_head;
      m_head->m_prev = newNode;
      newNode->m_prev->m_next = newNode;
    }
  }
  void PushBack(const T &t) 
  { 
    ++theSize;
    Node *newNode = new Node(t);

    if ( reversed > 0 )
    {
      newNode->m_next = m_head->m_next;
      newNode->m_prev = m_head;
      m_head->m_next = newNode;
      newNode->m_next->m_prev = newNode;
    }
    else
    {  
      newNode->m_prev = m_head->m_prev;
      newNode->m_next = m_head;
      m_head->m_prev = newNode;
      newNode->m_prev->m_next = newNode;
    }
  }
  void PopFront() 
  { 
    --theSize;

    if ( reversed > 0 )
    {  
      Delete( m_head->m_next );
    }
    else
    {
      Delete( m_head->m_prev );
    }
  }
  void PopBack()
  { 
    --theSize;

    if ( reversed < 0 )
    {  
      Delete( m_head->m_next );
    }
    else
    {
      Delete( m_head->m_prev );
    }
  }

  //Get a pointer to the first node in the list
  const Node *Begin() const 
  { 
    if ( reversed < 0 ) { return m_head->m_next; } 
    else { return m_head->m_prev; }
  }
  Node *Begin()
  { 
    if ( reversed < 0 ) { return m_head->m_next; } 
    else { return m_head->m_prev; }
  }

  //get a pointer to the last node in the list
  const Node *End() const
  { 
    if ( reversed > 0 ) { return m_head->m_next; } 
    else { return m_head->m_prev; }
  } 
  Node *End()
  { 
    if ( reversed > 0 ) { return m_head->m_next; } 
    else { return m_head->m_prev; }
  }

  //get a pointer to node next in the list
  const Node *Next(const Node *n) const 
  { 
    if (reversed > 0) 
    { 
      if ( n->m_prev == m_head ) { return n->m_prev->m_prev; }
      else { return n->m_prev; }
    } 
    else 
    { 
      if ( n->m_next == m_head ) { return n->m_next->m_next; }
      else { return n->m_next; } 
    }
  }
  Node *Next(const Node *n)
  { 
    if (reversed > 0) 
    { 
      if ( n->m_prev == m_head ) { return n->m_prev->m_prev; }
      else { return n->m_prev; }
    } 
    else 
    { 
      if ( n->m_next == m_head ) { return n->m_next->m_next; }
      else { return n->m_next; } 
    }
  }

  //Find a node with the specified key
  const Node *Find(const T &t) const
  {
    Node *tmp = new Node();
    tmp = m_head->m_next;
    while ( tmp =! m_head )
    {
      if (tmp->Data() == t)
      {
        return tmp;
      }
    }
    return NULL;
  }
  Node *Find(const T &t) 
  {
    Node *tmp = new Node();
    tmp = m_head->m_next;
    while ( tmp =! m_head )
    {
      if (tmp->Data() == t)
      {
        return tmp;
      }
    }
    return NULL;
  }

  //Delete the given node
  void Delete(Node *n)
  {
    if ( theSize == 0  )
    {
      //do nothing  
    }
    else
    {
      if ( n == m_head) { n = Next(n); }

      n->m_prev->m_next = n->m_next;
      n->m_next->m_prev = n->m_prev;
      delete n;

      --theSize;
    }
  }

  //Reverse the list in O(1) time
  void Reverse() { reversed *= -1; }

  

private:

  //NOTE: you may add any private member variables or 
  //      methods you need to complete the implementation
  
  int     theSize;
  int     reversed = -1;
  Node    *m_head;             // Head node


  void init()
  {
    theSize = 0;
    m_head = new Node();
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
  }

};

// Assignment operator.  Copies another list.
template<class T> void CRevList<T>::operator=(const CRevList<T> &b)
{
  Clear();
  Node const *tmp = new Node();
  tmp = b.Begin();

  while( tmp != Next(b.End()) )
  {
    PushBack( tmp->Data() );
    tmp = Next(tmp);
  }  
}

//template<class T> (CRevList<T>::Node *) CRevList<T>::Begin1() {return m_reverse ? m_head.m_prev : m_head.m_next;}


#endif
