/***********************************************************************
* Header:
*    Vector - Week 02, CS 235
* Summary:
*    This class is a replica of the std stack class.
*
*    This will contain the class definition of:
*        Stack         : A stack that operates FILO
* Author
*    Jeffrey Pearson
************************************************************************/

#ifndef WEEK02_STACK_H
#define WEEK02_STACK_H
using namespace std;

template <class T>
class Stack
{
public:
   //Overloaded Constructor
   explicit Stack <T> (int definedSize = 0);

   //Copy Constructor
   Stack(const Stack<T> &source);

   //Destructor
   ~Stack() = default;

   //Empty
   //Returns a bool that states if the stack is empty
   bool empty();

   //Size
   //Returns an integer of the current size of the stack
   int size();

   //Capacity
   //Returns an int of the max capacity of the stack
   int capacity();

   //Clear
   //Empties the array
   void clear();

   //Push
   //adds a number to the top of the stack
   void push(T insertValue);

   //Pop
   //Takes a value off the top of the stack
   void pop();

   //Top
   //Returns the current value of the top item in the stack
   T top();

   // The operator= overload
   // Copies the stack from what is given
   Stack& operator=(const Stack& source);

   friend ostream& operator<<(ostream& lhs, Stack& rhs)
   {
      lhs << "{ ";
      for (int i=0; i<rhs.currentLocation; i++)
      lhs << rhs.data[i] << " ";
      lhs << "}";
      return lhs;
   }
private:
   //Stores the current location of the top of the stack
   int currentLocation{};
   //Stores the capacity
   int max;
   //Stores current size
   T* data;
   //denotes if there is nothing there
   bool last = true;
   //The sizeUp function
   //Increases the size of the usable space
   void sizeUp();
};

template<class T>
Stack<T>::Stack(int definedSize)
{
   //Initialize currentLocation, max, currentSize, and the data array;
   currentLocation = 0;
   max = definedSize;
   data = new T[definedSize];
}



template<class T>
bool Stack<T>::empty()
{
   return currentLocation  -1 < 0;
}

template<class T>
int Stack<T>::size()
{
    return currentLocation;
}

template<class T>
int Stack<T>::capacity()
{
    return max;
}

template<class T>
void Stack<T>::clear()
{
   currentLocation = 0;
}

template<class T>
void Stack<T>::push(T insertValue)
{
   try
   {
      //check if value will interfere
      //if not, add a value to the top of the stack
      if (currentLocation < max && currentLocation != 0)
      {
         data[currentLocation++] = insertValue;
      }
      else
      {
         //Increase size, then push item
         sizeUp();
         data[currentLocation++] = insertValue;
      }
   }
   catch (const char *)
   {
      throw "ERROR: Unable to allocate new buffer for Stack";
   }
}

template<class T>
void Stack<T>::pop()
{
   if (currentLocation > 0)
   {
       currentLocation--;
   }
   else if (currentLocation == 0 && last == false)
   {
       last = true;
   }
   else
   {
       throw "ERROR: Unable to pop from an empty Stack";
   }
}

template<class T>
T Stack<T>::top()
{
   if (!last)
      return data[currentLocation - 1];
   else
      throw "ERROR: Unable to reference the element from an empty Stack";
}

template<class T>
void Stack<T>::sizeUp()
{
   if (currentLocation == 0)
   {
      last = false;
      delete[] data;
      max = 1;
      data = new T[max];
   }
   else
   {
      //double the size of the array
      const int newMax = max*2;
      T* temp = new T[newMax];
      //Copy data between arrays
      for (int i = 0; i < currentLocation; i++)
         temp[i] = data[i];
      delete[] data;
      data = &temp[0];
      max = newMax;
   }
}

template<class T>
Stack<T> &Stack<T>::operator=(const Stack &source) {
   //Delete the old one
   delete [] data;
   //Make a new array of the new max size
   try { data = new T[source.max]; }
   catch (const char *)
   {
      throw "ERROR: Unable to allocate a new buffer for Stack";
   }
   //Set the variables here to match
   currentLocation = source.currentLocation;
   max = source.max;
   //Iterate through the values in the other one, till they match
   for (int i = 0; i <= source.currentLocation; i++)
   {
      this->data[i] = source.data[i];
      currentLocation = i;
   }
   return *this;
}

template<class T>
Stack<T>::Stack(const Stack<T> &source) {
   //Set the variables here to match
   currentLocation = source.currentLocation;
   max = source.max;
   //Make a new array of the new max size
   data = new T[source.max];

   //Iterate through the values in the other one, till they match
   for (int i = 0; i <= currentLocation; i++)
   {
      this->data[i] = source.data[i];
      this->currentLocation = i;
      //cout << "currentLocation: " << currentLocation << endl;
      //cout << "this->data[i]: " << this->data[i] << endl;
      //cout << "i: " << i << endl;
      //cout << "source.data[i]: " << source.data[i] << endl;
   }
}


#endif //WEEK02_STACK_H
