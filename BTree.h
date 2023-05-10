#ifndef BTREE_H
#define BTREE_H
#include "BTreeNode.h"
#include "User.h"
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <limits>
#include <cassert>
using namespace std;
namespace btree{
  class BTree{
  public:

    BTree(): root(unique_ptr<BTreeNode>(new BTreeNode(nullptr))){}
    void insert(pair<User,int> key);
    string findUser(int perm);
    string str();
    string findUserDetails(int perm);
    pair<string,string> genres(int index);
  private:
    void reroot();
    unique_ptr<BTreeNode> root;

  };
}
#endif
