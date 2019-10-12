#ifndef IDLE_STATE_HPP_
#define IDLE_STATE_HPP_

#include "State.hpp"

class IdleState : public State
{
public:
  IdleState(void);
  ~IdleState();

  void entryAction(Event, Protocol *) override;
  void exitAction(Event, Protocol *) override;
  bool guardAction(Event, Protocol *) override;
  void timeAction(Event, Protocol *) override;
};

#endif