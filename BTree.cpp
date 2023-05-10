#include "BTree.h"
#include "BTreeNode.h"
namespace btree{
  void BTree::reroot()
  {
    assert(root);
    auto newRoot=unique_ptr<BTreeNode>(new BTreeNode(nullptr));
    auto oldRootRaw=root.get();
    root->parent=newRoot.get();
    newRoot->children[0]=move(root);
    newRoot->children[0]->parent=newRoot.get();
    root=move(newRoot);
    BTreeNode::split(oldRootRaw);

  }
  void BTree::insert(pair<User,int> key)
  {
    if(root->size==4)
    {
      reroot();
    }
    root->insert(key);
  }
  string BTree::str()
  {
    return "["+root->str()+"]";
  }
  pair<string,string> BTree::genres(int index)
  {
    pair<string,string> genreP;
    genreP=root->genres(index);
    return genreP;
  }
  string BTree::findUser(int perm)
  {
    string s;
    if(root->findUser(perm))
    {
      s+="User exists in the B-tree!";
    }
    else
    {
      s+="User does not exist.";
    }
    return s;
  }
  string BTree::findUserDetails(int perm)
  {
    string s;
    s=root->findUserDetails(perm);
    return s;
  }
  
}
