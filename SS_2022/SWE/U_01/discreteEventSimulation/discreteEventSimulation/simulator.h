#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <ctime>
#include <random>
#include "event.h"
#include "eventQueue.h"
using namespace std;

class Simulator {
  int maxBuffer;
  int targetConsum;
  int currentConsum;
  int currentProduced;
  int randomInterval;
  int stepNum;
  int producerWaited;
  int consumerWaited;
  std::queue<int>buffer;
  EventQueue eq;
  int scaleInterval;

public:
  /// <summary>
  /// Create Production Simulation with the given Production Parameters
  /// </summary>
  /// <returns></returns>
  Simulator(int maxBuff, int target, int randInt)
    : maxBuffer(maxBuff), targetConsum(target), randomInterval(randInt) 
  {
    currentConsum = 0;
    currentProduced = 0;
    stepNum = 0;
    scaleInterval = 10;
    producerWaited = 0;
    consumerWaited = 0;
  };

  virtual ~Simulator() {};

  int getBufferSize() {
    return maxBuffer;
  }
  int getTargetConsum() {
    return targetConsum;
  }
  int getCurrentConsum() {
    return currentConsum;
  }

  /// <summary>
  /// Produce Function that increments number of produced Objects, produced item is pushed to the buffer 
  /// and is a random number specified by the randomInterval Component of the Simulation Objekt
  /// </summary>
  /// <returns></returns>
  void produce() {
    if (maxBuffer > buffer.size()) {
      currentProduced++;
      int prodTime = rand() % randomInterval;
      buffer.push(prodTime);
    }
    else {
      //cout << "Buffer full, Producer waiting..." << endl;
      producerWaited++;
    }
  }
  /// <summary>
  /// Consume Function that decrements number of produced Objects by removing element from buffer 
  /// and increases consum by incrementing currentConsum of the Simulation Objekt
  /// </summary>
  /// <returns></returns>
  void consume() {
    if (!buffer.empty()) {
      currentConsum++;
      int consTime = buffer.front();
      buffer.pop();
    }
    else {
      //cout << "Buffer empty, Consumer waiting..." << endl;
      consumerWaited++;
    }
  }
  /// <summary>
  /// Simulation consists of a While Loop that runs as long as the in the 
  /// component targetConsum specified number has not been reached. Prints number of produced and 
  /// consumed items as well as necessary iteration steps and time to the consol.
  /// Time of an event is again computet via random numbers derived from the provided randomInterval component
  /// </summary>
  /// <returns></returns>
  void startSimulation() {
    cout << "---------- Starting Consumer/Producer Simulation ----------" << endl;
    cout << "Simulation Parameters are: " << endl;
    cout << "Buffer Size: " << this->getBufferSize() << endl;
    cout << "Target Consum: " << this->getTargetConsum()<< endl;
    int counter = 0;
    int currentTime = 0;
    
    // Create Random Time for event
    srand((unsigned)time(NULL));
    // Main Simulation loop that runs until consumation target is reached
    //cout << endl;
    //cout << "----- Start Simulation loop -----" << endl;
    while (this->currentConsum < this->targetConsum) {
      int time = rand() % this->randomInterval;
      // Add Time of Event to current Time, necessary to avoid 
      // events that occure previous to the current time (eg time = 50, currentTime = 100, Event would
      // happen in the past -> nonsensical but unavoidable with random numbers)
      if (time < currentTime) {
        time += currentTime;
      }
      // Decide which Event gets fired -> rand between 0/1 had too little variation
      // hence using distribution propertios with larger interval
      float rNr = rand() % scaleInterval +1;
      if (rNr <= 5) {
        // Lambda Function here enables other functions while
        // accessing the state of our simulator at the same time
        Event *e = new Event(time, [&](){this->produce();});
        eq.addEvent(e);
      }
      else {
        Event *e = new Event(time, [&]() {this->consume(); });
        eq.addEvent(e);
      }
      // Execute current Event in Queue, otherwise state of Simulator 
      // does not change -> eq.run() would be feasible if we would stop
      // after a certain number of registered events or after a time threshold
      eq.step();
      // Advance current Time
      currentTime = time;
      counter++;
    }
    cout << endl;
    cout << "----- Simulation Loop ended with Results -----" << endl;
    cout << "Waited Steps Producer: " << producerWaited << " | Consumer: " << consumerWaited << endl;
    if (producerWaited > 0 && consumerWaited > 0) {
      int totalWait = producerWaited + consumerWaited;
      float pT = (float)producerWaited / (float)totalWait;
      float cT = (float)consumerWaited / (float)totalWait;
      float pC = (float)producerWaited / (float)consumerWaited;

      cout << "Total waited Steps: " << totalWait << endl;
      cout << "Ratios:" << endl;
      cout << "P/T = " << pT << " | C/T = " << cT << " | P/C = " << pC << endl;
    }

    cout << "Produced Items: " << currentProduced << " | Consumed Items: " << currentConsum << " | Needed Steps: " << counter << " | Needed Time: " << currentTime << endl;
    cout << endl;
  }
};

#endif // !SIMULATOR_H
