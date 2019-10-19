#ifndef REGISTER_STATE_HPP_
#define REGISTER_STATE_HPP_

#include "State.hpp"

class RegisterState : public State
{
public:
  RegisterState(void);
  ~RegisterState();

  void entryAction(Event, Protocol *) override;
  void exitAction(Protocol *) override;
  bool guardAction(Event, Protocol *) override;
  void timeAction(Protocol *) override;

private:
  void generate(Protocol *);
};

#endif