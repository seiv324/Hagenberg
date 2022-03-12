#ifndef SKIPNODE_H
#define SKIPNODE_H

#include <memory>

// Testing 
#include <iostream>

using namespace std;



template<typename K>
class Skip_node {
  using share_ptr = shared_ptr<Skip_node<K>>;
public:
//private:
  K key;
  int level;
  //share_ptr *arr;
  shared_ptr<Skip_node<int>> **arr;
  /*shared_ptr<Skip_node<K>>* arr;*/

//public:
  Skip_node(K inp_key, int inp_lev) {
    key = inp_key;
    level = inp_lev;
    arr = new shared_ptr<Skip_node<int>> * [inp_lev +1];
    memset(arr, 0, sizeof(shared_ptr<Skip_node<int>>*) * (level +1));
    cout << sizeof(arr) / sizeof(arr[0]) << endl;
  }

  ~Skip_node() {
    delete[] arr;
  }

  K get() {
    return K;
  }

};


#endif // !SKIPNODE_H

