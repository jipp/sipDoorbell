#ifndef STATE_HPP_
#define STATE_HPP_

class State
{
public:
  virtual void entryAction(void) = 0;
  virtual void exitAction(void) = 0;
  virtual bool guardAction(void) = 0;
  virtual void timeAction(void) = 0;
};

#endif