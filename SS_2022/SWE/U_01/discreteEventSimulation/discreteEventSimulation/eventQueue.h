#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H
#include <vector>
#include <queue>
#include "event.h"
#include "compareFunctor.h"

class EventQueue {
private:
  // Implement paused Functionality
  bool paused = false;
public:
  std::priority_queue<Event*, std::vector<Event*>, CompareFunctor>eq;
  /// <summary>
  /// Create Priority Queue Object with using the provided Compare Function and Event Class
  /// </summary>
  /// <returns></returns>
  EventQueue(){};


  /// <summary>
  /// Add Event according to its time to our Queue using push
  /// </summary>
  /// <returns></returns>
  void addEvent(Event *e);

  void pause();
  bool isPaused();

  void stop();

  /// <summary>
  ///Excecute next chronological Event from queue
  /// </summary>
  /// <returns></returns>
  void step();


   /// <summary>
  ///Run through whole queue in chronological order
  /// </summary>
  /// <returns></returns>
  void run();

  /// <summary>
  ///  Return size of our Priority Queue
  /// </summary>
  /// <returns></returns>
  long getSize();

  //todo print queue
};

#endif // !EVENTQUEUE_H
