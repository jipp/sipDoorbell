#ifndef STATE_HPP_
#define STATE_HPP_

#include "Event.hpp"
#include "Protocol.hpp"

class State
{
public:
  virtual void entryAction(Event, Protocol *) = 0;
  virtual void exitAction(Event, Protocol *) = 0;
  virtual bool guardAction(Event, Protocol *) = 0;
  virtual void timeAction(Event, Protocol *) = 0;
};

#endif