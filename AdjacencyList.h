#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H
#include "BTreeNode.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

class AdjacencyList{
public:
  AdjacencyList();
  void addUser(string info);
  void addNew(int perm,vector<int> perms);
  bool exists(int perm);
  int getIndex(int perm); 
  //returns the index in the friendlist
  //of where this user's information is
  int getSizeOfFL();
  vector<int> showFriends(int perm);
  int getPerm(int index);
  void printUserInfo(int index);
  vector<vector<int>> returnList(){return friendList;}
  vector<int> uniqueFriends(int perm, vector<int> friends);
  void updateList(int userPerm,int friendPerm);
  void DFS(vector<vector<int>> friendList,int v,vector<bool> &discovered, vector<int>traversedPerms);


private:
  int index;
  vector<vector<int>> friendList;


};

#endif
