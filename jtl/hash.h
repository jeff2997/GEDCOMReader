//
// Created by jeff on 3/26/18.
//

#ifndef WEEK12_HASH_H
#define WEEK12_HASH_H

#include <map>
#include <list>
#include <clocale>
#include <vector>

template <class T>
class Hash
{
public:
   //Default constructor
   Hash() throw (const char *);
   //Non-default constructor
   Hash(int numBuckets) throw (const char *);
   //Copy Constructor
   Hash(const Hash &rhs) throw (const char *);
   //Destructor
   ~Hash();
   //Overloaded Assignment Operator
   Hash& operator=(const Hash& rhs) throw (const char *);
   //Inserts into the hash
   void insert(T data);
   //Returns true if empty
   bool empty();
   //Returns the size
   int size() const;
   //Returns the num of buckets
   int capacity() const;
   //Empties the hash
   void clear();
   //Returns true if the value is found
   bool find(T value);
   //Pure virtual function to be overloaded.
   virtual int hash(const T &value) const = 0;
private:
   std::list<T>* buckets;
   int myCap;
   int mySize;
};

template<class T>
Hash<T>::Hash() throw (const char *)
{
   buckets = NULL;
   myCap = 0;
   mySize = 0;
}

template<class T>
Hash<T>::~Hash()
{
   for(int i = 0; i < myCap; i++)
      buckets[i].clear();
   delete[] buckets;
}

template<class T>
Hash<T>::Hash(int numBuckets) throw (const char *)
{
   try
   {
      buckets = new std::list<T>[numBuckets];
      myCap = numBuckets;
      mySize = 0;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash.";
   }
}

template<class T>
void Hash<T>::insert(T data)
{
   int index = hash(data);
   buckets[index].push_front(data);
   mySize++;
}

template<class T>
bool Hash<T>::empty()
{
   return mySize == 0;
}

template<class T>
int Hash<T>::size() const
{
   return mySize;
}

template<class T>
int Hash<T>::capacity() const
{
   return myCap;
}

template<class T>
void Hash<T>::clear()
{
   for(int i = 0; i < myCap; i++)
      if(buckets != NULL)
         buckets[i].clear();
   mySize = 0;
}

template<class T>
bool Hash<T>::find(T value)
{
   int index = hash(value);
   for(typename std::list<T>::iterator it=buckets[index].begin();
       it != buckets[index].end(); it++)
   {
      if(*it == value) return true;
   }
   return false;
}

template<class T>
Hash<T>::Hash(const Hash &rhs) throw (const char *)
{
   try
   {
      myCap = rhs.capacity();
      buckets = new std::list<T>[rhs.capacity()];

      for (int i = 0; i < rhs.capacity(); i++)
      {
         buckets[i] = rhs.buckets[i];
      }
      mySize = rhs.size();
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash.";
   }
}

template<class T>
Hash<T>& Hash<T>::operator=(const Hash &rhs) throw (const char *)
{
   try
   {
      clear();
      myCap = rhs.capacity();
      buckets = new std::list<T>[rhs.capacity()];

      for (int i = 0; i < rhs.capacity(); i++)
      {
         buckets[i] = rhs.buckets[i];
      }
      mySize = rhs.size();
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash.";
   }
}


#endif //WEEK12_HASH_H
