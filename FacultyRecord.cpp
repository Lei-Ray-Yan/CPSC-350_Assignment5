/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 5

- the implementation of FacultyRecord.h

*/

#include<iostream>
#include "FacultyRecord.h"

using namespace std;


bool FacultyRecord :: operator == (const FacultyRecord &b){
  return (id == b.id);
}

bool FacultyRecord :: operator != (const FacultyRecord &b){
  return (id != b.id);
}

bool FacultyRecord :: operator > (const FacultyRecord &b){
  return (id > b.id);
}

bool FacultyRecord :: operator < (const FacultyRecord &b){
  return (id < b.id);
}

ostream& operator << (ostream &a, FacultyRecord const &b){
  a << "Faculty ID: " << b.id << endl;
  a << "Name: " << b.name << endl;
  a << "Level: " << b.level << endl;
  a << "Department: " << b.department << endl;
  for(int i=0; i<b.adviseesID.size(); ++i){
    a << "Advisee #" << i+1 << ": " << b.adviseesID[i] << endl;
  }

  return a;
}


FacultyRecord :: FacultyRecord(){
  id = 0;
  name = "name";
  level = "level";
  department = "department";
}

FacultyRecord :: ~FacultyRecord(){
  //do nothing;
}

FacultyRecord :: FacultyRecord(int i, string n, string l, string d, vector<int> ai){
  id = i;
  name = n;
  level = l;
  department = d;
  adviseesID = ai;
}


//miscellenious
void FacultyRecord :: printAll(){
  cout << "Faculty ID: " << id << endl;
  cout << "Name: " << name << endl;
  cout << "Level: " << level << endl;
  cout << "Department: " << department << endl;
  for(int i=0; i<adviseesID.size(); ++i){
    cout << "Advisee #" << i+1 << ": " << adviseesID[i] << endl;
  }
}


//serialization, deserializaiton

string FacultyRecord :: serialize(){
  stringstream ss;
  ss << "*FacultyRecord:";
  ss << id << "&";
  ss << name << "&";
  ss << level << "&";
  ss << department << "&";

  for(int i=0; i<adviseesID.size(); ++i){
    ss << adviseesID[i] << "&";
  }

  return ss.str();
}

bool FacultyRecord :: deserialize(string key){
  string identifier = "";

  for(int i=0; i<key.length(); ++i){
    if(key[i] != ':'){
      identifier += key[i];
      continue;
    }

    if(identifier != "*FacultyRecord"){
      cout << "Warning! Trying to deserialize FacultyRecord by a key with wrong type. " << endl;
      return false;
    }
  }

  string content = "";
  vector<string> list;
  int startPos = key.find(':') + 1;
  for(int i=startPos; i<key.length(); ++i){
    if(key[i] == '&'){
      list.push_back(content);
      content = "";
      continue;
    }
    content += key[i];
  }

  try{
    id = stoi(list[0]);
    name = string(list[1]);
    level = string(list[2]);
    department = string(list[3]);
    adviseesID.clear();
    for(int i=4; i<list.size(); ++i){
      adviseesID.push_back(stoi(list[i]));
    }
  }
  catch(...){
    return false;
  }

  return true;
}




