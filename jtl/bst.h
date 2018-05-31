/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Br. Helfrich
 *    Modified by Scott Ercanbrack - removed most of the the BST class functions,
 *                                   but left BST Iterator class.
 *    Completed by Jeffrey Pearson - now it works!!
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"    // for BinaryNode
#include "stack.h"    // for Stack

// forward declaration for the BST iterator
template <class T>
class BSTIterator; 

/*****************************************************************
 * BINARY SEARCH TREE
 * Create a Binary Search Tree
 *****************************************************************/
template <class T>
class BST
{
public:
   // constructor
   BST(): root(NULL){};
   
   // copy constructor
   BST(const BST & rhs);    
   
   ~BST();

   int  size() const  { return empty() ? 0 : root->size(); }   // BinaryNode class needs a size function
   
   
   // determine if the tree is empty
   bool empty() const
   {
      return root == NULL;
   }

   // remove all the nodes from the tree.  Makes an empty tree.
   void clear()
   {
      deleteBinaryTree(root);
      root = NULL;
   }

   // overloaded assignment operator
   BST & operator = (const BST & rhs) noexcept(false)
   {
      root = copy(rhs.root);
      return *this;
   }
      
   // insert an item
   void insert(const T & t) noexcept(false);

   // remove an item
   void remove(BSTIterator <T> & it);

   // find a given item
   BSTIterator <T> find(const T & t);

   // the usual iterator stuff
   BSTIterator <T> begin() const;
   BSTIterator <T> end() const  { return BSTIterator <T> (NULL) ; }
   BSTIterator <T> rbegin() const;
   BSTIterator <T> rend() const  { return BSTIterator <T> (NULL); }
   
private:

   BinaryNode <T> * root;
   //A copy function to help the constructor and assignment operator
   BinaryNode<T>* copy(BinaryNode<T>*);
};

/*********************************************************
* copy constructor
**********************************************************/
template <class T>
BST<T>::BST(const BST &rhs)
{
   root = copy(rhs.root);
}

/*****************************************************
* Destructor
*******************************************************/
template <class T>
BST<T>::~BST()
{
   if(root != NULL)
      deleteBinaryTree(root);
}


/*****************************************************
 * BST :: BEGIN
 * Return the first node (left-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: begin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pLeft)
      nodes.push(nodes.top()->pLeft);

   return BSTIterator<T>(nodes);   
}

/*****************************************************
 * BST :: RBEGIN
 * Return the last node (right-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: rbegin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pRight)
      nodes.push(nodes.top()->pRight);

   return BSTIterator<T>(nodes);
}  

/*****************************************************
 * BST :: INSERT
 * Insert a node at a given location in the tree
 ****************************************************/
template <class T>
void BST <T> :: insert(const T & t) noexcept(false)
{

   //Case 1 - If there is no tree
   BinaryNode<T>* at = root;
   bool first = true;
   while(first)
   {

      if(at == NULL)
      {
         at = new BinaryNode<T>(t);
         root = at;
         first = false;
      }
      else if(at->pLeft == NULL && t <= at->data)
      {
         //If less than parent value, insert here
         at->pLeft = new BinaryNode<T>(t);
         at->pLeft->pParent = at;
         first = false;
      }
      else if(at->pRight == NULL && t > at->data)
      {
         //If greater than parent value, insert here
         at->pRight = new BinaryNode<T>(t);
         at->pRight->pParent = at;
         first = false;
      }
      else if(at->pLeft != NULL && t <= at->data)
      {
         //If the left node exists, and we are <= to the value, we
         //don't want to make a new node right now, so go left
         at = at->pLeft;
      }
      else if(at->pRight != NULL && t > at->data)
      {
         //Same as the pLeft, but go right
         at = at->pRight;
      }
   }

}

/*************************************************
 * BST :: REMOVE
 * Remove a given node as specified by the iterator
 ************************************************/
template <class T>
void BST <T> :: remove(BSTIterator <T> & it)
{
   BinaryNode<T>* point = it.getNode();
   //Check if deleting a leaf
   if(point->pLeft == NULL && point->pRight == NULL)
   {
      if(point->pParent != NULL)
      {
         if(point->pParent->data > point->data)
            //find out which side this node is on of the parent
            point->pParent->pLeft = NULL;
         else
            point->pParent->pRight = NULL;
      }
      delete point;
   }
   //Check if deleting something with one child
   else if((point->pLeft == NULL && point->pRight != NULL) ||
         (point->pLeft != NULL && point->pRight == NULL))
   {
      if(point->pParent->data > point->data) //If I am on the left
      {
         if(point->pRight != NULL)
            point->pParent->pLeft = point->pRight;
         else
            point->pParent->pLeft = point->pLeft;
      }
      else //If on the right
      {
         if(point->pRight != NULL)
            point->pParent->pRight = point->pRight;
         else
            point->pParent->pRight = point->pLeft;
      }
   }
   //Check if deleting something with two children.
   else if(point->pLeft != NULL && point->pRight != NULL)
   {
      //Find Successor (Txtbook pg 685)
      BinaryNode<T>* finder  = point->pRight;
      BinaryNode<T>* parent = point;
      while(finder->pLeft != NULL)
      {
         parent = finder;
         finder = finder->pLeft;
      }
      //Move data
      point->data = finder->data;
      point = finder;
      Stack<BinaryNode<T>* > findme;
      findme.push(NULL);
      findme.push(finder);
      BSTIterator<T> myFinder(findme);
      remove(myFinder);
   }

}

/****************************************************
 * BST :: FIND
 * Return the node corresponding to a given value
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: find(const T & t)
{
   BinaryNode<T>* search = root;
   bool run = true;
   Stack<BinaryNode<T>* > myStack;
   while(search != NULL)
   {
      if(search->data == t)
      {
         BSTIterator<T> myIterator = begin();
         while(*myIterator != t)
            myIterator++;
         return myIterator;
      }
      else if(search->data <= t)
      {
         search = search->pRight;
      }
      else if(search->data > t)
      {
         search = search->pLeft;
      }
   }
   return end();


}
/***********************
 * Makes a copy of a BST
 * @tparam T
 * @param rhs
 * @return
 */
template<class T>
BinaryNode<T>* BST<T>::copy(BinaryNode<T>* rhs)
{
   //VLR Prefix style
   if(rhs == NULL)
      return NULL;
   //Copy This node
   BinaryNode<T>* newNode = new BinaryNode<T>(rhs->data);
   //set pleft to a returned copy of the left node
   newNode->pLeft = copy(rhs->pLeft);
   //set pright to a returned copy of the right node
   newNode->pRight = copy(rhs->pRight);
   return newNode;
}



/**********************************************************
 * BINARY SEARCH TREE ITERATOR
 * Forward and reverse iterator through a BST
 *********************************************************/
template <class T>
class BSTIterator
{
public:
   // constructors
   BSTIterator(BinaryNode <T> * p = NULL)    { nodes.push(p);  }
   BSTIterator(Stack <BinaryNode <T> *> & s) { nodes = s;         }
   BSTIterator(const BSTIterator <T> & rhs)  { nodes = rhs.nodes; }

   // assignment
   BSTIterator <T> & operator = (const BSTIterator <T> & rhs)
   {
      // need an assignment operator for the Stack class.
      nodes = rhs.nodes;
      return *this;
   }

   // compare
   bool operator == (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() == nodes.const_top();
   }
   bool operator != (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() != nodes.const_top();
   }

   // de-reference. Cannot change because it will invalidate the BST
   T & operator * ()
   {
      if(nodes.top() != NULL)
         return nodes.top()->data;
   }

   // iterators
   BSTIterator <T> & operator ++ ();
   BSTIterator <T>   operator ++ (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      ++(*this);
      return itReturn;
   }
   BSTIterator <T> & operator -- ();
   BSTIterator <T>   operator -- (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      --(*this);
      return itReturn;
   }

   // must give friend status to remove so it can call getNode() from it
   friend void BST <T> :: remove(BSTIterator <T> & it);

private:

   // get the node pointer
   BinaryNode <T> * getNode() { return nodes.top(); }

   // the stack of nodes
   Stack < BinaryNode <T> * > nodes;
};


/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a right node, take it
   if (nodes.top()->pRight != NULL)
   {
      nodes.push(nodes.top()->pRight);

      // there might be more left-most children
      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);
      return *this;
   }

   // there are no right children, the left are done
   assert(nodes.top()->pRight == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the left-child, got to the parent.
   if (pSave == nodes.top()->pLeft)
      return *this;

   // we are the right-child, go up as long as we are the right child!
   while (nodes.top() != NULL && pSave == nodes.top()->pRight)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}


#endif // BST_H