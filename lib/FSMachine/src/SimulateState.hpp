#ifndef SIMULATE_STATE_HPP_
#define SIMULATE_STATE_HPP_

#include "State.hpp"

class SimulateState : public State
{
public:
  SimulateState();
  ~SimulateState();

  void entryAction(void) override;
  void exitAction(void) override;
  bool guardAction(void) override;
  void timeAction(void) override;
};

#endif