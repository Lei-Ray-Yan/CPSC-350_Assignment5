/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 5

- a general file processor class for conveniency with iterating the files. Read from, stores or write to files. 

*/

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


class FileProcessor{
public:
  string filePath;
  vector<string> fileContent;
  int lineCount = 0;
  bool fileExists;

  FileProcessor();
  ~FileProcessor();
  FileProcessor(string newFilePath);

  bool readLineToVector();
  bool writeToFile(string content);

  void outputContentToConsole();

};


#endif










