/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 5

- this class hold information of the student records, and allows serialization and deserialization of these records.

*/

#ifndef STUDENTRECORD_H
#define STUDENTRECORD_H

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


class StudentRecord{
private:

public:
  int id;
  string name;
  string level; //Freshmen, Sophomore, etc;
  string major;
  double GPA;
  int advisor;

  /*
  * Operater overloading for loose coupling with bst
  */
  bool operator == (const StudentRecord &b);
  bool operator != (const StudentRecord &b);
  bool operator > (const StudentRecord &b);
  bool operator < (const StudentRecord &b);

  StudentRecord();
  ~StudentRecord();
  StudentRecord(int i, string n, string l, string m, double gpa, int a);

  void printAll();

  /*
  * Serialization deserialization
  */
  string serialize();
  bool deserialize(string key);

};

ostream& operator << (ostream &a, StudentRecord const &b);


#endif











