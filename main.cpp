//
// Created by jeff on 4/2/18.
//
#include <iostream>
#include <fstream>
#include <cmath>
#include "jtl/list.h"
#include "familytree.h"
using namespace std;

int main(int argc, char** argv)
{

   fstream gedcomfile;

   string temp = "";
   string next = "0";
   string filename = "/home/jeff/Dev/cs235/week13/cameron.ged";
   string command;
   bool bDate = false;
   bool dDate = false;
   bool interface = true;
   bool verbose = true;
   bool verboseConfig = false;
   bool sort = false;
   bool generations = false;
   bool run = true;
   bool saveSort = true;
   int last = 0;
   int numGenerations = 8;

   familytree myTree;
   person *tPerson = new person;
   gedcomfile >> temp;

   if(argc > 1)
   {
      if(argc > 2)
      {
         cout << "Usage: a.out filetoread.ged" << endl;
         return 0;
      }
      interface = false;
      run = true;
      generations = true;
         try
         {
            gedcomfile.open(argv[1], iostream::in);
         }
         catch(const char *)
         {
            throw "File did not open";
         }
         if(!gedcomfile.is_open())
         {
            cout << "Could not open file: " << argv << endl;
            return 1;
         }
   }


   //BEGIN USER INTERFACE
   while(interface)
   {
      while(!gedcomfile.is_open())
      {
         cout << "What file would you like to open?" << endl << "\t> ";
         cin >> filename;
         try
         {
            gedcomfile.open(filename.c_str(), iostream::in);
         }
         catch(const char *)
         {
            throw "File failed to open";
         }
         if(!gedcomfile.is_open())
            cout << "Could not open file: " << filename << ". Please try again." << endl;
      }

      if(verbose || verboseConfig)
      {
         cout << "Available commands: " << endl;
         cout << "sort - Displays an alphabetically sorted list of names from your file." << endl;
         cout << "generations - Displays a specified number of generations, starting from "
                 "the most recent" << endl;
         cout << "config - Allows you to change settings" << endl;
         cout << "help - Display the help menu" << endl;
         cout << "quit - Quits the program" << endl;
         if(!verboseConfig)
            verbose = false;
      }
      cout << "Enter Command: ";
      cin >> command;
      if(command == "sort")
      {
         sort = true;
         interface = false;
      }
      else if(command == "generations")
      {
         generations = true;
         interface = false;
      }
      else if(command == "help")
      {
         verbose = true;
      }
      else if(command == "config")
      {
         bool settings = true;
         while(settings)
         {
            string select;
            cout << "Settings-------------------------------------------------------" << endl;
            cout << "1 Verbose Mode------------------------------------------";
            if(verboseConfig) cout << "enabled" << endl; else cout << "disabled" << endl;
            cout << "2 Save sorted.dat---------------------------------------" << saveSort << endl;
            cout << "To change a setting, enter its number. Type 'back' to exit" << endl;
            cout << "\t>";
            cin >> select;
            if(select == "1")
            {
               string newValue;
               cout << "Verbose Mode: " << endl;
               cout << "Current Value: " << verboseConfig << endl;
               cout << "Accepted Values: enabled, disabled" << endl;
               cout << "New value: ";
               cin >> newValue;
               if(newValue == "enabled")
               {
                  verboseConfig = true;
               }
               else if(newValue == "disabled")
               {
                  verboseConfig = false;
               }
               else
               {
                  cout << "Invalid value, setting not changed." << endl;
               }
            }
            else if(select == "2")
            {
               string newValue;
               cout << "Save sorted.dat?:" << endl;
               cout << "Current value: " << saveSort << endl;
               cout << "Accepted values: true or false" << endl;
               if(newValue == "true")
               {
                  verboseConfig = true;
               }
               else if(newValue == "false")
               {
                  verboseConfig = false;
               }
               else
               {
                  cout << "Invalid value, setting not changed." << endl;
               }
            }
            else if(select == "back")
            {
               settings = false;
            }
            else
            {
               cout << "Invalid command. Please try again" << endl;
            }
         }

      }
      else if(command == "quit")
      {
         interface = false;
         run = false;
      }
      else
      {
         cout << "Invalid command. Please try again" << endl;
      }
   }

//   END USER INTERFACE-------------------------------------------------------------------------
//   BEGIN MAIN PROGRAM-------------------------------------------------------------------------

if(run)
{
   while (!gedcomfile.eof())
   {
      if (temp == "0" && next == "0" || (next == "FAM") || (temp == "FAM"))
      {
         last = 0;
         if(next[0] != '@' && next[1] != 'F')
            gedcomfile >> next;

         if (next[0] == '@' && next[1] == 'I')
         {
            //Then we are in an individual person.
            //Get their ID.
            string idhold = "";
            for (int i = 0; i < next.size(); i++)
            {
               if (isdigit(next[i])) idhold += (next[i]);
            }
            tPerson->id = atoi(idhold.c_str());

         }
         else if(next[0] == '@' && next[1] == 'F')
         {
            person* dad = NULL;
            person* mom = NULL;
            person* child = NULL;
            bool test = false;
            string replace = "";

            gedcomfile >> next;
            gedcomfile >> temp;
            if(isdigit(next[0]) && !isdigit(temp[0])) swap(next, temp);
            //This skips empty families
            if(temp == "0")
               temp = "1";

            while(temp == "1") //Until we reach the next family
            {
               if(next == "HUSB")
               {
                  gedcomfile >> next;
                  if(next == "0") break;
                  string idhold = "";
                  int realID = 0;
                  for (int i = 0; i < next.size(); i++)
                  {
                     if (isdigit(next[i])) idhold += (next[i]);
                  }
                  realID = atoi(idhold.c_str());
                  dad = myTree.start;
                  for(int i = 1; i < realID; i++)
                     if(dad->id != realID)
                        dad = dad->next;
               }
               else if(next == "WIFE")
               {
                  //Get ID
                  gedcomfile >> next;
                  if(next == "0") break;
                  string idhold = "";
                  int realID = 0;
                  for (int i = 0; i < next.size(); i++)
                  {
                     if (isdigit(next[i])) idhold += (next[i]);
                  }
                  realID = atoi(idhold.c_str());
                  mom = myTree.start;
                  for(int i = 1; i < realID; i++)
                     if(mom->id != realID)
                        mom = mom->next;
               }
               else if(next == "CHIL")
               {
                  //Get ID
                  gedcomfile >> next;
                  if(next == "0") break;
                  string idhold = "";
                  int realID = 0;
                  for (int i = 0; i < next.size(); i++)
                  {
                     if (isdigit(next[i])) idhold += (next[i]);
                  }
                  realID = atoi(idhold.c_str());
                  //Go to child
                  child = myTree.start;
                  for(int i = 1; i <= realID; i++)
                     if(child->id != realID)
                        child = child->next;
                  child->mother = mom;
                  child->father = dad;
               }
               else if(temp == "0")
               {
                  temp = "1";
               }
               else if (isdigit(next[0]))
                  temp = next;
               gedcomfile >> next;
            }

               temp = next;
         }

         if(temp != next)
         {
            temp = next + "1";
         }

      } else if (temp == "1")
      {
         if (last > 1)
         {
            bDate = false;
            dDate = false;
         }
         last = 1;
         gedcomfile >> next;
         if (next == "NAME" && tPerson->id != NULL)
         {
            gedcomfile >> next;
            while (next != "1" && next != "2" && next != "3")
            {
               tPerson->wholename += next;
               gedcomfile >> next;
               if (next != "1" && next != "2" && next != "3")
                  tPerson->wholename += " ";
               for (int i = 0; i < tPerson->wholename.size(); i++)
                  if (ispunct(tPerson->wholename[i]))
                     tPerson->wholename.erase(i, 1);
            }
            temp = next;

         } else if (next == "SEX")
         {
            gedcomfile >> next;
            tPerson->sex = next;
         } else if (next == "BIRT")
            bDate = true;
         else if (next == "DEAT")
            dDate = true;

      } else if (temp == "2")
      {
         if (last > 2)
         {
            bDate = false;
            dDate = false;
         }
         last = 2;
         gedcomfile >> next;
         if (next == "GIVN")
         {
            gedcomfile >> next;
            while (next != "1" && next != "2" && next != "3")
            {
               tPerson->givenname += next;
               gedcomfile >> next;
               if (next != "1" && next != "2" && next != "3")
                  tPerson->givenname += " ";
            }
            temp = next;
         }
         else if (next == "SURN")
         {
            gedcomfile >> next;
            while (next != "1" && next != "2" && next != "3")
            {
               tPerson->surname += next;
               gedcomfile >> next;
               if (next != "1" && next != "2" && next != "3")
                  tPerson->surname += " ";
            }
            temp = next;
         }
         else if (next == "DATE" && bDate == true)
         {
            string test;
            string test2;
            gedcomfile >> next;
            gedcomfile >> test;

            if (test != "1" && test != "2" && test != "3")
            {
               gedcomfile >> test2;
               if (test2 != "1" && test2 != "2" && test2 != "3")
               {
                  //Normal Date
                  tPerson->bdate->day = atoi(next.c_str());
                  tPerson->bdate->month = test;
                  tPerson->bdate->year = test2;
               } else
               {
                  //Month and Year
                  tPerson->bdate->month = next;
                  tPerson->bdate->year = test;
               }
            } else
            {
               //Just Year
               tPerson->bdate->year = next;
            }
            next = test;
            bDate = false;
         }
         else if (next == "DATE" && dDate == true)
         {
            string test;
            string test2;
            gedcomfile >> next;
            gedcomfile >> test;

            if (test != "1" && test != "2" && test != "3")
            {
               gedcomfile >> test2;
               if (test2 != "1" && test2 != "2" && test2 != "3")
               {
                  //Normal Date
                  tPerson->ddate->day = atoi(next.c_str());
                  tPerson->ddate->month = test;
                  tPerson->ddate->year = atoi(test2.c_str());
               } else
               {
                  //Month and Year
                  tPerson->ddate->month = next;
                  tPerson->ddate->year = atoi(test.c_str());
               }
            }
            else
            {
               //Just Year
               tPerson->ddate->year = atoi(test.c_str());
            }
            next = test;
            dDate = false;
         }
         else temp = next;

      }
      if (temp == "0" && next != "0" && (tPerson->givenname != "" || tPerson->wholename != ""))
      {
         myTree.insert(tPerson);
         tPerson = new person;
         next = temp;
      }
      else if (temp == "0" && next != "0" && (tPerson->givenname == "" || tPerson->wholename == ""))
         next = temp;
      if (temp == "" || temp != next || !isdigit(temp[0]))
      {
         gedcomfile >> temp;
      }
   }

   //Save to file if enabled
   if(saveSort)
   {
      string fileOut = "sorted.dat";
      fstream fout;
      fout.open(fileOut.c_str(), iostream::out);
      person *newTemp = myTree.sortedStart;
      for (int i = 0; i < myTree.size; i++)
      {
         //Sorts and points to the correct location
         fout << newTemp->givenname;
         if (newTemp->givenname != "" && newTemp->surname != "")
            fout << " ";
         if (newTemp->surname != "")
            fout << newTemp->surname;
         if (newTemp->bdate->month != "" || newTemp->bdate->day != NULL || newTemp->bdate->year != "")
            fout << ", b.";
         if (newTemp->bdate->day != NULL &&
             newTemp->bdate->month != "") //This tidies things up if there's a day but not a month
            fout << " " << newTemp->bdate->day;
         if (newTemp->bdate->month != "")
            fout << " " << newTemp->bdate->month;
         if (newTemp->bdate->year != "")
            fout << " " << newTemp->bdate->year;
         fout << endl;
         newTemp = newTemp->sNext;
      }
   }
}

   gedcomfile.close();
   if (sort)
   {
      person *newTemp = myTree.sortedStart;
      for (int i = 0; i < myTree.size; i++)
      {
         //Sorts and points to the correct location
         cout << newTemp->givenname;
         if (newTemp->givenname != "" && newTemp->surname != "")
            cout << " ";
         if (newTemp->surname != "")
            cout << newTemp->surname;
         if (newTemp->bdate->month != "" || newTemp->bdate->day != NULL || newTemp->bdate->year != "")
            cout << ", b.";
         if (newTemp->bdate->day != NULL &&
             newTemp->bdate->month != "") //This tidies things up if there's a day but not a month
            cout << " " << newTemp->bdate->day;
         if (newTemp->bdate->month != "")
            cout << " " << newTemp->bdate->month;
         if (newTemp->bdate->year != "")
            cout << " " << newTemp->bdate->year;
         cout << endl;
         newTemp = newTemp->sNext;
      }
   }
   if(generations)
   {
      //Print the tree
      myTree.start->level();
   }
   return 0;
}

