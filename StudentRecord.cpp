/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 5

- the implementation of FacultyRecord.h

*/

#include<iostream>
#include "StudentRecord.h"

using namespace std;


bool StudentRecord :: operator == (const StudentRecord &b){
  return (id == b.id);
}

bool StudentRecord :: operator != (const StudentRecord &b){
  return (id != b.id);
}

bool StudentRecord :: operator > (const StudentRecord &b){
  return (id > b.id);
}

bool StudentRecord :: operator < (const StudentRecord &b){
  return (id < b.id);
}


ostream& operator << (ostream &a, StudentRecord const &b){
  a << "Student ID: " << b.id << endl;
  a << "Name: " << b.name << endl;
  a << "Level: " << b.level << endl;
  a << "Major: " << b.major << endl;
  a << "GPA: " << b.GPA << endl;
  a << "Advisor: " << b.advisor << endl;
  return a;
}


StudentRecord :: StudentRecord(){
  id = 0;
  name = "name";
  level = "level";
  major = "major";
  GPA = 0.0;
  advisor = 0;
}

StudentRecord :: ~StudentRecord(){
  //do nothing;
}

StudentRecord :: StudentRecord(int i, string n, string l, string m, double gpa, int a){
  id = i;
  name = n;
  level = l;
  major = m;
  GPA = gpa;
  advisor = a;
}


//miscellenious
void StudentRecord :: printAll(){
  cout << "Student ID: " << id << endl;
  cout << "Name: " << name << endl;
  cout << "Level: " << level << endl;
  cout << "Major: " << major << endl;
  cout << "GPA: " << GPA << endl;
  cout << "Advisor: " << advisor << endl;
}


//serialization, deserializaiton

string StudentRecord :: serialize(){
  stringstream ss;
  ss << "*StudentRecord:";
  ss << id << "&";
  ss << name << "&";
  ss << level << "&";
  ss << major << "&";
  ss << GPA << "&";
  ss << advisor << "&";

  return ss.str();
}

bool StudentRecord :: deserialize(string key){
  string identifier = "";

  for(int i=0; i<key.length(); ++i){
    if(key[i] != ':'){
      identifier += key[i];
      continue;
    }

    if(identifier != "*StudentRecord"){
      cout << "Warning! Trying to deserialize StudentRecord by a key with wrong type. " << endl;
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

  if(list.size() != 6){
    cout << "Warning! Incorrect key size for StudentRecord deserialization" << endl;
    cout << "key size: " << list.size() << endl;
    for(int i=0; i<list.size(); ++i){
      cout << list[i];
    }
    cout << endl;
    return false;
  }

  try{
    id = stoi(list[0]);
    name = string(list[1]);
    level = string(list[2]);
    major = string(list[3]);
    GPA = stod(list[4]);
    advisor = stoi(list[5]);
  }
  catch(...){
    return false;
  }

  return true;
}













