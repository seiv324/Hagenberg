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
      arr = new std::shared_ptr<Skip_node>[inp_lev] {};
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

  ~Skip_set(){
    //delete[] header_arr;
  };

  int gen_rand(int size) {
    return (float)rand() / size;
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

  void insert(T value) {
    shared_ptr_temp current = header;
    shared_ptr_temp update[MAXLEVEL];
    memset(update, 0, sizeof(shared_ptr_temp) * (MAXLEVEL));

    for (int i = cur_level; i >= 0; i--)
    {
      while (current->arr[i] != NULL && current->arr[i]->key < value){
        current = current->arr[i];
      }
     update[i] = current;
    }

    current = current->arr[0];
    if (current == NULL || current->key != value)
    {
      int rlevel = gen_rand_level(MAXLEVEL);

      if (rlevel > cur_level)
      {
        for (int i = cur_level +1; i < rlevel; i++) {
          update[i] = header;
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
      std::cout << "Successfully Inserted key " << value << "\n";
    }
  };

  
  bool erase(T value);

  // Display skip list level wise
  //void SkipList::displayList()
  //{
  //  cout << "\n*****Skip List*****" << "\n";
  //  for (int i = 0; i <= level; i++)
  //  {
  //    Node* node = header->forward[i];
  //    cout << "Level " << i << ": ";
  //    while (node != NULL)
  //    {
  //      cout << node->key << " ";
  //      node = node->forward[i];
  //    }
  //    cout << "\n";
  //  }
  //};

  friend std::ostream& operator << (std::ostream &os, const Skip_set &s){

    os << "Print List: Level (Node Key | Node Level) " << endl;
    os << "{" << endl;

    int j = 0;
    for (int i = 0; i <= s.cur_level; i++) {
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

