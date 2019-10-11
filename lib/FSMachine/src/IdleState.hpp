#ifndef IDLE_STATE_HPP_
#define IDLE_STATE_HPP_

#include "State.hpp"

class IdleState : public State
{
public:
  IdleState();
  ~IdleState();

  void entryAction(Event) override;
  void exitAction(Event) override;
  bool guardAction(Event) override;
  void timeAction(Event) override;
};

#endif