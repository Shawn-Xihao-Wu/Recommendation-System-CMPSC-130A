#ifndef BTREENODE_H
#define BTREENODE_H
#include <iostream>
#include <utility>
#include <string>
#include <cassert>
#include <memory>
#include <cmath>
#include <vector>
#include <limits>
#include "User.h"
using namespace std;
namespace btree{
  const size_t min=2;
  const size_t max=4;
  class BTree;
  class BTreeNode{
  public:
    //static const int min=2;
    //static const int max=4;
    BTreeNode(BTreeNode* parent):size(0),parent(parent){}
    void insert(pair<User,int> key); //insert a new key w/ subtree rooted w/ this node, when notFull
    //void splitChild(int i, BTreeNode *y); //splits the child y of this node. i is the index
    //of y in the Child array C[i]. the child Y must be full when this is called
    //void checkInvariants();
    bool findUser(int perm);
    string findUserDetails(int perm);
    string str();
    pair<string,string> genres(int index);
    //BTreeNode *search(int k);//searched for key rooted w this node. null if k not present
  private:
    static void split(BTreeNode* oldNode);
    void add(pair<User,int> key, unique_ptr<BTreeNode> & other);
    size_t findPosition(const pair<User,int>& key);
    void placeKey(const pair<User,int>& key, const size_t pos);
    BTreeNode * parent;
    size_t size;
    pair<User,int> keys[max];
    unique_ptr<BTreeNode> children[max+1];
    bool isLeaf(); //true when node is a leaf
    friend class BTree; //this class can access private variables
    //int *keys; //array of keys
    //int t; this was the min degree

    //m-1 keys at all non-leaf nodes
    //the root has between 2 and M children
    //all middle nodes have between 2-4 children
    //static int min=2; //all leaves at same depth, with between 1-2 data items
    //BTreeNode **C; //array of child pointers
    //int currentKeys; //current number of keys

  };

}

#endif
