#include "BTreeNode.h"
namespace btree{

  bool BTreeNode::isLeaf()
  {
    for(auto i=0;i<size;++i)
    {
      if((bool)children[i])
        return false;
    }
    return true;

  }
  size_t BTreeNode::findPosition(const pair<User,int>& key)
  {
    size_t pos=0;
    for(auto end=size;pos!=end && keys[pos].first.getPerm()< key.first.getPerm();++pos);
    return pos;

  }
  void BTreeNode::placeKey(const pair<User,int>& key, const size_t pos)
  {
    for(auto i=size;i>pos;--i)
    {
      keys[i]=keys[i-1];
      assert(!children[i+1]);
      children[i+1]=move(children[i]);
    }
    keys[pos]=key;
    ++size;
  }
  void BTreeNode::insert(pair<User,int> key)
  {
    if(!isLeaf())
    {
      auto keyPosition=findPosition(key);
      if(!children[keyPosition])
      {
        children[keyPosition]=unique_ptr<BTreeNode>(new BTreeNode(this));
      }
      else if(children[keyPosition]->size==max)
      {
        split(children[keyPosition].get());
        keyPosition=findPosition(key);
      }
      children[keyPosition]->insert(key);
      return;
    }
    placeKey(key,findPosition(key));
  }
  void BTreeNode::add(pair<User,int> key, unique_ptr<BTreeNode>& other)
  {
    assert(size<max);
    assert(other.get()!=nullptr);
    const auto pos=findPosition(key);
    placeKey(key,pos);
    children[pos+1]=move(other);
    children[pos+1]->parent=this;
  }
  void BTreeNode::split(BTreeNode* oldNode)
  {
    assert(oldNode);
    assert(oldNode->parent);
    assert(oldNode->parent->size<max);

    unique_ptr<BTreeNode> newNode(new BTreeNode(oldNode->parent));
    BTreeNode* newNodeRaw=newNode.get();

    const size_t median=max/2;
    const pair<User,int> medianKey=oldNode->keys[median];

    if((bool)oldNode->children[median+1])
    {
      newNode->children[0]=move(oldNode->children[median+1]);
      newNode->children[0]->parent=newNodeRaw;
    }
    for(size_t i=median+1,newi=0,end=max;i!=end;++i,++newi)
    {
      newNode->keys[newi]=oldNode->keys[i];
      if(oldNode->children[i+1])
      {
        newNode->children[newi+1]=move(oldNode->children[i+1]);
        newNode->children[newi+1]->parent=newNode.get();
      }
      ++newNode->size;
      --oldNode->size;
    }
    --oldNode->size; //remove the median
    oldNode->parent->add(medianKey,newNode);

  }
  string BTreeNode::str()
  {
    string s;
    for(size_t i=0,end=size;i!=end;++i)
    {
      if((bool)children[i])
      {
        s+=children[i]->str()+", ";
      }
      s+=keys[i].first.toString();
      s+=", ";
    }
    if((bool)children[size])
      s+=children[size]->str();
    else
      s.erase(s.end() -2,s.end()); //erase the last ,
    return s;
  }
  bool BTreeNode::findUser(int perm)
  {
    int i=0;
    while(i<size && perm > keys[i].first.getPerm())
    {
      i++;
    }
    if(keys[i].first.getPerm()==perm)
    {
      return true;
    }
    if(isLeaf())
    {
      return false;
    }
    return children[i]->findUser(perm);

  }
  pair<string,string> BTreeNode::genres(int perm)
  {
    pair<string,string> genrePair;
    int i=0;
    while(i<size&& perm>keys[i].first.getPerm())
    {
      i++;
    }
    if(keys[i].first.getPerm()==perm){
      genrePair.first=keys[i].first.getGenre1();
      genrePair.second=keys[i].first.getGenre2();
      return genrePair;
    }
    if(isLeaf())
    {
      genrePair.first="not";
      genrePair.second="found";
      return genrePair;
    }
    return children[i]->genres(perm);

  }
  string BTreeNode::findUserDetails(int perm)
  {
    int i=0;

    while(i<size && perm > keys[i].first.getPerm())
    {
      i++;
    }
    if(keys[i].first.getPerm()==perm)
    {
      return keys[i].first.toString();
    }
    if(isLeaf())
    {
      return "User not found.";
    }
    return children[i]->findUserDetails(perm);

  }

}
