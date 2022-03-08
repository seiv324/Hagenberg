#include "eventQueue.h"
#include <iostream>

using namespace std;

void EventQueue::addEvent(Event* e) {
  // Use implemented push to add Event to queue
  this->eq.push(e);
}

// Pause changes Queue Status -> both directions
void EventQueue::pause(){
  if (paused) {
    paused = false;

  }
  else {
    paused = true;
  } 
}

bool EventQueue::isPaused() {
  return paused;
}

// Stop Event Queue without Removing EQ Object
void EventQueue::stop() {
  while (!this->eq.empty()) {
    this->eq.pop();
  }
}

void EventQueue::step() {
  // Get topmost event
  if (this->eq.empty()) {
    throw exception();
  }
  Event *e = this->eq.top();
  // Call provided Functor/Lambda
  e->callExecutable();
  this->eq.pop();
}

void EventQueue::run() {
  // Change pause state before running -> is only relevant if triggered by event
  if (this->paused) { this->paused = false; }
  // Run as long as Queue is neither paused nor empty
  
  while (!this->paused && !this->eq.empty()) {
    //Event *e = this->eq.top();
    //e->callExecutable();
    //this->eq.pop();

    // CALL step instead!
    step();

  }
}

long EventQueue::getSize() {
  return this->eq.size();
}