#ifndef SIMULATESTATE_HPP
#define SIMULATESTATE_HPP

#include "State.hpp"

class SimulateState : public State
{
public:
  SimulateState();
  ~SimulateState();

  void entryAction(Event exitEvent, Protocol *protocol) override;
  void exitAction(Protocol *protocol) override;
  bool guardAction(Event checkEvent, Protocol *protocol) override;
  void timeAction(Protocol *protocol) override;
};

#endif