/*
- Raymond Raymond
- 2297956
- lyan@chapman.edu
- CPSC-350-01
- Assignment 5

- a general, generic Binary Search Tree class, with some modification for better performance with this project.

*/

#ifndef GENBST_H
#define GENBST_H

#include <iostream>
#include <sstream>
#include <vector>
#include "GenTreeNode.h"

using namespace std;


template <typename GenType>
class GenBST{
private:
  GenTreeNode<GenType> *root;
  unsigned int size;

public:
  GenBST();
  ~GenBST();

  /*
  * The basic core features of BST.
  */
  bool searchNode(GenType k);
  void insertNode(GenType k);
  bool deleteNode(GenType k);

  GenTreeNode<GenType> *getSuccessor(GenTreeNode<GenType> *node);

  bool isEmpty();
  unsigned int getSize();
  GenType getMin();
  GenType getMax();
  void recPrint(GenTreeNode<GenType> *node);
  void printEntireTree();
  /*
  * For conveniece of this project.
  */
  GenType* getKeyWithID(int value);  //return the node with key compares the same to the given dummy key

  /*
  * Serialization, deserialization.
  */
  string serialize();
  void serializeNode(GenTreeNode<GenType> *node, vector<string> *content);
  bool deserialize(string key);

};


//core functions
template <typename GenType>
GenBST<GenType> :: GenBST(){
  root = NULL;
}

template <typename GenType>
GenBST<GenType> :: ~GenBST(){
  // FIXME
}

template <typename GenType>
bool GenBST<GenType> :: searchNode(GenType k){
  if (isEmpty()){
    return false;
  }
  else{
    GenTreeNode<GenType> *curr = root;
    while(curr->key != k){
      if(k < curr->key){
        curr = curr->left;
      }
      else{
      curr = curr->right;
      }

      if(curr == NULL){
        return false;
      }
    }
    return true;
  }
}

template <typename GenType>
void GenBST<GenType> :: insertNode(GenType k){
  GenTreeNode<GenType> *node = new GenTreeNode<GenType>(k);

  if(isEmpty()){
    root = node;
  }
  else{
    GenTreeNode<GenType> *curr = root;
    GenTreeNode<GenType> *parent = root;

    while(true){
      parent = curr;
      if(k < curr->key){
        curr = curr->left;
        if(curr == NULL){
          parent->left = node;
          break;
        }
      }
      else{
        curr = curr->right;
        if(curr == NULL){
          parent->right = node;
          break;
        }
      }
    }
  }

  size ++;
}

template <typename GenType>
bool GenBST<GenType> :: deleteNode(GenType k){
  if(isEmpty()){
    return false;
  }

  GenTreeNode<GenType> *curr = root;
  GenTreeNode<GenType> *parent = root;
  bool isLeftChild = true;

  //locate the target node
  while(curr->key != k){
    parent = curr;
    if(k < curr->key){
      isLeftChild = true;
      curr = curr->left;
    }
    else{
      isLeftChild = false;
      curr = curr->right;
    }

    if(curr == NULL){
      return false;
    }
  }

  //if deleting node has no children
  if(curr->left == NULL && curr->right == NULL){
    if(curr == root){
      root = NULL;
    }
    else if(isLeftChild){
      parent->left = NULL;
    }
    else{
      parent->right = NULL;
    }
  }

  //if has one left child
  else if(curr->right == NULL){
    if(curr == root){
      root = curr->left;
    }
    else if(isLeftChild){
      parent->left = curr->left;
    }
    else{
      parent->right = curr->left;
    }
  }

  //if has one right child
  else if(curr->left == NULL){
    if(curr == root){
      root = curr->right;
    }
    else if(isLeftChild){
      parent->left = curr->right;
    }
    else{
      parent->right = curr->right;
    }
  }

  //has two children
  else{
    GenTreeNode<GenType> *successor = getSuccessor(curr);

    if(curr == root){
      root = successor;
    }
    else if(isLeftChild){
      parent->left = successor;
    }
    else{
      parent->right = successor;
    }

    successor->left = curr->left;
  }

  size --;
  return true;
}


//assisting functions
template <typename GenType>
GenTreeNode<GenType> *GenBST<GenType> :: getSuccessor(GenTreeNode<GenType> *node){
  GenTreeNode<GenType> *sp = node; //successor parent
  GenTreeNode<GenType> *successor = node;
  GenTreeNode<GenType> *curr = node->right;

  //find the left-most node of the right side branch, aka the node with next value (larger)
  while (curr != NULL){
    sp = successor;
    successor = curr;
    curr = curr->left;
  }

  //need to check if successor is descendent of right child
  if (successor != node->right){
    sp->left = successor->right;
    successor->right = node->right;
    node->right = NULL;
  }

  return successor;
}


//miscellenious functions
template <typename GenType>
bool GenBST<GenType> :: isEmpty(){
  return (root == NULL);
}

template <typename GenType>
unsigned int GenBST<GenType> :: getSize(){
  return size;
}

template <typename GenType>
GenType GenBST<GenType> :: getMin(){
  GenTreeNode<GenType> *curr = root;

  if(isEmpty()){
    return NULL;
  }

  while(curr->left != NULL){
    curr = curr->left;
  }

  return curr->key;
}

template <typename GenType>
GenType GenBST<GenType> :: getMax(){
  GenTreeNode<GenType> *curr = root;

  if(isEmpty()){
    return NULL;
  }

  while(curr->right != NULL){
    curr = curr->right;
  }

  return curr->key;
}

template <typename GenType>
void GenBST<GenType> :: recPrint(GenTreeNode<GenType>* node){
  if(node == NULL){
    return;
  }

  recPrint(node->left);
  cout << node->key << endl;
  recPrint(node->right);
}

template <typename GenType>
void GenBST<GenType> :: printEntireTree(){
  recPrint(root);
}

template <typename GenType>
GenType* GenBST<GenType> :: getKeyWithID(int value){
  if (isEmpty()){
    return NULL;
  }
  else{
    GenTreeNode<GenType> *curr = root;
    while(curr->key.id != value){
      if(value < curr->key.id){
        curr = curr->left;
      }
      else{
      curr = curr->right;
      }

      if(curr == NULL){
        return NULL;
      }
    }
    GenType *keyRef = new GenType();
    keyRef = &(curr->key);
    return keyRef;
  }
}


//serialization and deserialization
template <typename GenType>
string GenBST<GenType> :: serialize(){   //type: StudentRecordNode or FacultyRecordNode
  string key = "*GenBST:";
  vector<string> *content = new vector<string>();
  serializeNode(root, content);

  vector<string> &contentRef = *content;
  for(int i=0; i<content->size(); ++i){
    key += contentRef[i];
  }

  delete content;
  return key;
}

template <typename GenType>
void GenBST<GenType> :: serializeNode(GenTreeNode<GenType> *node, vector<string> *content){
  if(node == NULL){
    return;
  }
  serializeNode(node->left, content);
  content->push_back(node->serialize());
  serializeNode(node->right, content);
}

template <typename GenType>
bool GenBST<GenType> :: deserialize(string key){
  string identifier = "";
  for(int i=0; i<key.length(); ++i){
    if(key[i] != ':'){
      identifier += key[i];
      continue;
    }
    if(identifier != "*GenBST"){
      cout << "Warning: Trying to apply a key with wrong type for GenBST deserialization. " << endl;
      return false;
    }
    break;
  }

  string content = "";
  vector<string> list;
  int startPos = key.find(':') + 1;
  if(startPos >= key.length()){
    return true;
  }
  for (int i=startPos; i<key.length(); ++i){
    if(key[i] == '*' && i != startPos){
      list.push_back(content);
      content = "*";
      continue;
    }
    content += key[i];
  }
  //catch up the last element
  list.push_back(content);

  for(int i=0; i<list.size(); ++i){
    GenType newValue;
    newValue.deserialize(list[i]);
    insertNode(newValue);
  }
  return true;
}


#endif







