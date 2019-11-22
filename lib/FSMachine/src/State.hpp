#ifndef STATE_HPP
#define STATE_HPP

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