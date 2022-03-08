#pragma once

class AbstractEvent {
public:
  AbstractEvent(){};
  virtual ~AbstractEvent() = 0;
  virtual void action() = 0;
};