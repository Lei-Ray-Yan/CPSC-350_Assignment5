/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 5

- the implementation of Rollback.h

*/

#include "Rollback.h"

using namespace std;


//constructor destrucot
Rollback :: Rollback(){
  operationType = -1;
  fID = -1;
  sKey = "";
  fKey = "";
}

Rollback :: ~Rollback(){
  //do nothing;
}

Rollback :: Rollback(int op){
  operationType = op;
  fID = -1;
  sKey = "";
  fKey = "";
}







