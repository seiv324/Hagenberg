#include <iostream>
#include "skipSet.h"

using namespace std;

/*
http://www.pennelynn.com/Documents/CUJ/HTML/15.01/MARTINKA/MARTINKA.HTM
https://www.keithschwarz.com/interesting/code/skiplist/Skiplist.hh.html
*/

int main() {
  // used for randomization
  srand((unsigned)time(nullptr));

  Skip_set<int> s(0, 0.5);

  //for (int i = 0; i < 1000; i++) {
  //  cout << s.gen_rand_level(32) << endl;
  //}

  cout << s.find(2) << endl;
  for (int i = 1; i <=5; i++) {
    //int adder = (rand()/32);
    //s.insert(i + adder);
    s.insert(i);
  }
  cout << s << endl;
  s.erase(2);
  cout << s.find(2) << endl;
  cout << s.find(6) << endl;
  cout << s << endl;
 
  return 0;
}