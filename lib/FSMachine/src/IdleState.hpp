#ifndef IDLESTATE_HPP
#define IDLESTATE_HPP

#include "State.hpp"

class IdleState : public State
{
public:
  IdleState();
  ~IdleState();

  void entryAction(Event exitEvent, Protocol *protocol) override;
  void exitAction(Protocol *protocol) override;
  bool guardAction(Event checkEvent, Protocol *protocol) override;
  void timeAction(Protocol *protocol) override;
};

#endif