#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <iostream>
using namespace std;

// Define Generic Function with void as parameter and return type
using func_t = function<void(void)>;

class Event{
private:
  int pointTime;
  // Implement: Events call Events via excecutable
  func_t executable;

public:
  /// <summary>
  /// Event Constructor gets Point in Time (int) and function to be executed
  /// (function<void(void)>
  /// </summary>
  /// <returns></returns>
  Event(int pT, func_t executable_f){
    pointTime = pT;
    executable = executable_f;
  };
  virtual ~Event(){};
 /// <summary>
 /// Return point in Time for the Event
 /// </summary>
 /// <returns></returns>
  int getPointTime() const{
    return this->pointTime;
  }
 /// <summary>
 /// Calls generic function that is member of our current Event
 /// </summary>
 /// <returns></returns>
  void callExecutable(){
    //cout << "In Excecutable" << endl;
    executable();
  }
};


#endif // !EVENT_H