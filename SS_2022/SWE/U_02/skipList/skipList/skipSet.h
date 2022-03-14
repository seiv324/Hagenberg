#ifndef SKIPSET_H
#define SKIPSET_H

#include <memory>;

using namespace std;
#include <iostream>

/* Create Template Class where the Maxlevel can be adjusted*/
template<typename T, const int MAXLEVEL = 32>
class Skip_set {
  /* Use nested class to give same Template Type to both classes */
  class Skip_node {
  public:
    /* Template Type for Key which is identical to the value of the node */
    T key;
    /* For Destructor of Skip Set this Level in each node is necessary */
    int level;
    std::shared_ptr<Skip_node>* arr;
    
    /// <summary>
    /// Constructor Skip_node, Key = Value
    /// </summary>
    /// <param name="inp_key"> Value to insert (template type)</param>
    /// <param name="inp_lev"> Level of connections for node </param>
    Skip_node(T inp_key, int inp_lev) {
      key = inp_key;
      level = inp_lev;
      /* Create new array of shared pointer for every node*/
      arr = new std::shared_ptr<Skip_node>[inp_lev] {}; // +1
    }
    ~Skip_node() {
      /* Destructor needs to destroy array of each but not 
      individual pointers -> shared pointer advantage */
      delete[] arr;
    }
  };

  /* Outside of Node use template -> wasn't working if placed higher in code */
  using shared_ptr_temp = shared_ptr<Skip_node>;

private:
  /* Skip Set has current Level */
  int cur_level;
  /* Provided Probability */
  float prob;
  /* Current number of nodes */
  int cur_size;
  /* Header node that points to other nodes in list ->
  idea of using an array here instead of an skip_node was 
  not feasible for the later algorithms */
  shared_ptr_temp header;

public:
  /// <summary>
  /// Constructor Skip_set, key determines Type of Data, constructor value can be nonsensical
  /// stored in Nodes, inp_prob used for random level calculation 
  /// </summary>
  /// <param name="key"> Type of stored data (template) </param>
  /// <param name="inp_prob"> Float for level calculation </param>
  Skip_set(T key, float inp_prob){ 
    cur_level = 0;
    cur_size = 0;
    prob = inp_prob;
    // use make shared since it is safer
    header = make_shared<Skip_node>(key, MAXLEVEL);
  };

  virtual ~Skip_set(){
    shared_ptr_temp current = header;
 
    /* Destructor needs to go through every connection between nodes 
    for each node and individually cap them */
    while (current != nullptr) {
        shared_ptr_temp temp_node = current->arr[0];
        // get level for each individual node
        int temp_lev = current->level;
        for (int i = 0; i < temp_lev; i++) {
          // pointers are set to null
          current->arr[i] = nullptr;
          }
      current = temp_node;
    }

  };

  /// <summary>
  /// Generate Random Number
  /// </summary>
  /// <returns> Random Integer Value </returns>
  int gen_rand() {
    return ((float)rand() / RAND_MAX);
  }

  /// <summary>
  /// Generate Random Level
  /// </summary>
  /// <param> </param>
  /// <returns> Returns Random Level smaller maximum of Skip_set </returns>
  int gen_rand_level() {
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

  /* The following algorithms are close derivatives of the provided 
  algorithmic description in the provided paper, there has not been 
  a major alteration of these except for c++ syntax and shared_ptr usage */

  /// <summary>
  /// Find specified value
  /// </summary>
  /// <param name="value"> value (template) </param>
  /// <returns> TRUE found / FALSE not contained </returns>
  bool find(T value) {
    shared_ptr_temp current = header;
    // Iterate through every level of our header node
    for (int i = cur_level; i >= 0; i--) {
      // Check every "lane" through our list for the provided value
      while (current->arr[i] != nullptr && current->arr[i]->key < value) {
        current = current->arr[i];
      }
    }
    // If either break condition is fullfilled set to lowest possible connection
    current = current->arr[0];
    
    if (current != nullptr && current->key == value) {
      return true;
    }
    else {
      return false;
    }
  }

  /// <summary>
  /// Insert provided Value ordered in our list, its level is randomly calculated 
  /// </summary>
  /// <param name="value"> value (template) </param>
  void insert(T value) {
    shared_ptr_temp current = header;
    // MAXLEVEL +1 necessary else corrupted memory
    shared_ptr_temp update[MAXLEVEL+1]{}; 
    
    // Iterate through every level 
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
      // create random level for the new node
      int rand_level = gen_rand_level();

      // search place within skip_list
      if (rand_level > cur_level)
      {
        // search "lane" where to put new node
        for (int i = cur_level +1; i < rand_level; i++) { 
          update[i] = header; 
        }
        cur_level = rand_level;
      }
      
      shared_ptr_temp n = std::make_shared<Skip_node>(value, rand_level);

      // Update Lane of new node and all nodes that point to it
      for (int i = 0; i < rand_level; i++)
      {
          n->arr[i] = update[i]->arr[i];
          update[i]->arr[i] = n;
      }
      // Increase number of nodes in skip_list
      cur_size++;
    }
  };

  /// <summary>
  /// If provided Value is in the skip_list delete it and alter
  /// lanes of skip_list
  /// </summary>
  /// <param name="value">value to delete (template) </param>
  /// <returns> TRUE found and erased / FALSE not found </returns>
  bool erase(T value){
    shared_ptr_temp current = header;
    shared_ptr_temp update[MAXLEVEL]{}; 

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
        // No delete necessary since shared_ptr deletes itself when no other pointer references it
        while (cur_level > 0 && header->arr[cur_level] == nullptr) {
          cur_level--;
        }
        return true;
    }
    else {
      return false;
    }

  };
  /// <summary>
  /// Output Operator, prints each level with its respective nodes 
  /// </summary>
  /// <param name="os"> Output stream </param>
  /// <param name="s"> reference to skip_set </param>
  /// <returns></returns>
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
    os << "}" << endl;

    return os;
  };
};

#endif // !SKIPSET_H

