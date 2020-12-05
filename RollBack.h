/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 5

- although called the Rollback, this class merely stores information required for rollbacks. 

*/

#ifndef ROLLBACK_H
#define ROLLBACK_H

#include <iostream>
#include <vector>

using namespace std;


class Rollback{
private:

public:
  int operationType; //1=addSR; 2=addFR; 3=deleteSR; 4=deleteFR;
  vector<int> sID;
  int fID;
  string sKey;
  string fKey;

  Rollback();
  ~Rollback();
  Rollback(int op);
};


#endif




