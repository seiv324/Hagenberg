#include <iostream>
#include "skipSet.h"
#include "simulation_file.h"

using namespace std;

/*
http://www.pennelynn.com/Documents/CUJ/HTML/15.01/MARTINKA/MARTINKA.HTM
https://www.keithschwarz.com/interesting/code/skiplist/Skiplist.hh.html
*/

int main() {
  // used for randomization
  srand((unsigned)time(nullptr));


  //Skip_set<int> s(0, 0.5);

  ////for (int i = 0; i < 1000; i++) {
  ////  cout << s.gen_rand_level(32) << endl;
  ////}

  //cout << s.find(2) << endl;
  //for (int i = 1; i <= 50000; i++) {
  //  //int adder = (rand()/32);
  //  //s.insert(i + adder);
  //  s.insert(i);
  //}
  ////cout << s << endl;
  ////s.erase(2);
  ////cout << s.find(2) << endl;
  ////cout << s.find(6) << endl;
  //cout << s << endl;
 
  //// Testen 
  //// set K insert
  //// Add timer insert find erase
  //// 1000, 10000, 100000, 1 Mio Faktoren 
  //// Debuger umschalten auf release
  // Array an zeichen daraus random einen wert

  //Skip_set<string> s("", 0.5);
  //s.insert("beidl");
  //s.insert("dobler");
  //s.insert("graph");
  //s.insert("schwengel");
  //s.insert("penis");

  //cout << s << endl;
  int counter = 6900;
  while(counter <= 10000){ // ab 6900 nochmal 
    simulate_own_set_int(counter);
    simulate_own_set_string(counter);
    simulate_set_int(counter);
    simulate_set_string(counter);
    counter += 100;
  };

  counter = 10000;
  while (counter <= 100000) { // 100 000
    simulate_own_set_int(counter);
    simulate_own_set_string(counter);
    simulate_set_int(counter);
    simulate_set_string(counter);
    counter += 1000;
  };

  return 0;
}