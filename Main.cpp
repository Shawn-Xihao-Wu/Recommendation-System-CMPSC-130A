#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "User.h"
#include "AdjacencyList.h"
#include "BTree.h"
#include "BTreeNode.h"

using namespace std;
int main()
{
  ifstream myfile;
  bool flag=true;
  int choice;
  string currentLine;
  vector<string> line;
  AdjacencyList aList=AdjacencyList();
  myfile.open("users_friendship.txt");
  if(!myfile.is_open())
    cout<<"File failed to open."<<endl;
  while(getline(myfile,currentLine))
  {
    line.push_back(currentLine);

  }
  btree::BTree tree;

  while(flag==true)
  {
    cout<<endl;
    cout<<"Welcome to the friend recommendation system."<<endl;
    cout<<"1)Run the program with users_friendship.txt"<<endl;
    cout<<"2)Add a new user in the system."<<endl;
    cout<<"3)Find a user."<<endl;
    cout<<"4)Find the details of a user."<<endl;
    cout<<"5)Recommend Friends."<<endl;
    cout<<"Enter 0 to exit."<<endl;
    cout<<"Which operation do you want to make? (1,2,3,4,5)"<<endl;
    cin>>choice;

    if(choice==0)
    {
      cout<<"Exiting."<<endl;
      flag=false;
    }
    else if(choice==1)
    {
      cout<<endl;
      for(int i=0;i<line.size();i++)
      {
        aList.addUser(line[i]);
        User user(line[i]);
        int index=aList.getIndex(user.getPerm());
        pair<User,int> p(user,index);
        tree.insert(p);
      }
      //cout<<tree.str()<<endl;

    }
    else if(choice==2)
    {
      int permU;
      vector<int>permV;
      string permsRead,tok;
      string nameU,genre1U,genre2U;
      cout<<"Enter the new user\'s: perm number,name, 2 movie genres, and friends\' perm number."<<endl;
      cout<<endl;
      cout<<"Perm Number:"<<endl;
      cin>>permU;
      cout<<"Name:"<<endl;
      cin>>nameU;
      cout<<"Genre Options: Action, Adventure, Comedy, Crime, Drama, Fantasy, Horror, Sci-Fi."<<endl;
      cout<<"Genre 1:"<<endl;
      cin>>genre1U;
      cout<<"Genre 2:"<<endl;
      cin>>genre2U;
      cout<<"Friend perm numbers separated by semicolon"<<endl;
      cin>>permsRead;
      stringstream ss(permsRead);
      while(getline(ss,tok,';'))
      {
        permV.push_back(stoi(tok));
      }

      if(aList.exists(permU))
        cout<<"User already exists."<<endl;
      else
      {
        User u1(permU,nameU,genre1U,genre2U); //create a new user
        aList.addNew(permU,permV);
        for(int i=0;i<permV.size();i++)
        {
          if(aList.exists(permV[i]))
            aList.updateList(permV[i],permU);
        }
        int indNewUserAL=aList.getIndex(permU);
        pair<User,int> newP(u1,indNewUserAL);
        tree.insert(newP);
        //cout<<tree.str()<<endl;


      }
    }
    else if(choice==3)
    {
      int userNum;
      cout<<"Enter the perm number to find if the desired user exists:"<<endl;
      cin>>userNum;
      cout<<endl;
      cout<<tree.findUser(userNum)<<endl;
    }
    else if(choice==4)
    {
      int uNum;
      cout<<"Enter the perm number of the desired user\'s details:"<<endl;
      cin>>uNum;
      cout<<endl;
      cout<<tree.findUserDetails(uNum)<<endl;
      cout<<endl;
    }
    else if(choice==5)
    {
      int pNum;
      vector<int> traversedPerms;
      vector<bool>discovered(aList.getSizeOfFL());
      cout<<"Enter the perm number for the desired user\'s recommended friends:"<<endl;
      cin>>pNum;
      cout<<"Recommended Friends List:"<<endl;
      pair<string,string> userGenres;
      pair<string,string> tempGenres;
      vector<int> friendPerms;
      vector<int> unique;
      userGenres=tree.genres(pNum); //returns genres for user inputted
      for(int i=0;i<aList.getSizeOfFL();i++)
      {
        tempGenres=tree.genres(aList.getPerm(i));
        if(tempGenres.first==userGenres.first || tempGenres.first== userGenres.second || tempGenres.second==userGenres.first || tempGenres.second==userGenres.second)
        {
          friendPerms.push_back(aList.getPerm(i));
        }
      }
      unique=aList.uniqueFriends(pNum,friendPerms);
      vector<string> finalVV;
      for(int i=0;i<unique.size();i++)
      {
        finalVV.push_back(tree.findUserDetails(unique[i]));
      }
      for(int i=0;i<finalVV.size();i++)
      {
        cout<<"<";
        cout<<finalVV[i];
        cout<<">";
        cout<<endl;
      }





    }
    else
    {
      cout<<"Please enter a valid input."<<endl;
    }


  }




  return 0;
}
