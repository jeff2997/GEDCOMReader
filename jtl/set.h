/*******************************************************
 * Program: Set
 *      Week 05, Set
 *      Brother Ercanbrack, CS 235
 *  Author:
 *  Jeffrey Pearson
 *
 */

#ifndef WEEK05_SET_H
#define WEEK05_SET_H

#include <clocale>

//Forward declaration of SetIterator
template <class T>
class SetIterator;

/***************************************
 * The Set Class
 * Imitates the STL set and
 * Uses fancy c++ to make things happen
 */
template <class T>
class Set
{
public:
    /***********************
     * Default Constructor
     */
    Set();
    /***********************
     * Copy Constructor
     * @param copy
     */
    Set(const Set<T>& copy);
    /***********************
     * Constructor that takes a size
     * @param cap
     */
    explicit Set(int cap);
    /***********************
     * Default Destructor
     */
    ~Set() = default;
    /***********************
     * Overloaded Assignment Operator
     * @param rhs
     * @return
     */
    Set<T>& operator=(const Set& rhs);
    /***********************
     * empty()
     * @return true if empty
     */
    bool empty() { return iSize == 0; };
    /***********************
     * size()
     * @return an int of the size
     */
    int size() { return iSize; };
    /***********************
     * capacity()
     * @return an int of the capacity
     */
    int capacity() { return iCap; };
    /***********************
     * clear()
     * empties the set
     */
    void clear() { iSize = 0; };
    /***********************
     * erase()
     * erases the value passed
     * @param value
     */
    void erase(int loc);
    /***********************
     * find()
     * returns the index of the value passed
     * @param value
     * @return
     */
    int find(T value);
    /***********************
     * The overloaded intersection operator
     * @param rhs
     * @return
     */
    Set<T> operator&&(Set& rhs);
    /***********************
     * The overloaded union operator
     * @param rhs
     * @return
     */
    Set<T> operator||(const Set& rhs);
    // return an iterator to the beginning of the list
    SetIterator <T> begin() { return SetIterator<T>(data); }

    // return an iterator to the end of the list
    SetIterator <T> end() { return SetIterator<T>(data + iSize);}
    /***********************
     * insert() adds an object to the array
     * @param iThing
     */
    void insert(T iThing);

private:
    int iSize;
    int iCap;
    T* data;
    /***********************
     * iReallocate()
     * reallocates the internal array
     */
    void iReallocate();
    /***********************
     * iReallocate(int newSize)
     * reallocates like the above function, but
     * allows the size to be manually set
     */
    void iReallocate(int newSize);
    /***********************
     * iFindValue() finds an object
     * and returns it's location
     * @param iObject
     */
    int iFindValue(T iObject);

   /************************
    * iDelete() deletes an item
    * @param iLocation
    */
    void iDelete(int iLocation);

};

template<class T>
Set<T>::Set()
{
   data = new T[0];
   iSize = 0;
   iCap = 0;
}

template<class T>
Set<T>::Set(const Set<T>& copy)
{
    //make sure that this is big enough
    data = new T[copy.iCap];
    //once we are large enough, copy in the things
    //from copy

    for (int i = 0; i < copy.iSize; i++)
    {
        data[i] = copy.data[i];
    }
    //Set variables to match
    iSize = copy.iSize;
    iCap = copy.iCap;
}

template<class T>
Set<T>::Set(int cap)
{
   data = new T[cap];
   iCap = cap;
   iSize = 0;
}

template<class T>
Set<T> &Set<T>::operator=(const Set& rhs)
{
    //This will function similarly to the copy constructor
    //First check if we are large enough
    //If not, reallocate
    if (empty() || iCap < rhs.iSize)
        iReallocate();
    //Copy in all the things from rhs
    for (int i = 0; i < rhs.iSize; i++)
    {
        data[i] = rhs.data[i];
    }
    //Then set our variables to match
    iCap = rhs.iCap;
    iSize = rhs.iSize;
}

template<class T>
void Set<T>::erase(int loc)
{
    //int iLocation = iFindValue(value);
    iDelete(loc);
}

template<class T>
int Set<T>::find(T value)
{
   int iBegin = 0;
   int iEnd = iSize - 1;
   int iMiddle = -1;
   while(iBegin <= iEnd)
   {
      iMiddle = (iBegin + iEnd) / 2;
      if(data[iMiddle] == value)
         return iMiddle;
      else if(value < data[iMiddle])
         iEnd = iMiddle - 1;
      else
         iBegin = iMiddle + 1;
   }
   return -1;
}

template<class T>
Set<T> Set<T>::operator&&(Set &rhs)
{
    Set newSet;
    //Pull a value from Set 1
    for(int i = 0; i < iSize; i++)
    {
        //Is it in set 2?
        //Then put it in the newSet
        if(rhs.find(data[i]) != -1)
        {
            newSet.insert(data[i]);
        }
    }
    return newSet;
}

template<class T>
Set<T> Set<T>::operator||(const Set &rhs)
{
    Set newSet(*this);
    for(int i = 0; i < rhs.iSize; i++)
    {
        newSet.insert(rhs.data[i]);
    }
    return newSet;
}

template<class T>
void Set<T>::iReallocate()
{

    //check if size is 0
    if(iCap == 0)
    {
        //if so, make the size 1
        iCap = 1;
        delete[] data;
        data = new T[iCap];
    }
    //if not, double the size
    else
    {
        //save the old capacity
        int iPac = iCap;
        //make a new array twice the size
        //and set the new capacity
        iCap *= 2;
        T* newData = new T[iCap];
        //for each item in the array, copy
        //into the new array
        for (int i = 0; i < iPac; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = &newData[0];
    }
}

template<class T>
void Set<T>::iReallocate(int newSize)
{
    //check that the newSize is larger
    //than what we have
    //if not, don't reallocate
    if(newSize > iCap)
    {
        //if so, save the old capacity
        int iPac = iCap;
        //make a new array with the new size
        //and set the new capacity
        iCap = newSize;
        T* newData = new T[iCap];
        //for each item in the array, copy
        //into the new array
        for(int i = 0; i < iPac; i++)
        {
            newData[i] = data[i];
        }
    }
}

template<class T>
int Set<T>::iFindValue(T iObject)
{
   int iBegin = 0;
   int iEnd = iSize - 1;
   int iMiddle = 0;
   while(iBegin <= iEnd)
   {
      iMiddle = (iBegin + iEnd) / 2;
      if(iObject == data[iMiddle])
         return iMiddle;
      else if(iObject < data[iMiddle])
         iEnd = iMiddle - 1;
      else
         iBegin = iMiddle + 1;
   }
   return iBegin;

}

template<class T>
void Set<T>::iDelete(int iLocation)
{
    if (iLocation != -1)
    {
        //Make a new array of the same size
        T* newData = new T[iCap];
        //make a for loop that copies all the data
        int iProCounter = 0;
        for(int i = 0; i < iSize; i++)
        {
            //add a check that will immediately increment i by an
            //additional value when i == the location
            if(i != iLocation)
            {
                newData[iProCounter] = data[i];
                iProCounter++;
            }
        }
        //fix iSize
        iSize--;
        //When done, delete the old array
        delete[] data;
        //and set data to the new one
        data = &newData[0];
    }
}

template<class T>
void Set<T>::insert(T iThing)
{  //Check if duplicate
   if(find(iThing) == -1)
   {
      if(iCap < iSize + 1)
         iReallocate();
      //Check size
      int iInsert = iFindValue(iThing);

      if(data[iInsert] != iThing && iInsert >= 0)
      {

         T hold1 = 0;
         T hold2 = 0;
         if (iInsert >= 0)
            hold1 = data[iInsert];
         for(int i = iInsert; i < iSize; i++)
         {
            hold2 = data[i + 1];
            data[i + 1] = hold1;
            hold1 = hold2;
         }
         if (iInsert >= 0)
            data[iInsert] = iThing;
         iSize++;
      }
   }
}


/**************************************************
 * SET ITERATOR
 * An iterator through Set
 *************************************************/
template <class T>
class SetIterator
{
public:
    // default constructor
    SetIterator() : p(NULL) {}

    // initialize to direct p to some item
    SetIterator(T * p) : p(p) {}


    // not equals operator
    bool operator != (const SetIterator & rhs) const {
        return rhs.p != this->p;
    }

    //operator two
    bool operator != (SetIterator & rhs) {
        return rhs.p != this->p;
    }

    // dereference operator
    T & operator * ()
    {
        return *p;
    }

    // prefix increment
    SetIterator <T> & operator ++ ()
    {
        p++;
        return *this;
    }

    // postfix increment
    SetIterator <T> operator++(int postfix)
    {
        SetIterator tmp(*this);
        p++;
        return tmp;
    }

private:
    T * p;
};

#endif //WEEK05_SET_H
