//
// Created by jeff on 4/2/18.
//

#ifndef WEEK13_FAMILYTREE_H
#define WEEK13_FAMILYTREE_H
#include <string>
#include "jtl/vector.h"

struct person;

//A simple container for dates
struct date
{
   date() = default;
   ~date() = default;
   int day;
   std::string month;
   std::string year;
};
/*****************************
 * This is my custom modified list class
 * the person objects act as nodes
 */
class familytree
{
public:
   //default constructor
   familytree();
   //default deconstructor
   ~familytree() = default;

   //Public data types
   int size;
   person* start;
   person* sortedStart;
   //inserts a person pointer
   void insert(person*);

};


/******************************
 * Contains many simple data types for a person
 */
struct person
{
   person();
   ~person() = default;
   std::string wholename;
   std::string givenname;
   std::string surname;
   std::string sex;
   std::string birthplace;
   date* bdate;
   date* ddate;
   std::string bplace;
   std::string dplace;
   unsigned long id;
   person* mother;
   person* father;
   person* next;
   person* previous;
   person* sNext;
   person* sPrevious;
   Vector<person>* children;
   bool operator < (const person& rhs);
   bool operator > (const person& rhs);
   std::ostream& operator << (std::ostream& out);
   void level();
};





#endif //WEEK13_FAMILYTREE_H
