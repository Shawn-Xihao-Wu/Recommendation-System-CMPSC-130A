#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
using namespace std;

class User{
public:
  User();
  User(int perm);
  User(string info);
  User(int perm,string name,string genre1,string genre2);
  int getPerm() const;
  string getName();
  string getGenre1();
  string getGenre2();
  void setName(string name);
  void setPerm(int perm);
  void setGenre1(string genre1);
  void setGenre2(string genre2);
  void operator=(const User& user);//overload assignment operator
  string toString();

private:
  int perm;
  string name;
  string genre1;
  string genre2;




};

#endif
