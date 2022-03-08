#include "event.h";
#include "eventQueue.h";
#include "simulator.h";
#include "compareFunctor.h";
#include <iostream>
using namespace std;


int main() {
  // Start general Test Cases
  cout << "---------- Start General Test Cases ----------" << endl;
  cout << "----- Test 1 -----" << endl;
  cout << " Step through Event Queue and retreive size " << endl;
  EventQueue mQ0;
  Event *e01 = new Event(1, [&mQ0]() {cout << "Event 1, remaining Size: " << mQ0.getSize() << " | "; });
  Event* e02 = new Event(2, [&mQ0]() {cout << "Event 2, remaining Size: " << mQ0.getSize() << " | "; });
  Event* e03 = new Event(3, [&mQ0]() {cout << "Event 3, remaining Size: " << mQ0.getSize() << " | " << endl; });

  mQ0.addEvent(e01);
  mQ0.addEvent(e02);
  mQ0.addEvent(e03);

  mQ0.step();
  mQ0.step();
  mQ0.run();
  cout << endl;

  cout << "----- Test 2 -----" << endl;
  cout << " Test Events triggering other Events and differences in timestamps" << endl;
  EventQueue mQ;
  Event* e1 = new Event(3, [](){cout << "| Event 1, ";});
  Event* e2 = new Event(2, [](){cout << "| Event 2, ";});
  Event* e3 = new Event(1, []() {cout << "| Event 3, "; });
  Event* e4 = new Event(5, []() {cout << "| Event 4 "; });
  // Show events triggering other events
  Event* e5 = new Event(0, [&mQ](){
     Event* e6 = new Event(10, [](){cout << "| Event 6 (triggered by event 5) " << endl; });
     mQ.addEvent(e6); cout << "| Event 5 (add event to trigger) ";
    });

  mQ.addEvent(e1);
  mQ.addEvent(e2);
  mQ.addEvent(e3);
  mQ.addEvent(e4);
  mQ.addEvent(e5);

  mQ.run();
  cout << endl;
  
  cout << "----- Test 3 -----" << endl;
  cout << " Test Pause/Resume Operations via Events" << endl;
  EventQueue mQ1;
  Event* e10 = new Event(2, [&mQ1](){mQ1.pause(); cout << "Pause Queue, is paused :"<< mQ1.isPaused() << " | "; });
  Event* e11 = new Event(3, [&mQ1](){cout << "Restart Queue, is paused:" << mQ1.isPaused() <<" | ";});
  Event* e12 = new Event(1, [](){cout <<"Event 1 | ";});
  Event* e13 = new Event(4, []() {cout << "Event 2 | "; });
  Event* e14 = new Event(5, []() {cout << "Event 3 | " << endl; });

  mQ1.addEvent(e10);
  mQ1.addEvent(e11);
  mQ1.addEvent(e12);
  mQ1.addEvent(e13);
  mQ1.addEvent(e14);

  mQ1.run();
  mQ1.run();
  cout << endl;

  cout << "---------- End General Test Cases ----------" << endl;
  cout << endl;

  // Start Simulator for Consumer/Producer Scenario
  Simulator *s = new Simulator(10,10,10);
  s->startSimulation();
  Simulator* s1 = new Simulator(10, 100, 10);
  s1->startSimulation();
  Simulator* s2 = new Simulator(100, 100, 50);
  s2->startSimulation();
  Simulator* s3 = new Simulator(5, 1200, 200);
  s3->startSimulation();
  return 0;

}