#ifndef COMPAREFUNCTOR_H
#define COMPAREFUNCTOR_H

#include "event.h"

// Just for my understanding I realized the necessary compare function
// for the priority queue as the bellow functor object (but without private
// components that would enable state saving since this is not necessary)
class CompareFunctor {
public:
    // Compare Point in Time of both Events
    bool operator()(const Event* e1, const Event* e2) const {
      return e1->getPointTime() > e2->getPointTime();
    }
};

#endif // !COMPAREFUNCTOR_H


