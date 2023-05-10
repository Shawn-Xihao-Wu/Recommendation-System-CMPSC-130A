#include "User.h"
User::User(int perm)
{
  this->perm=perm;
}
User::User(){}
User::User(int perm,string name, string genre1,string genre2)
{
  this->perm=perm;
  this->name=name;
  this->genre1=genre1;
  this->genre2=genre2;

}
User::User(string info)
{
  stringstream ss(info);
  int pos;
  string token;
  vector<string> subV;
  pos=info.find(';');
  string p=info.substr(0,pos);
  int permno=stoi(p);
  while(getline(ss,token,';'))
  {
    if(isalpha(token[0]))
      subV.push_back(token);
  }
  this->perm=permno;
  this->name=subV[0];
  this->genre1=subV[1];
  this->genre2=subV[2];

}
int User::getPerm() const
{
  return perm;
}
string User::getName()
{
  return name;
}
string User::getGenre1()
{
  return genre1;
}
string User::getGenre2()
{
  return genre2;
}
void User::setName(string name)
{
  this->name=name;
}
void User::setPerm(int perm)
{
  this->perm=perm;
}
void User::setGenre1(string genre1)
{
  this->genre1=genre1;
}
void User::setGenre2(string genre2)
{
  this->genre2=genre2;
}
void User::operator= (const User& user)
{
  perm=user.perm;
  name=user.name;
  genre1=user.genre1;
  genre2=user.genre2;
}
string User::toString()
{
  string s;
  s+="Name: ";
  s+=this->getName();
  s+=", Perm: ";
  s+=to_string(this->getPerm());
  s+=", Genres: ";
  s+=this->getGenre1();
  s+=" & ";
  s+=this->getGenre2();
//  s+="\n";

  return s;

}
