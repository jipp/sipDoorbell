#ifndef IDLE_STATE_HPP_
#define IDLE_STATE_HPP_

#include "State.hpp"

class IdleState : public State
{
public:
  IdleState();
  ~IdleState();

  void entryAction(void) override;
  void exitAction(void) override;
  bool guardAction(void) override;
  void timeAction(void) override;
};

#endif