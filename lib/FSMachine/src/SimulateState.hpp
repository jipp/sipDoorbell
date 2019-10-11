#ifndef SIMULATE_STATE_HPP_
#define SIMULATE_STATE_HPP_

#include "State.hpp"

class SimulateState : public State
{
public:
  SimulateState();
  ~SimulateState();

  void entryAction(Event) override;
  void exitAction(Event) override;
  bool guardAction(Event) override;
  void timeAction(Event) override;
};

#endif