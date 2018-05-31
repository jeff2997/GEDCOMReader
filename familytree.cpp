//
// Created by jeff on 4/2/18.
//

#include <iostream>
#include <iomanip>
#include "familytree.h"

using namespace std;

person::person()
{
   wholename = "";
   givenname = "";
   surname = "";
   sex = "";
   birthplace = "";
   bdate = new date();
   ddate = new date();
   bplace = "";
   dplace = "";
   id = NULL;
   mother = NULL;
   father = NULL;
   previous = NULL;
   next = NULL;
   sPrevious = NULL;
   sNext = NULL;
   children = new Vector<person>;
}

bool person::operator<(const person &rhs)
{
   if(this->surname < rhs.surname)
      return true;
   else if(this->surname > rhs.surname)
      return false;
   else
   {
      if(this->givenname < rhs.givenname)
         return true;
      else if(this->givenname > rhs.givenname)
         return false;
      else
      {
         if(this->bdate->year < rhs.bdate->year)
            return true;
         else
            return false;
      }
   }
}

bool person::operator>(const person &rhs)
{
   if(this->surname > rhs.surname)
      return true;
   else if(this->surname < rhs.surname)
      return false;
   else
   {
      if(this->givenname > rhs.givenname)
         return true;
      else if(this->givenname < rhs.givenname)
         return false;
      else
      {
         if(this->bdate->year > rhs.bdate->year)
            return true;
         else
            return false;
      }
   }
}

std::ostream& person::operator<<(std::ostream& out)
{
   out << givenname << " " << surname << endl;
   return out;
}



familytree::familytree()
{
   size = 0;
   start = NULL;
   sortedStart = NULL;
}

void familytree::insert(person* rhs)
{
   //Check if this is smaller than the start
   //If so, make this the previous of next
   //and that the next of this, and reset start
   if(start == NULL)
   {
      start = rhs;
      sortedStart = rhs;
   }
   else
   {
      person* temp = start;
      while(temp->next)
         temp = temp->next;
      temp->next = rhs;
   }
   person* tempfind = sortedStart;
   bool inserted = false;
   string temp;
   temp = rhs->surname;
   string tempfindtemp = tempfind->surname;
   for(int i = 0; i < temp.size(); i++)
      temp[i] = toupper(temp[i]);

   if(size != 0)
      while(!inserted)
      {
         tempfindtemp = tempfind->surname;
         for(int i = 0; i < tempfindtemp.size(); i++)
            tempfindtemp[i] = toupper(tempfindtemp[i]);
         bool lessthan = false;
         if(temp < tempfindtemp)
            lessthan = true;
         else if(temp > tempfindtemp)
            lessthan = false;
         else if(rhs->givenname < tempfind->givenname)
            lessthan = true;
         else if(rhs->givenname > tempfind->givenname)
            lessthan = false;
         else if(rhs->bdate->year < tempfind->bdate->year)
            lessthan = true;
         else
            lessthan = false;
         if(lessthan)
         {
            //insert
            rhs->sNext = tempfind;
            rhs->sPrevious = tempfind->sPrevious;
            if(tempfind->sPrevious)
               tempfind->sPrevious->sNext = rhs;
            else
               sortedStart = rhs;
            rhs->sPrevious = tempfind->sPrevious;
            tempfind->sPrevious = rhs;
            inserted = true;
         }
         else if(!lessthan && tempfind->sNext)
         {
            tempfind = tempfind->sNext;
         }
         else
         {
            //insert
            rhs->sNext = NULL;
            rhs->sPrevious = tempfind;
            tempfind->sNext = rhs;
            inserted = true;
         }
      }

   size++;
}

void person::level()
{
   const int MAX = 300;
   person* queue[MAX];
   person* temp;
   int front = 0;
   int back = 0;
   int genFind = 1;
   int curGen = 1;

   queue[back++] = this;
   cout << "The Ancestors of " << wholename << ":" << endl;
   while (front != back)
   {

      //This prints out the text for each generation
      if(front == genFind && queue[genFind] != NULL)
      {
         genFind = back;
         switch(curGen)
         {

            case(1):
            {
               cout << "Parents:" << endl;
               break;
            }
            case(2):
            {
               cout << "Grandparents:" << endl;
               break;
            }
            case(3):
            {
               cout << "Great Grandparents:" << endl;
               break;
            }
            default:
            {
               if(curGen == 4)
                  cout << "2nd";
               else if(curGen == 5)
                  cout << "3rd";
               else
                  cout << curGen - 2 << "th";

               cout << " Great Grandparents:" << endl;
               break;
            }

         }
         curGen++;
      }
      temp = queue[front];
      front = (front + 1) % MAX;

      if (temp != NULL)
      {
         // visit if not the first, so we don't repeat anyone
         if(temp != queue[0])
         {
            cout << "        ";
            cout << temp->givenname;
            if (temp->givenname != "" && temp->surname != "")
               cout << " ";
            if (temp->surname != "")
               cout << temp->surname;
            if (temp->bdate->month != "" || temp->bdate->day != NULL || temp->bdate->year != "")
               cout << ", b.";
            if (temp->bdate->day != NULL &&
                temp->bdate->month != "") //This tidies things up if there's a day but not a month
               cout << " " << temp->bdate->day;
            if (temp->bdate->month != "")
               cout << " " << temp->bdate->month;
            if (temp->bdate->year != "")
               cout << " " << temp->bdate->year;
            cout << endl;
            // end Visit
         }

         queue[back] = temp->father;
         back = (back + 1) % MAX;
         queue[back] = temp->mother;
         back = (back + 1) % MAX;

      }
   }
}


