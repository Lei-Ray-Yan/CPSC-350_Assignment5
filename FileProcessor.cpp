/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 5

- the implementation of FileProcessor.h

*/

#include "FileProcessor.h"

using namespace std;


FileProcessor :: FileProcessor(){
  filePath = "";
  fileExists = false;
}

FileProcessor :: ~FileProcessor(){
  //do nothing;
}

FileProcessor :: FileProcessor(string newFilePath){
  filePath = newFilePath;

  ifstream checkFile;
  checkFile.open(newFilePath);
  if(checkFile.is_open()){
      fileExists = true;
  }else{
      fileExists = false;
  }
}



bool FileProcessor :: readLineToVector(){
  ifstream inFile;

  inFile.open(filePath);
  if(!inFile.is_open()){
    cout << "Error: file not found by given file path. " << endl;
    return false;
  }

  string currLine;
  while(getline(inFile, currLine)){
    fileContent.push_back(currLine);
  }

  inFile.close();
  return true;
}

bool FileProcessor :: writeToFile(string content){
  ofstream outFile;

  outFile.open(filePath);
  if(!outFile.is_open()){
    cout << "Error: file not found by given file path. " << endl;
    return false;
  }

  outFile << content;

  outFile.close();
  return true;
}

void FileProcessor :: outputContentToConsole(){
  for(int i=0; i<fileContent.size(); ++i){
    cout << fileContent[i] << endl;
  }
}










