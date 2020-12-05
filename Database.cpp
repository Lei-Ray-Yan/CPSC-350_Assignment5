/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 5

- the implementation of Database.h

*/

#include "Database.h"

using namespace std;


//constructo destructor
Database :: Database(){
  masterStudent = new GenBST<StudentRecord>();
  masterFaculty = new GenBST<FacultyRecord>();
  rollbackStack = new GenStack<Rollback>();
}

Database :: ~Database(){
  delete masterStudent;
  delete masterFaculty;
  delete rollbackStack;
}


//core functions
void Database :: initializeDatabase(){

  FileProcessor *fp1 = new FileProcessor("studentTable.txt");
  FileProcessor *fp2 = new FileProcessor("facultyTable.txt");

  if(fp1->fileExists){
    fp1->readLineToVector();
    masterStudent->deserialize(fp1->fileContent[0]);
  }
  if(fp2->fileExists){
    fp2->readLineToVector();
    masterFaculty->deserialize(fp2->fileContent[0]);
  }

  delete fp1;
  delete fp2;

}

void Database :: userInterface(){
  bool needExit = false;
  while(!needExit){
    cout << "Please Enter Number to select operation: " << endl;
    cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3. Find and display student information given the students id" << endl;
    cout << "4. Find and display faculty information given the faculty id" << endl;
    cout << "5. Given a student’s id, print the name and info of their faculty advisor" << endl;
    cout << "6. Given a faculty id, print ALL the names and info of his/her advisees." << endl;
    cout << "7. Add a new student" << endl;
    cout << "8. Delete a student given the id" << endl;
    cout << "9. Add a new faculty member" << endl;
    cout << "10. Delete a faculty member given the id." << endl;
    cout << "11. Change a student’s advisor given the student id and the new faculty id." << endl;
    cout << "12. Remove an advisee from a faculty member given the ids" << endl;
    cout << "13. Rollback" << endl;
    cout << "14. Exit" << endl;
    cout << "-----Extra Features-----" << endl;
    cout << "15. Add or change advisees to a faculty member. " << endl;
    cout << "16. Reset the entire database.  " << endl;
    cout << "17. Store database as file. " << endl;
    cout << "18. Reload database from file. " << endl;
    cout << endl;

    int userSelection = readUserInt();

    cout << endl;

    switch (userSelection){
      case 1:
        cout << "Printing out all students' information: " << endl;
        cout << endl;
        masterStudent->printEntireTree();
        break;
      case 2:
        cout << "Printing out all faculties' information: " << endl;
        cout << endl;
        masterFaculty->printEntireTree();
        break;
      case 3:
      {
        cout << "Enter the searching student id, integers only: " << endl;
        int searchingID = readUserInt();
        StudentRecord *sr = masterStudent->getKeyWithID(searchingID);
        if(sr == NULL){
          cout << "Coundn't find the requested student. " << endl;
          cout << endl;
        }
        else{
          cout << "Find the student, printing the information: " << endl;
          cout << endl;
          cout << *sr << endl;
        }
        break;
      }
      case 4:
      {
        cout << "Enter the searching faculty id, integers only: " << endl;
        int searchingID = readUserInt();
        FacultyRecord *fr = masterFaculty->getKeyWithID(searchingID);
        if(fr == NULL){
          cout << "Coundn't find the requested faculty. " << endl;
          cout << endl;
        }
        else{
          cout << "Find the faculty, printing the information: " << endl;
          cout << endl;
          cout << *fr << endl;
        }
        break;
      }
      case 5:
      {
        cout << "Enter the student's ID, integers only: " << endl;
        int searchingID = readUserInt();
        StudentRecord *sr = masterStudent->getKeyWithID(searchingID);
        if(sr == NULL){
          cout << "Could not find the advisee due to unrecorded student ID" << endl;
          cout << endl;
          delete sr;
        }
        else{
          cout << "Find the student, now printing the information of the student's advisor: " << endl;
          cout << endl;
          FacultyRecord *fr = masterFaculty->getKeyWithID(sr->advisor);
          if(fr == NULL){
            cout << "Error: couldn't find advisor for this student, contact admin for more info. " << endl;
            cout << endl;
            delete fr;
          }else{
            cout << *fr << endl;
          }
        }
        break;
      }
      case 6:
      {
        cout << "Enter the faculty's ID, integers only: " << endl;
        int searchingID = readUserInt();
        FacultyRecord *fr = masterFaculty->getKeyWithID(searchingID);
        if(fr == NULL){
          cout << "Could not find the students due to unrecorded faculty ID" << endl;
          cout << endl;
          delete fr;
        }
        else{
          cout << "Find the faculty, now printing the information of all advisees: " << endl;
          cout << endl;
          vector<int> aID = fr->adviseesID;
          if(aID.size() <= 0){
            cout << "Couldn't find any advisees under this advisor. " << endl;
            cout << endl;
          }
          else{
            StudentRecord *sr = new StudentRecord();
            for(int i=0; i<aID.size(); ++i){
              sr = masterStudent->getKeyWithID(aID[i]);
              cout << *sr << endl;
            }
          }
        }
        break;
      }
      case 7:
      {
        //record info from user as serialized key;
        string element;
        string key = "*StudentRecord:";
        cout << "Enter the new student's: " << endl;
        cout << "ID, integers only: " << endl;
        int sID = readUserInt();
        if(sID == -1){
          cout << "Student ID cannot be -1 or containing any character that is not integer. Process abandoned. " << endl;
          cout << endl;
          break;
        }
        if(masterStudent->getKeyWithID(sID) != NULL){
          cout << "Student with same ID already recorded in the system, please recheck the info. Process abandoned. " << endl;
          cout << endl;
        }
        element = to_string(sID);
        key = key + element + "&";
        cout << "Name, a string: " << endl;
        element = readUserString();
        key = key + element + "&";
        cout << "Level, a string: (Freshman, Sophomore, Junior or Senior)" << endl;
        element = readUserString();
        key = key + element + "&";
        cout << "Major, a string: " << endl;
        element = readUserString();
        key = key + element + "&";
        cout << "GPA, a double: " << endl;
        element = readUserString();
        key = key + element + "&";
        int userInput;
        bool cancelAdd = false;
        while(true){
          cout << "Adivsor ID, integers only: " << endl;
          userInput = readUserInt();
          if(userInput == -1){
            cout << "A student record must have an associated advisor. Process abandoned. " << endl;
            cancelAdd = true;
            break;
          }
          if(masterFaculty->getKeyWithID(userInput) != NULL){
            element = to_string(userInput);
            key = key + element + "&";
            break;
          }
          else{
            cout << "Warning: cannot add a student record with invalid faculty ID. Please retry or enter any letter to abandon the process. " << endl;
          }
        }
        if(cancelAdd == true){
          break;
        }
        addStudentRecord(key, sID, userInput);
      }
        break;
      case 8:
      {
        cout << "Enter the deleting student's ID, integers only: " << endl;
        int sID = readUserInt();
        StudentRecord *sr = masterStudent->getKeyWithID(sID);
        if(sr == NULL){
          cout << "Could not find deleting student's record, please recheck the ID provided. " << endl;
          delete sr;
          break;
        }
        int fID = sr->advisor;
        deleteStudentRecord(sID, fID);
      }
        break;
      case 9:
      {
        //record info from user as serialized key;
        string element;
        string key = "*FacultyRecord:";
        cout << "Enter the new faculty's: " << endl;
        cout << "ID, integers only: " << endl;
        int fID = readUserInt();
        if(fID == -1){
          cout << "Faculty ID cannot be -1 or contains letter, process abandoned. " << endl;
          cout << endl;
          break;
        }
        if(masterFaculty->getKeyWithID(fID) != NULL){
          cout << "Faculty with same ID already recorded in the system, please recheck the info. Process abandoned. " << endl;
          cout << endl;
        }
        element = to_string(fID);
        key = key + element + "&";
        cout << "Name, a string: " << endl;
        element = readUserString();
        key = key + element + "&";
        cout << "Level, a string: " << endl;
        element = readUserString();
        key = key + element + "&";
        cout << "Department, a string: " << endl;
        element = readUserString();
        key = key + element + "&";
        int userInput;
        addFacultyRecord(key);
      }
        break;
      case 10:
      {
        cout << "Enter the deleting faculty's ID, integers only: " << endl;
        int dID = readUserInt();
        deleteFacultyRecord(dID);
      }
        break;
      case 11:
      {
        cout << "Enter the student's ID, integers only: " << endl;
        int sID = readUserInt();
        cout << "Enter the new faculty ID, integers only: " << endl;
        int fID = readUserInt();
        if(sID == -1 || fID == -1){
          cout << "the IDs must not be -1 or contains anything not digits. Process abandoned. " << endl;
          break;
        }
        StudentRecord *sr = new StudentRecord();
        sr = masterStudent->getKeyWithID(sID);
        FacultyRecord *fr = new FacultyRecord();
        fr = masterFaculty->getKeyWithID(fID);
        if(sr == NULL){
          cout << "Cannot find the given student. Process abandoned. " << endl;
          break;
        }
        if(fr == NULL){
          cout << "Cannot find the given faculty. Process abandoned. " << endl;
          break;
        }
        int ofID = sr->advisor;
        sr->advisor = fID;
        cout << "Successfully changed the student's advisor. " << endl;
        //update for referential integrity: new advisor
        bool studentAlreadyIn = false;
        for(int i=0; i<fr->adviseesID.size(); ++i){
          if(fr->adviseesID[i] == sID){
            studentAlreadyIn = true;
            break;
          }
        }
        if(!studentAlreadyIn){
          fr->adviseesID.push_back(sID);
        }
        //update for referential integrity: old advisor
        FacultyRecord *ofr = new FacultyRecord();
        ofr = masterFaculty->getKeyWithID(ofID);
        if(fr != NULL){
          vector<int> &adIDs = ofr->adviseesID;
          vectorRemoveInt(adIDs, sID);
        }
        cout << "Updated corresponding faculty's information (advisees' ID) for referential integrity. " << endl;
        cout << endl;
      }
        break;
      case 12:
      {
        //record IDs;
        cout << "Enter the faculty's ID, integers only: " << endl;
        int fID = readUserInt();
        cout << "Enter the student's ID, integers only: " << endl;
        int sID = readUserInt();
        cout << "Enter the new faculty's ID for the student's new advisor, integers only: " << endl;
        int nfID = readUserInt();
        //check for input format;
        if(fID == -1 || sID == -1 || nfID == -1){
          cout << "the IDs must not be -1 or contains anything not digits. Process abandoned. " << endl;
          break;
        }
        //check if corresponding records exists;
        FacultyRecord *fr = new FacultyRecord();
        fr = masterFaculty->getKeyWithID(fID);
        StudentRecord *sr = new StudentRecord();
        sr = masterStudent->getKeyWithID(sID);
        FacultyRecord *nfr = new FacultyRecord();
        nfr = masterFaculty->getKeyWithID(nfID);
        if(fr == NULL){
          cout << "Cannot find the given faculty. Process abandoned. " << endl;
          break;
        }
        if(sr == NULL){
          cout << "Cannot find the given student. Process abandoned. " << endl;
          break;
        }
        if(nfr == NULL){
          cout << "Cannot find the given new faculty. Process abandoned. " << endl;
          break;
        }
        //check if relationship between records exists
        bool studentNotIn = true;
        for(int i=0; i<fr->adviseesID.size(); ++i){
          if(fr->adviseesID[i] == sID){
            studentNotIn = false;
            break;
          }
        }
        if(studentNotIn == true){
          cout << "The student is already not one of the faculty's advisee. Process abandoned. " << endl;
          break;
        }
        //perform action: remove advisee
        vector<int> &adIDs = fr->adviseesID;
        vectorRemoveInt(adIDs, sID);
        //update referential integrity
        nfr->adviseesID.push_back(sID);
        sr->advisor = nfID;
        cout << "Updated corresponding information (student's advisor's ID and new faculty's advisees' ID) for referential integrity. " << endl;
        cout << endl;
      }
        break;
      case 13:
      {
        cout << "Are you sure you want to rollback 1 step? (this action is irrevocable)" << endl;
        cout << "Enter YES to confirm, or anything else to exit: " <<endl;
        string userInput = readUserString();
        if(userInput != "YES"){
          cout << "Response is not \"YES\". Process abandoned. " << endl;
          break;
        }
        executeRollback();
      }
        break;
      case 14:
      {
        needExit = true;
        serializeData();
        cout << "Database auto-saved as file. " << endl;
        break;
      }

      //Extra functions
      case 15:  //add advisees to faculty records
      {
        cout << "Enter the faculty's ID, integers only: " << endl;
        int fID = readUserInt();
        if(fID == -1){
          cout << "The ID should not be -1 or contains any non-digit characters. Process abandoned. " << endl;
          cout << endl;
          break;
        }
        if(masterFaculty->getKeyWithID(fID) == NULL){
          cout << "Cannot find faculty with given id. Process abandoned. " << endl;
          cout << endl;
          break;
        }
        int userInput;
        while(true){
          cout << "Advisee's ID: (Enter a letter to complete the process)" << endl;
          userInput = readUserInt();
          if(userInput == -1){
            break;
          }
          if(masterStudent->getKeyWithID(userInput) == NULL){
            cout << "Cannot add advisee with invalid student ID, please retry. " << endl;
            continue;
          }
          //add sID to new FR
          masterFaculty->getKeyWithID(fID)->adviseesID.push_back(userInput);
          //remove sID from old FR
          vector<int> &adIDs = masterFaculty->getKeyWithID(masterStudent->getKeyWithID(userInput)->advisor)->adviseesID;
          vectorRemoveInt(adIDs, userInput);
          //change fID in SR to new fID
          masterStudent->getKeyWithID(userInput)->advisor = fID;
        }
        cout << "Successfully assigned these advisee to appointed faculty. " << endl;
        cout << "Corresponding information (student's advisor) has been updated due to referential integrity. " << endl;
        cout << endl;
      }
        break;
      case 16:  //clear the entire database
      {
        cout << "Are you sure? You might lose the job if perform this action without a permission.   :) " << endl;
        cout << "Enter YES to confirm: " << endl;
        string userInput = readUserString();
        if(userInput != "YES"){
          cout << "Wise choice. Process abandoned. " << endl;
          cout << endl;
          break;
        }
        cout << "Okk.  :(  As you wish. " << endl;
        masterStudent = new GenBST<StudentRecord>();
        masterFaculty = new GenBST<FacultyRecord>();
        rollbackStack = new GenStack<Rollback>();
        cout << "Database reset. " << endl;
        cout << endl;
      }
        break;
      case 17: //serialize database
      {
        serializeData();
        cout << "Database saved as file. " << endl;
        cout << endl;
        break;
      }
      case 18: //deserialize database
      {
        if(deserializeData()){
          cout << "Successfully reload the database from the files. " << endl;
          cout << endl;
        }
        else{
          cout << "File not found or imcomplte. Process abandoned. " << endl;
          cout << endl;
        }
        break;
      }
      default:
        cout << "Fail to record a valid input, please retry... " << endl;
        break;
    }

    cout << "Press Enter to Continue" << endl;
    inputRealClean();
  }
}

bool Database :: addStudentRecord(string key, int sID, int fID){
  //deserialize the key
  StudentRecord *sr = new StudentRecord();
  if(!sr->deserialize(key)){
    cout << "Fail to process the information, please recheck the inputs. " << endl;
    delete sr;
    return false;
  }
  masterStudent->insertNode(*sr);
  cout << "Successfully added a new student record. " << endl;
  //update for referential integrity
  FacultyRecord *fr = new FacultyRecord();
  fr = masterFaculty->getKeyWithID(fID);
  fr->adviseesID.push_back(sID);
  cout << "Corresponding faculty information (advisees ID) updated for referential integrity. " << endl;
  cout << endl;
  //add rollback
  vector<int> vsID;
  vsID.push_back(sr->id);
  addRollback(1, vsID, fr->id, sr->serialize(), fr->serialize());
  return true;
}

bool Database :: addFacultyRecord(string key){
  //deserialize the key
  FacultyRecord *fr = new FacultyRecord();
  if(!fr->deserialize(key)){
    cout << "Fail to process the information, please recheck the inputs. " << endl;
    cout << endl;
    delete fr;
    return false;
  }
  masterFaculty->insertNode(*fr);
  cout << "Successfully added the new Faculty record. " << endl;
  //no need to update for referential integrity, no advisees added
  cout << "Please add advisees manually in #15. " << endl;
  cout << endl;
  //add rollback
  vector<int> vaID = fr->adviseesID;
  addRollback(2, vaID, fr->id, "", fr->serialize());
  return true;
}

bool Database :: deleteStudentRecord(int sID, int fID){
  StudentRecord *sr =  masterStudent->getKeyWithID(sID);
  string sKey = sr->serialize();
  if(!masterStudent->deleteNode(*sr)){
    cout << "Fail to remove the record from the Database for unknown reason, contact admin for detail. " << endl;
    delete sr;
    return false;
  }
  cout << "Successfully deleted the record. " << endl;
  //update for referential integrity
  FacultyRecord *fr = new FacultyRecord();
  fr = masterFaculty->getKeyWithID(fID);
  if(fr == NULL){
    return false;
  }
  vector<int> &adIDs = fr->adviseesID;
  vectorRemoveInt(adIDs, sID);
  cout << "Updated corresponding faculty information (advisees ID) for referential integrity. " << endl;
  cout << endl;
  vector<int> vsID;
  vsID.push_back(sID);
  addRollback(3, vsID, fr->id, sKey, fr->serialize());
  return true;
}

bool Database :: deleteFacultyRecord(int dID){
  FacultyRecord *fr = masterFaculty->getKeyWithID(dID);
  if(fr == NULL){
    cout << "Could not find deleting faculty's record, please recheck the ID provided. " << endl;
    cout << endl;
    return false;
  }
  if(fr->adviseesID.size() > 0){
    cout << "Warning: cannot perform the action due to referential integrity. " << endl;
    cout << "Before the deletion, make sure there is no student ID registered as advisees under this faculty. " << endl;
    cout << endl;
    return false;
  }
  cout << "Find the record, deleting... " << endl;
  if(!masterFaculty->deleteNode(*fr)){
    cout << "Fail to remove the record from the Database for unknown reason, contact admin for detail. " << endl;
    cout << endl;
    return false;
  }
  cout << "Successfully deleted the record. " << endl;
  cout << endl;
  //record rollback
  vector<int> vsID;
  addRollback(4, vsID, fr->id, "", fr->serialize());
}


//assisting functions
int Database :: readUserInt(){
  string holder;
  getline(cin, holder);
  for(int i=0; i<holder.length(); ++i){
    if(!isdigit(holder[i])){
      return -1;
    }
  }
  try{
    return stoi(holder);
  }
  catch(...){
    return -1;
  }

}

string Database :: readUserString(){ //read entire line without \n
  string holder;
  getline(cin, holder);
  string newHolder = "";
  for(int i=0; i<holder.length(); ++i){
    if(holder[i] != '\n' && holder[i] != '\r'){
      newHolder += holder[i];
    }
  }

  return newHolder;
}

void Database :: vectorRemoveInt(vector<int> &v, int value){
  cout << endl;
  for(int i=0; i<v.size(); ++i){
    if(v[i] == value){
      v.erase(v.begin()+i);
      break;
    }
  }
  cout << endl;
}

void Database :: inputRealClean(){
  cin.ignore(1000000, '\n');
  cin.clear();
}

void Database :: addRollback(int opType, vector<int> sID, int fID, string sKey, string fKey){
  Rollback rb(opType);
  rb.sID = sID;
  rb.fID = fID;
  rb.sKey = sKey;
  rb.fKey = fKey;
  rollbackStack->push(rb);
}

void Database :: executeRollback(){
  if(rollbackStack->isEmpty()){
    cout << "No operation recorded yet, nothing to be rolled. " << endl;
    cout << endl;
    return;
  }
  Rollback rb = rollbackStack->pop();
  switch(rb.operationType){
    case 1: //added SR
    {
      int sID = rb.sID[0];
      deleteStudentRecord(sID, rb.fID);
      rollbackStack->pop();
      break;
    }
    case 2: //added FR
    {
      deleteFacultyRecord(rb.fID);
      rollbackStack->pop();
      break;
    }
    case 3: //deleted SR
    {
      int sID = rb.sID[0];
      addStudentRecord(rb.sKey, sID, rb.fID);
      rollbackStack->pop();
      break;
    }
    case 4: //deleted FR
    {
      addFacultyRecord(rb.fKey);
      rollbackStack->pop();
      break;
    }
    default:
      cout << "Error: corruption in rollback feature, contact admin for details. " << endl;
      break;
  }
}


//miscellenious
void Database :: addStuff(){
  StudentRecord *s3 = new StudentRecord(1002293, "heloo1", "Sophomore", "CS", 3.77, 3);
    StudentRecord *s2 = new StudentRecord(1002334, "heloo2", "Junior", "CS", 3.45, 3);
      StudentRecord *s1 = new StudentRecord(1001124, "heloo3", "Freshman", "CS", 3.90, 3);
    masterStudent->insertNode(*s3);
    masterStudent->insertNode(*s1);
    masterStudent->insertNode(*s2);

    vector<int> v1 = {233344, 345633, 334443};
    FacultyRecord *f1 = new FacultyRecord(44553, "ffee1", "Prof", "CS", v1);
    FacultyRecord *f2 = new FacultyRecord(12233, "ffee2", "Prof", "CS", v1);
    FacultyRecord *f3 = new FacultyRecord(58887, "ffee1", "Prof", "CS", v1);
    masterFaculty->insertNode(*f1);
    masterFaculty->insertNode(*f2);
    masterFaculty->insertNode(*f3);
}

void Database :: printToConsole(){
  cout << "masterStudent: " << endl;
  masterStudent->printEntireTree();
  cout << "masterFaculty" << endl;
  masterFaculty->printEntireTree();
}


//serialization, deserialization
void Database :: serializeData(){
  FileProcessor *fp1 = new FileProcessor("studentTable.txt");
  fp1->writeToFile(masterStudent->serialize());
  FileProcessor *fp2 = new FileProcessor("facultyTable.txt");
  fp2->writeToFile(masterFaculty->serialize());
  delete fp1;
  delete fp2;
}

bool Database :: deserializeData(){
  //check files
  FileProcessor *fp1 = new FileProcessor("studentTable.txt");
  if(!fp1->readLineToVector()){
    return false;
  }
  FileProcessor *fp2 = new FileProcessor("facultyTable.txt");
  if(!fp2->readLineToVector()){
    return false;
  }
  //load data
  string studentRecordKey = fp1->fileContent[0];
  masterStudent->deserialize(studentRecordKey);
  string facultyRecordKey = fp2->fileContent[0];
  masterFaculty->deserialize(facultyRecordKey);

  delete fp1;
  delete fp2;
  return true;
}






