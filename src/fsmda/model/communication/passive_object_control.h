#ifndef FSMDA_PASSIVE_OBJECT_CONTROL_H_
#define FSMDA_PASSIVE_OBJECT_CONTROL_H_

#include <string>
#include <vector>
using namespace std;

class PassiveCCMInterface
{
public:
  virtual
  ~PassiveCCMInterface ()
  {
  }

  virtual void
  prepare (const string& position)=0;

  virtual void
  sendContent (char* content)=0;
};

class PassivePCMInterface
{
public:
  virtual
  ~PassivePCMInterface ()
  {
  }

  virtual void
  notifyError (const string& message, const string& objectId)=0;
};

#endif /* FSMDA_PASSIVE_OBJECT_CONTROL_H_ */
