// WHOLE CLASS NOT NECESSARY

#ifndef SKIPNODE_H
#define SKIPNODE_H

#include <memory>

// Testing 
#include <iostream>

using namespace std;



template<typename K>
class Skip_node {
  using shared_ptr_temp = shared_ptr<Skip_node<K>>;
public:
//private:
  K key;
  int level;
  shared_ptr_temp *arr;

//public:
  //Skip_node(int &inp_key, int inp_lev) {
  Skip_node(K inp_key, int inp_lev){
    key = inp_key;
    level = inp_lev;
    arr = new shared_ptr_temp [inp_lev];
  }

  ~Skip_node() {
    delete[] arr;
  }

  K get_key() {
      return key;
  }

};


#endif // !SKIPNODE_H

