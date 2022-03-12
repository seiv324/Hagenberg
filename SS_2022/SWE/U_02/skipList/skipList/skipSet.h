#ifndef SKIPSET_H
#define SKIPSET_H

#include <memory>;
#include "skipNode.h";

// Testing 
#include <iostream>

template<typename T, const int MAXLEVEL = 32>
class Skip_set {
private:
  Skip_node<T> *header;
  int cur_size;
  float prob;

public:
  Skip_set(T key, float inp_prob){ 
    cur_size = 0; 
    prob = inp_prob;
    header = new Skip_node<T>(key, MAXLEVEL);
    int sizI = sizeof(header->arr[0]);
    int siz = sizeof(header->arr);
    cout << siz/sizI << endl;
  };

  ~Skip_set(){};

  int gen_rand(int size) {
    return (float)rand() / size;
  }

  int gen_rand_level(int size) {
    int new_level = 0;
    while (gen_rand(size) < prob) {
      new_level++;
    }
    return min(new_level, MAXLEVEL);
  }

  int get_size() const {
    return cur_size;
  };

  bool find(T value){
    Skip_node *cur = header;
    for (int i = MAXLEVEL -1; i >= 0; i--) {
      while (cur->arr[i] != nullptr && cur->arr[i]->key != value) {
        cur = cur->arr[i];
      }
    }
    cur = cur->arr[0];
    return cur != nullptr && cur->key == value;
  };
  
  void insert(T value){
    Skip_node *cur = header;
    std::shared_ptr<Skip_node> arr[MAXLEVEL];



  };
  
  bool erase(T value);

  friend std::ostream& operator << (std::ostream &os, const Skip_set &s);
};

#endif // !SKIPSET_H

