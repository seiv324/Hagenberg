#ifndef SKIPSET_H
#define SKIPSET_H

#include <memory>;
// WHOLE CLASS NOT NECESSARY
// #include "skipNode.h";


using namespace std;
// Testing 
#include <iostream>

template<typename T, const int MAXLEVEL = 32>
class Skip_set {
  class Skip_node {
  public:
    T key;
    int level;
    std::shared_ptr<Skip_node>* arr;
    
    Skip_node(T inp_key, int inp_lev) {
      key = inp_key;
      level = inp_lev;
      arr = new std::shared_ptr<Skip_node>[inp_lev] {}; // +1
    }
    ~Skip_node() {
      delete[] arr;
    }
  };

  using shared_ptr_temp = shared_ptr<Skip_node>;

private:
  int cur_level;
  float prob;
  int cur_size;
  //shared_ptr_temp header_arr; // hier Array?
  shared_ptr_temp header;

public:
  Skip_set(T key, float inp_prob){ 
    cur_level = 0;
    cur_size = 0;
    prob = inp_prob;
    header = make_shared<Skip_node>(key, MAXLEVEL);
    //header_arr = new shared_ptr_temp [MAXLEVEL] {nullptr};
  };

  virtual ~Skip_set(){
    shared_ptr_temp current = header;
    int counter = 0;
    while (current != nullptr) {
        shared_ptr_temp temp_node = current->arr[0];
        int temp_lev = current->level;
        for (int i = 0; i < temp_lev; i++) {
          current->arr[i] = nullptr;
          }
        
      current = temp_node;
      cur_size--;
      //counter++;
      //cout << "Size:" << cur_size << " Counter: " << counter << endl;
    }

  };

  int gen_rand() {
    return ((float)rand() / RAND_MAX);
  }

  int gen_rand_level(int size) {
    int level = 1;
    while (((float)rand() / RAND_MAX) < prob && level < MAXLEVEL)
    {
      level++;
    }
    return level;
  }

  int get_size() const {

    return cur_size;
  };

  bool find(T value) {
    shared_ptr_temp current = header;
    for (int i = cur_level; i >= 0; i--) {
      while (current->arr[i] != nullptr && current->arr[i]->key < value) {
        current = current->arr[i];
      }
    }
    current = current->arr[0];
    if (current != nullptr && current->key == value) {
      return true;
    }
    else {
      return false;
    }
  }


  void insert(T value) {
    shared_ptr_temp current = header;
    shared_ptr_temp update[MAXLEVEL+1]{}; // MAXLEVEL
    //memset(update, 0, sizeof(shared_ptr_temp) * (MAXLEVEL));

    for (int i = cur_level; i >= 0; i--)
    {
      while (current->arr[i] != nullptr && current->arr[i]->key < value){
        current = current->arr[i];
      }
     update[i] = current;
    }

    current = current->arr[0];
    if (current == nullptr || current->key != value)
    {
      int rlevel = gen_rand_level(MAXLEVEL);

      if (rlevel > cur_level)
      {
        for (int i = cur_level +1; i < rlevel; i++) { // cur_level +1
          update[i] = header; // keinen Plan
        }
        cur_level = rlevel;
      }
      shared_ptr_temp n = std::make_shared<Skip_node>(value, rlevel);

      for (int i = 0; i < rlevel; i++)
      {
          n->arr[i] = update[i]->arr[i];
          update[i]->arr[i] = n;
      }
      cur_size++;
      //std::cout << "Successfully Inserted key " << value << "\n";
    }
  };

  
  bool erase(T value){
    shared_ptr_temp current = header;
    shared_ptr_temp update[MAXLEVEL]{}; // -1 
    //memset(update, 0, sizeof(shared_ptr_temp) * (MAXLEVEL));
    for (int i = cur_level; i >= 0; i--) {
      while (current->arr[i] != nullptr && current->arr[i]->key < value) {
        current = current->arr[i];
      }
      update[i] = current;
    }
    current = current->arr[0];
    if (current != nullptr && current->key == value) {
      for (int i = 0; i < cur_level; i++) {
        if (update[i]->arr[i] != current) {
          break;
        }
        else {
          update[i]->arr[i] = current->arr[i];
        }
      }
        //delete current;
        while (cur_level > 0 && header->arr[cur_level] == nullptr) {
          cur_level--;
        }
        return true;
    }
    else {
      return false;
    }

  };

  friend std::ostream& operator << (std::ostream &os, const Skip_set &s){
    os << endl;
    os << "Print List: Level (Node Key | Node Level) " << endl;
    os << "{" << endl;

    int j = 0;
    for (int i = 0; i < s.cur_level; i++) {
      j++;
      shared_ptr_temp list = s.header->arr[i];
      os << "Level " << i << ": ";
      while (list != nullptr) {
        os << "( " << list->key << " | " << list->level << " )";
        list = list->arr[i];
      }
      os << endl;
    }

    //for (int i = 1; i <= s.cur_level; i++) {

    //  while (list->arr[0] != nullptr) {
    //    os << "( ";
    //    os << "Node Key: " << list->arr[0]->key;
    //    os << " | Node Level: " << list->arr[0]->level;
    //    os << ") ";
    //    list = list->arr[0];
    //  }
    //  j++;
    //}


    os << "}" << endl;

    return os;
  };
};

#endif // !SKIPSET_H

