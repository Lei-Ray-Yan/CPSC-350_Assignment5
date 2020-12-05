/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 5

- this class hold information of the faculty records, and allows serialization and deserialization of these records.

*/

#ifndef FACULTYRECORD_H
#define FACULTYRECORD_H

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


class FacultyRecord{
private:

public:
  int id;
  string name;
  string level; //Lecturer, Assistant Prof, Associate Prof, etc
  string department;
  vector<int> adviseesID;

  /*
  * Operater overloading for loose coupling with bst
  */
  bool operator == (const FacultyRecord &b);
  bool operator != (const FacultyRecord &b);
  bool operator > (const FacultyRecord &b);
  bool operator < (const FacultyRecord &b);

  FacultyRecord();
  ~FacultyRecord();
  FacultyRecord(int i, string n, string l, string d, vector<int> ai);

  void printAll();

  /*
  * Serialization deserialization
  */
  string serialize();
  bool deserialize(string key);

};

ostream& operator << (ostream &a, FacultyRecord const &b);


#endif











