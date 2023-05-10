#include "AdjacencyList.h"

AdjacencyList::AdjacencyList()
{

}
int AdjacencyList::getSizeOfFL()
{
  return friendList.size();
}
void AdjacencyList::addUser(string info)
{
  stringstream ss(info);
  string token;
  vector<int> subV;
  while(getline(ss,token,';'))
  {
    if(isdigit(token[0]))
    {
      subV.push_back(stoi(token));
    }
  }
  friendList.push_back(subV);
}
void AdjacencyList::addNew(int perm, vector<int>permV)
{
  vector<int> newsubV;
  newsubV.push_back(perm);
  for(int i=0;i<permV.size();i++)
  {
    newsubV.push_back(permV[i]);
  }
  friendList.push_back(newsubV);
}
int AdjacencyList::getPerm(int index)
{
  return friendList[index].at(0);
}
bool AdjacencyList::exists(int perm)
{
  for(int i=0;i<friendList.size();i++)
  {
    if(friendList[i].at(0)==perm)
      return true;
  }
  return false;
}
int AdjacencyList::getIndex(int perm)
{
  for(int i=0;i<friendList.size();i++)
  {
    if(friendList[i].at(0)==perm)
      return i;
  }
  return -1;
}
void AdjacencyList::updateList(int userPerm,int friendPerm)
{
  int ind=getIndex(userPerm);
  friendList[ind].push_back(friendPerm);
}
void AdjacencyList::printUserInfo(int index)
{
  if(index==-1)
  {
    return;
  }
  cout<<"User:";
  cout<<friendList[index].at(0);
  cout<<" Friends:";
  for(int i=1;i<friendList[index].size();i++)
  {
    cout<<friendList[index].at(i);
    cout<<" ";
  }
}
vector<int> AdjacencyList::showFriends(int perm)
{
  int ind=getIndex(perm);
  vector<int> friendV;
  for(int i=1;i<friendList[ind].size();i++)
  {
    friendV.push_back(friendList[ind].at(i));
  }
  return friendV;

}
vector<int> AdjacencyList::uniqueFriends(int perm, vector<int> friends)
{
  vector<int> friendsOfUser=showFriends(perm);
  //find(v.begin(),v.end(),5)==v.end() checks that v has no val 5
  vector<int> uniqueFriends;
  for(int i=0;i<friends.size();i++)
  {
    //if friends[i] doesnt exist, add it to new vector to be returned
    if(find(friendsOfUser.begin(),friendsOfUser.end(),friends[i])==friendsOfUser.end() && friends[i]!=perm)
    {
      uniqueFriends.push_back(friends[i]);
    }
  }
  return uniqueFriends;
}
void AdjacencyList::DFS(vector<vector<int>> friendList, int v, vector<bool> &discovered,vector<int>traversedPerms)
{
  discovered[v]= true;
  traversedPerms.push_back(v);
  //do something at each node
  for(int u : friendList[v])
  {
    if(!discovered[u])
      DFS(friendList,u,discovered,traversedPerms);
  }

}
