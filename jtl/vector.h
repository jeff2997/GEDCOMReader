/***********************************************************************
* Header:
*    Vector - Week 01, CS 235
* Summary:
*    This class is based on the Vector Class by Brother Helfrich
*    and is a simple replication of a Vector. It can accept any data type
*    and will modify itself to allow for any amount of storage within.
*
*    This will contain the class definition of:
*        Vector         : A class that holds stuff
*        VectorIterator : An interator through Container
* Author
*    Jeffrey Pearson
************************************************************************/

#ifndef CONTAINER_H
#define CONTAINER_H

#include <cassert>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

/************************************************
 * VECTOR
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
    // default constructor : empty and kinda useless
    Vector() : numItems(0), cap(0), data(NULL) {}

    // copy constructor : copy it
    Vector(const Vector & rhs) throw (const char *);

    // non-default constructor : pre-allocate
    Vector(int capacity) throw (const char *);

    // destructor : free everything
    ~Vector()        { if (data != NULL) delete [] data; }

    // is the container currently empty
    bool empty() const  { return numItems == 0;         }

    // remove all the items from the container
    void clear()        { numItems = 0;                 }

    // how many items are currently in the container?
    int size() const    { return numItems;              }

    // what is the size of the container?
    int capacity() const { return cap;                 }

    // add an item to the container
    void push_back(const T &t) throw (const char *);

    //Add [] operator overload
    T & operator[] (int value);

    //Add [] operator overloaded (const)
    T & operator[] (int value) const;

    //Add Assignment operator overload
    //For some reason this does not want a declaration
    //And definition
    Vector & operator=(Vector const& rhs)
    {
       //Delete everything in me
       if (data != NULL) delete [] data;
       //add values from rhs
       const int CAPACITY = rhs.capacity();
       data = new T[rhs.capacity()];
       this->cap = CAPACITY;
       int test1 = -1;
       int test2 = -1;
       for (int i = 0; i < rhs.size(); i++)
       {
          test2 = rhs[i];
          data[i] = rhs[i];
          test1 = data[i];
       }
       this->numItems = rhs.size();
       return *this;
    }

    // return an iterator to the beginning of the list
    VectorIterator <T> begin() { return VectorIterator<T>(data); }

    // return an iterator to the end of the list
    VectorIterator <T> end() { return VectorIterator<T>(data + numItems);}

private:
    T * data;          // dynamically allocated array of T
    int numItems;      // how many items are currently in the Container?
    int cap;           // how many items can I put on the Container before full?
};

/**************************************************
 * CONTAINER ITERATOR
 * An iterator through Container
 *************************************************/
template <class T>
class VectorIterator
{
public:
    // default constructor
    VectorIterator() : p(NULL) {}

    // initialize to direct p to some item
    VectorIterator(T * p) : p(p) {}


    // not equals operator
    bool operator != (const VectorIterator & rhs) const {
       return rhs.p != this->p;
    }

    //operator two
    bool operator != (VectorIterator & rhs) {
       return rhs.p != this->p;
    }

    // dereference operator
    T & operator * ()
    {
       return *p;
    }

    // prefix increment
    VectorIterator <T> & operator ++ ()
    {
       p++;
       return *this;
    }

    // postfix increment
    VectorIterator <T> operator++(int postfix)
    {
       VectorIterator tmp(*this);
       p++;
       return tmp;
    }

private:
    T * p;
};

/*******************************************
 * CONTAINER :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);

   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < cap; i++)
      data[i] = T();
}

/**********************************************
 * CONTAINER : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int capacity) throw (const char *)
{
   assert(capacity >= 0);

   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }


   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

/***************************************************
 * VECTOR :: PUSH_BACK
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Vector <T> :: push_back(const T &t) throw (const char *)
{
   //Multiplier for the new array creation
   const int TO_DOUBLE = 2;
   const int DEFAULT_MAX = 1;
   int capStore = 0;

   //Increment numItems to account for the addition
   //Make sure the value will fit
   if (numItems < cap)
   {
      //If Space then
      //Add Value
      data[numItems++] = t;
   }
      //Make sure capacity is not 0
   else
   {
      capStore = cap;
      cap = (cap > 0) ? (cap *= TO_DOUBLE) : DEFAULT_MAX;
      //Create swap array
      T* swap = new T[capStore];

      //Read into swap array
      for (int i = 0; i < capStore; i++)
      {
         swap[i] = data[i];
      }

      //Delete the old vector, create a new one
      //(twice the size), copy all values into it
      T* newVectorStore = new T[cap];
      if (data != NULL)
      {
         for (int j = 0; j < capStore; j++)
         {
            newVectorStore[j] = swap[j];
         }
      }

      //Delete the old array
      delete[] data;

      //Point to the new one
      data = &newVectorStore[0];

      //Add the new value on the end
      data[numItems++] = t;
   }
}

template<class T>
T &Vector<T>::operator[](int value) const {
   if (value < cap && value >= 0)
   {
      return data[value];
   }
   else
   {
      throw "ERROR: Invalid value " && value && " requested";
   }
}

template<class T>
T &Vector<T>::operator[](int value) {
   if (value < cap && value >= 0)
   {
      return data[value];
   }
   else
   {
      throw "ERROR: Invalid value " && value && " requested";
   }
}

#endif // CONTAINER_H
