#include <iostream>
#include <cassert>
#include <limits>
using namespace std;

#ifndef SET_H
#define SET_H

template<class X>class set{
private:
  int SET_SIZE;
  struct node{
    X val;
    node *left,*right;
  };

  node *node_insert(node *p,X x){
    if(p == NULL){
      node *q = new node;
      q->val = x;
      q->left = q->right = NULL;
      return q;
    }else{
      if(x == p->val)return p;
      if(x < p->val)p->left = node_insert(p->left,x);
      else p->right = node_insert(p->right,x);
      return p;
    }
  }

  bool node_find(node *p,X x){
    if(p == NULL)return false;
    else if(x == p->val)return true;
    else if(x < p->val)return node_find(p->left,x);
    else return node_find(p->right,x);
  }

  node *remove(node *p,X x){
    if(p == NULL)return NULL;
    else if(x < p->val)p->left = remove(p->left,x);
    else if(x > p->val)p->right = remove(p->right,x);
    else if(p->left == NULL){
      node *q = p->right;
      delete p;
      SET_SIZE--;
      return q;
    }else if(p->left->right == NULL){
      node *q = p->left;
      q->right = p->left;
      delete p;
      SET_SIZE--;
      return q;
    }else{
      node *q;
      for(q = p->left;q->right->right != NULL;q = q->right);
      node *r = q->right;
      q->right = r->left;
      r->left = p->left;
      r->right = p->right;
      delete p;
      SET_SIZE--;
      return r;
    }
    return p;
  }

  void node_clear(node *p){
    if(!p)return;
    node_clear(p->left);
    node_clear(p->right);
    delete p->left;
    delete p->right;
  }

  void print_root(node *root){
    if(root == NULL)return;
    print_root(root->left);
    print_root(root->right);
    cout << root->val << ",";
  }

public:
  node *root;
  set(){
    root = NULL;
    SET_SIZE = 0;
  }

  bool insert(X num){
    root = node_insert(root,num);
    if(root == NULL)return false;
    SET_SIZE++;
    return true;
  }

  bool add(X num){
    return insert(num);
  }

  int find(X num){
    return node_find(root,num);
  }

  bool erase(X num){
    if(!find(num))return false;
    remove(root,num);
    return true;
  }

  int size(){
    return SET_SIZE;
  }

  bool empty(){
    return SET_SIZE == 0;
  }

  void display(){
    print_root(root);
    cout << "\n";
  }

  void clear(){
    node_clear(root);
    delete root;
    root = nullptr;
    SET_SIZE = 0;
  }
  
  // for command line
  void controll(){
    string str;
    int n;
    while(1){
      str = "";
      cin >> str;
      if(str == "insert" || str == "add"){
        cin >> n;
        insert(n);
      }else if(str == "find"){
        cin >> n;
        if(!find(n)){
          cout << "Not found" << endl;
        }else{
          cout << "Found" << endl;
        }
      }else if(str == "clear"){
        cout << "cleared" << endl;
      }else if(str == "erase" || str == "remove"){
        cin >> n;
        if(erase(n)){
          cout << "OK" << endl;
        }else{
          cout << "False" << endl;
        }
      }else if(str == "size"){
        cout << "Size : " << size() << endl;
      }else if(str == "print"){
        display();
      }else if(str == "end" || str == "exit"){
        break;
      }else{
        cout << "Not found this func" << endl;
      }
    }
  }

  ~set(){
    clear();
    // cout << SET_SIZE << endl;
  }
};

#endif
