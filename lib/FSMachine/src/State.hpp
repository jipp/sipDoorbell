#ifndef STATE_HPP_
#define STATE_HPP_

#include "Event.hpp"
#include "Protocol.hpp"

class State
{
public:
  virtual void entryAction(Event, Protocol *) = 0;
  virtual void exitAction(Protocol *) = 0;
  virtual bool guardAction(Event, Protocol *) = 0;
  virtual void timeAction(Protocol *) = 0;
};

#endif