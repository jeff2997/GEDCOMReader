//
// Created by jeffrey on 2/21/18.
//

#ifndef WEEK07_NODE_H
#define WEEK07_NODE_H

#include <clocale>
#include <ostream>

template <class T>
struct Node
{
   //The Default Constructor
   //Purpose: to initialize default values
   //Parameters: none
   //Returns: none
   Node();
   //The Parametrized constructor
   //Parameters: set data
   //Parameters: T write
   explicit Node(T);

   //The Parametrized constructor
   //Parameters: set data and next
   //Parameters: T write and Node<T>* previous, Node<T>* next
   Node(T, Node<T>*, Node<T>*);

   Node<T>* next;
   Node<T>* previous;

   T data;
};

template<class T>
Node<T>::Node()
{
   next = NULL;
   previous = NULL;
}

template<class T>
Node<T>::Node(T write)
{
   data = write;
   next = NULL;
   previous = NULL;
}

template<class T>
Node<T>::Node(T write, Node<T> * prev, Node<T> * nxt)
{
   data = write;
   previous = prev;
   next = nxt;
}

/************************************
 * BEGIN NON-MEMBER FUNCTIONS
 */

/************************************
 * freeData() frees the data in a linked list
 * @tparam T
 * @param head
 */
template <class T>
void freeData(Node<T>* &pHead)
{
   if(pHead != NULL)
   {
      if(pHead->next != NULL)
      {
         freeData(pHead->next);
         delete pHead;
      }
      else
      {
         pHead->next = NULL;
         delete pHead;
      }
      pHead = NULL;
   }
}

/***********************************
 * insert() adds a node
 * @tparam T
 * @param write
 * @param pre
 * @param pHead
 */
template <class T>
void insert(T write, Node<T>* &pre, bool pHead = false)
{
   if(!pHead)
   {
      Node<T>* myNewNode = new Node<T>(write);
      if(pre != NULL)
      {
         myNewNode->next = pre->next;
         pre->next = myNewNode;
      }
      else
         pre = myNewNode;
   }
   else
   {
      Node<T>* myNewNode = new Node<T>(write, pre);
      pre = myNewNode;
   }

}

/************************************
 * find() - returns a node that it finds, else returns null
 * @tparam T
 * @param pHead
 * @param value
 * @return
 */
template <class T>
Node<T>* find(Node<T>* pHead, const T& value)
{
   Node<T>* thisPtr = pHead;
   while(thisPtr != NULL)
   {
      if (thisPtr->data == value)
         return thisPtr;
      else
         thisPtr = thisPtr->next;
   }
   return NULL;
}

/******************************
 * the overloaded extraction operator
 * @tparam T
 * @param out
 * @param rhs
 * @return
 */
template <class T>
std::ostream& operator<<(std::ostream& out, Node<T>* rhs)
{
   Node<T>* thisPtr = rhs;
   while(thisPtr != NULL)
   {
      out << thisPtr->data;
      if(thisPtr->next != NULL)
         out << ", ";
      thisPtr = thisPtr->next;
   }
   return out;
}
/***************************************
 * copy() - makes a copy of a list
 * @tparam T
 * @param rhs
 * @return
 */
template <class T>
Node<T>* copy(Node<T>* rhs)
{
   if(rhs == NULL)
      return NULL;
   else if(rhs->next == NULL)
   {
      return new Node<T>(rhs->data, rhs->previous, NULL);
   }
   else
   {
      Node<T>* newFirstNode = new Node<T>(rhs->data, rhs->previous, copy(rhs->next));
      return newFirstNode;
   }
}

#endif //WEEK07_NODE_H
