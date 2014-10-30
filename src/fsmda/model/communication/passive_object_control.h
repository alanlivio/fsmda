#ifndef FSMDA_PASSIVE_OBJECT_CONTROL_H_
#define FSMDA_PASSIVE_OBJECT_CONTROL_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   PassiveCCMInterface abstract class
 +---------------------------------------------------------------------*/
class PassiveCCMInterface
{
public:
  virtual
  // public constructors & destructors
  ~PassiveCCMInterface ()
  {
  }
  // public pure virtual methods
  virtual void
  prepare (const string& position)=0;
  virtual void
  sendContent (char* content)=0;
};

/*----------------------------------------------------------------------
 |   PassivePCMInterface abstract class
 +---------------------------------------------------------------------*/
class PassivePCMInterface
{
public:
  virtual
  // public constructors & destructors
  ~PassivePCMInterface ()
  {
  }

  // public pure virtual methods
  virtual void
  notifyError (const string& message, const string& objectId)=0;
};

#endif /* FSMDA_PASSIVE_OBJECT_CONTROL_H_ */
