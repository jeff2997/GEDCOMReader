#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <cassert>

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:
   BinaryNode();
   BinaryNode(T);
   // return size (i.e. number of nodes in tree)
   int size() const
   {
      return 1 +
             (pLeft== NULL? 0 : pLeft->size()) +
             (pRight == NULL ? 0 : pRight->size());
   }

   // add a node to the left/right
   void addLeft (BinaryNode <T> * pNode);
   void addRight(BinaryNode <T> * pNode);

   // create a node and add it to the left/right
   void addLeft (const T & t) noexcept(false);
   void addRight(const T & t) noexcept(false);

   //

   // since no validation is done, everything is public
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;
   T* data;
   int size();

private:
   int getSize(BinaryNode<T>*);
};
/***************************
 * Adds a node to the left child
 * @tparam T
 * @param pNode
 */
template<class T>
void BinaryNode<T>::addLeft(BinaryNode<T> *pNode)
{
   pLeft = pNode;
   if(pNode != NULL)
      pNode->pParent = this;
}
/****************************
 * Adds a node to the right child
 * @tparam T
 * @param pNode
 */
template<class T>
void BinaryNode<T>::addRight(BinaryNode<T> *pNode)
{
   pRight = pNode;
   if(pNode != NULL)
      pNode->pParent = this;
}
/****************************
 * Adds a node to the left child
 * @tparam T
 * @param t
 */
template<class T>
void BinaryNode<T>::addLeft(const T& t) noexcept(false)
{
   try
   {
      pLeft = new BinaryNode<T>;
      pLeft->pParent = this;
      pLeft->data = t;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
}
/****************************
 * Adds a node to the right child
 * @tparam T
 * @param t
 */
template<class T>
void BinaryNode<T>::addRight(const T& t) noexcept(false)
{
   try
   {
      pRight = new BinaryNode<T>;
      pRight->pParent = this;
      pRight->data = t;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
}
/****************************
 * Default Constructor
 * @tparam T
 */
template<class T>
BinaryNode<T>::BinaryNode()
{
   pLeft = NULL;
   pRight = NULL;
   pParent = NULL;
   data = NULL;
}
/****************************
 * Overloaded Constructor
 * @tparam T
 * @param myData
 */
template<class T>
BinaryNode<T>::BinaryNode(T myData)
{
   pLeft = NULL;
   pRight = NULL;
   pParent = NULL;
   data = myData;
}

template<class T>
int BinaryNode<T>::size()
{
   return getSize(this);
}

template<class T>
int BinaryNode<T>::getSize(BinaryNode<T> * add)
{
   int mySize = 0;
   if(add == NULL)
      return 0;
   if(add->pLeft != NULL)
      mySize += getSize(add->pLeft);
   if(add->pRight != NULL)
      mySize += getSize(add->pRight);
   //Account for this node
   mySize++;
   return mySize;
}

/***************************
 * Begin Non member functions
 */

/***************************
 * Deletes all of the tree recursively
 * @param deleteMe
 */
template <class T>
void deleteBinaryTree(BinaryNode<T>* deleteMe)
{
   if(deleteMe->pLeft != NULL)
      deleteBinaryTree(deleteMe->pLeft);
   if(deleteMe->pRight != NULL)
      deleteBinaryTree(deleteMe->pRight);
   delete deleteMe;
}

/***************************
 * Overloaded insertion operator
 * @param rhs
 * @return
 */
template <class T>
std::ostream& operator<<(std::ostream& out, BinaryNode<T>* myData)
{
   if(myData != NULL)
   {
      if(myData->pLeft != NULL)
         out << myData->pLeft;
      out << myData->data << " ";
      if(myData->pRight != NULL)
         out << myData->pRight;
   }
   return out;
}




#endif // BNODE_H
