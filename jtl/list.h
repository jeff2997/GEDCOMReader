//
// Created by jeffrey on 2/21/18.
//

#ifndef WEEK07_LIST_H
#define WEEK07_LIST_H

#include <clocale>
#include "node.h"

//Predeclare List Iterator
template <class T>
class ListIterator;

template <class T>
class List
{
public:
   /***********************
    * The Default Constructor
    */
   List();
   /***********************
    * The copy constructor
    */
   List(const List<T>&);
   /***********************
    * The Default destructor
    */
   ~List();
   /***********************
    * The overloaded assignment operator
    */
   List<T>& operator=(const List<T>&);
   /***********************
    * empty() returns true if empty
    * @return
    */
   bool empty();
   /***********************
    * clear() empties the entire list
    */
   void clear();
   /***********************
    * size() returns the size of the list
    * @return
    */
   int size();
   /***********************
    * push_back() adds an item to the back
    */
   void push_back(const T&) throw (const char *);
   /***********************
    * push_front() adds an item to the front
    */
   void push_front(const T&) throw (const char *);
   /***********************
    * Returns the first item in the list
    * @return
    */
   T& front() throw (const char *);
   /************************
    * returns the last item in the list
    * @return
    */
   T& back() throw (const char *);
   /************************
    * Adds an item to the list, and takes
    * both a ListIterator to the item which it needs to insert before,
    * and the item to insert.
    * @return a ListIterator to the new item
    */
   ListIterator<T> insert(ListIterator<T>& node, T& newData) throw(const char *);
   /***********************
    * remove() removes an element from the list
    */
   void remove(ListIterator<T>&) throw (const char *);
   /***********************
    * Returns a ListIterator to the first item in the list
    * @return
    */
   ListIterator<T> begin();
   /***********************
    * Returns a ListIterator to the last item in the list
    * @return
    */
   ListIterator<T> rbegin();
   /***********************
    * Returns a ListIterator that points to one past the last item in the
    * list (NULL).
    * @return
    */
   ListIterator<T> end();
   /***********************
    * Returns a ListIterator that points to one before the first item
    * in the list (NULL).
    * @return
    */
   ListIterator<T> rend();

private:
   int mySize;
   Node<T>* first;
   Node<T>* last;
   /***********************
    * Calculates the size of the list
    * @return
    */
   int calcSize(Node<T>*);


};

template<class T>
List<T>::List()
{
   mySize = 0;
   first = NULL;
   last = NULL;
}

template<class T>
List<T>::List(const List<T>& rhs)
{
   first = copy(rhs.first);
   last = rhs.last;
   mySize = rhs.mySize;
}

template<class T>
List<T>::~List()
{
   freeData(first);
}

template<class T>
List<T>& List<T>::operator=(const List<T> & rhs)
{
   freeData(first);
   first = copy(rhs.first);
   last = rhs.last;
   mySize = rhs.mySize;
   return *this;
}

template<class T>
bool List<T>::empty()
{
   return (mySize == 0);
}

template<class T>
void List<T>::clear()
{
   freeData(first);
   first = NULL;
   last = NULL;
   mySize = 0;
}

template<class T>
int List<T>::size()
{
   return mySize;
}

template<class T>
void List<T>::push_back(const T & newData) throw (const char *)
{
   if(mySize == 0)
   {
      //Consider Simplifying :)
      first = new Node<T>;
      first->data = newData;
      first->previous = NULL;
      first->next = NULL;
      last = first;
   }
   else //If larger than 0
   {
      last->next = new Node<T>;
      last->next->previous = last;
      last = last->next;
      last->next = NULL;
      last->data = newData;
   }
   mySize++;
}

template<class T>
void List<T>::push_front(const T & newData) throw (const char *)
{
   if(mySize == 0)
   {
      //Consider Simplifying :)
      first = new Node<T>;
      first->data = newData;
      first->previous = NULL;
      first->next = NULL;
      last = first;
   }
   else //If larger than 0
   {
      first->previous = new Node<T>;
      first->previous->next = first;
      first = first->previous;
      first->previous = NULL;
      first->data = newData;
   }
   mySize++;
}

template<class T>
T& List<T>::front() throw (const char *)
{
   if(mySize && first != NULL && last != NULL)
      return first->data;
   else
      throw "ERROR: unable to access data from an empty list";
}

template<class T>
T &List<T>::back() throw (const char *)
{
   if(mySize && first != NULL && last != NULL)
      return last->data;
   else
      throw "ERROR: unable to access data from an empty list";
}

template<class T>
ListIterator<T> List<T>::insert(ListIterator<T>& node, T& newData) throw (const char *)
{
   try
   {
      if(node!=end())
      {
         Node<T> *thisNode = new Node<T>;

         thisNode->next = node.getLocation();
         if (thisNode->next != NULL)
            thisNode->previous = thisNode->next->previous;
         if (thisNode->previous != NULL)
         {
            thisNode->previous->next = thisNode;
         }
         if (thisNode->next != NULL)
            thisNode->next->previous = thisNode;
         thisNode->data = newData;
         node--;
         if (thisNode->previous == NULL)
            first = thisNode;
         if (thisNode->next == NULL)
            last = thisNode;
      }
      else
      {
         //we are at the end.
         last->next = new Node<T>;
         last->next->previous = last;
         last = last->next;
         last->next = NULL;
         last->data = newData;
         node++;
      }
      mySize++;
      return node;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

template<class T>
void List<T>::remove(ListIterator<T>& node) throw (const char *)
{
   if(node != end())
   {

      Node<T> *myPtr = node.getLocation();
      if(myPtr == first)
         first = myPtr->next;
      if(myPtr == last)
         last = myPtr->previous;
      if(myPtr->previous != NULL)
         myPtr->previous->next = myPtr->next;
      if(myPtr->next != NULL)
         myPtr->next->previous = myPtr->previous;
      node.setLocation(myPtr->next);
      delete myPtr;
      mySize--;

   } else
      throw "ERROR: unable to remove from an invalid location in a list";
}

template<class T>
ListIterator<T> List<T>::begin()
{
   return ListIterator<T>(first);
}

template<class T>
ListIterator<T> List<T>::rbegin()
{
   return ListIterator<T>(last);
}

template<class T>
ListIterator<T> List<T>::end()
{
   if(!empty())
      return (++ListIterator<T>(last));
   else
      return ListIterator<T>(NULL);
}

template<class T>
ListIterator<T> List<T>::rend()
{
   if(!empty())
      return (--ListIterator<T>(first));
   else
      return ListIterator<T>(NULL);
}

template<class T>
int List<T>::calcSize(Node<T> *)
{
   mySize = 0;
   Node<T>* myPtr = first;
   while (myPtr != NULL)
   {
      mySize++;
      myPtr = myPtr->next;
   }
}



template <class T>
class ListIterator
{
public:
   // default constructor
   ListIterator() : p(NULL) {}

   // initialize to direct p to some item
   explicit ListIterator(Node<T> * p) : p(p) {}


   // not equals operator
   bool operator != (const ListIterator & rhs) const {
      return rhs.p != this->p;
   }

   //operator two
   bool operator != (ListIterator & rhs) {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return p->data;
   }

   // prefix increment
   ListIterator <T> & operator ++ ()
   {
      if(p != NULL)
      {
         p = p->next;
         return *this;
      }
   }

   // postfix increment
   ListIterator <T> operator++(int postfix)
   {
      if(p != NULL)
      {
         ListIterator tmp(*this);
         p = p->next;
         return tmp;
      }
   }
   //prefix increment
   ListIterator<T>& operator--()
   {
      if(p != NULL)
      {
         p = p->previous;
         return *this;
      }
   }
   //postfix increment
   ListIterator<T> operator--(int postfix)
   {
      if(p != NULL)
      {
         ListIterator tmp(*this);
         p = p->previous;
         return tmp;
      }
   }
   Node<T>* getLocation()
   {
      return p;
   }
   void setLocation(Node<T>* rhs)
   {
      p = rhs;
   }
private:
   Node<T> * p;
};


#endif //WEEK07_LIST_H
