/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 5

- the main file of this program. Handles the general flow of the process.

*/

/*
* Just in case this assignment is late, I would like to use 1 of the 3 late day allowance please :)
*/

#include <iostream>
#include "GenBST.h"
#include "Database.h"
#include "StudentRecord.h"
#include "FacultyRecord.h"

using namespace std;


int main(int argc, char **argv){

  //open up the database and read the stored information if have any.
  Database *db = new Database();
  db->initializeDatabase();

  //read user input and excute
  db->userInterface();



  return 0;
}







