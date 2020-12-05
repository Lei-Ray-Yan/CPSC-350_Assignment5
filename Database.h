/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 5

- the Database manages the database and all the related functions.

*/

#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "GenBST.h"
#include "GenStack.h"
#include "Rollback.h"
#include "FileProcessor.h"
#include "StudentRecord.h"
#include "FacultyRecord.h"

using namespace std;


class Database{
private:
public:
  /*
  * The following bst stores all the records, which the stack allows the program to record and execute rollback feature.
  */
  GenBST<StudentRecord> *masterStudent;
  GenBST<FacultyRecord> *masterFaculty;
  GenStack<Rollback> *rollbackStack;

  Database();
  ~Database();

  void initializeDatabase();
  /*
  * This is the main method of this class, and handles and executes the user inputs.
  */
  void userInterface();
  /*
  * Special implementation of all the functions that allows a rollback.
  */
  bool addStudentRecord(string key, int sID, int fID);
  bool addFacultyRecord(string key);
  bool deleteStudentRecord(int sID, int fID);
  bool deleteFacultyRecord(int dID);

  /*
  * All the functions that assists the primary core features.
  */
  int readUserInt();
  string readUserString();
  void vectorRemoveInt(vector<int> &v, int value);
  void inputRealClean();
  /*
  * The functions about rollback features.
  */
  void addRollback(int opType, vector<int> sID, int fID, string sKey, string fKey);
  void executeRollback();

  /*
  * For testing and debugging
  */
  void addStuff(); //for testing and debugging
  void printToConsole(); //for testing and debugging

  /*
  * Serialization and deserialization. 
  */
  void serializeData();
  bool deserializeData();

};


#endif




