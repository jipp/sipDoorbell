#ifndef STATE_HPP_
#define STATE_HPP_

#include "Event.hpp"

class State
{
public:
  virtual void entryAction(Event) = 0;
  virtual void exitAction(Event) = 0;
  virtual bool guardAction(Event) = 0;
  virtual void timeAction(Event) = 0;
};

#endif