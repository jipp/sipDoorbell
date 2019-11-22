#ifndef REGISTERSTATE_HPP
#define REGISTERSTATE_HPP

#include "State.hpp"

class RegisterState : public State
{
public:
  RegisterState();
  ~RegisterState();

  void entryAction(Event exitEvent, Protocol *protocol) override;
  void exitAction(Protocol *protocol) override;
  bool guardAction(Event checkEvent, Protocol *protocol) override;
  void timeAction(Protocol *protocol) override;

private:
  void generate(Protocol *);
};

#endif