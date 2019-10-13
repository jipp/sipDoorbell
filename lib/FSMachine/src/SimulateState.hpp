#ifndef SIMULATE_STATE_HPP_
#define SIMULATE_STATE_HPP_

#include "State.hpp"

class SimulateState : public State
{
public:
  SimulateState(void);
  ~SimulateState();

  void entryAction(Event, Protocol *) override;
  void exitAction(Protocol *) override;
  bool guardAction(Event, Protocol *) override;
  void timeAction(Protocol *) override;
};

#endif