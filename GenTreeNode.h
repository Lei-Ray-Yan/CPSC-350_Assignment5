/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 5

- a general, generic Tree Node class for bst. Assiting the GenBST.h. Allows serialization but not deserialization (latter done by key class). 

*/

#ifndef GENTREENODE_H
#define GENTREENODE_H

#include <iostream>

using namespace std;


template <typename GenType>
class GenTreeNode{
private:
  //none
public:
  GenType key;
  GenTreeNode *left;
  GenTreeNode *right;

  GenTreeNode();
  ~GenTreeNode();
  GenTreeNode(GenType k);

  string serialize();
};


template <typename GenType>
GenTreeNode<GenType> :: GenTreeNode(){
  left = NULL;
  right = NULL;
}

template <typename GenType>
GenTreeNode<GenType> :: ~GenTreeNode(){
  delete left;
  delete right;
}

template <typename GenType>
GenTreeNode<GenType> :: GenTreeNode(GenType k){
  key = k;
  left = NULL;
  right = NULL;
}

template <typename GenType>
string GenTreeNode<GenType> :: serialize(){
  return key.serialize();
}


#endif





