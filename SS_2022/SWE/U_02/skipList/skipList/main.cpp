#include <iostream>
#include "skipSet.h"
#include "simulation_file.h"

using namespace std;

int main() {
  // used for randomization
  srand((unsigned)time(nullptr));

  // cout << "----- Test of Set of Integers -----" << endl;
  
  //Skip_set<int> s(0, 0.5);

  ////for (int i = 0; i < 100; i++) {
  ////  cout << s.gen_rand_level(32) << endl;
  ////}
  ////cout << s << endl;
  // 
  ////s.erase(2);
  ////cout << s.find(2) << endl;
  ////cout << s.find(6) << endl;
  //cout << s << endl;

  //cout << s << endl;
  // cout << "----- End Test -----" << endl;

  // Start Runtime Evaluation:
  // Run each Funktion with the provided number of elements
  // at least 25/15/10 times (depending on the number of elements)
  int counter = 8000;
  while(counter <= 10000){ // Pro Einheit 25 Werte
    for (int i = 0; i < 15; i++) {
      simulate_own_set_int(counter);
      simulate_own_set_string(counter);
      simulate_set_int(counter);
      simulate_set_string(counter);
    }
    cout << "Counter " << counter << endl;
    counter += 1000;
  };


  return 0;
}