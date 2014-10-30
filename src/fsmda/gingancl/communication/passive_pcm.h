#ifndef FSMDA_GINGANCL_COMMUNICATION_PASSIVE_PCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_PASSIVE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/model/communication/passive_object_control.h>
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   PassivePCM  class
 +---------------------------------------------------------------------*/
class PassivePCM : public PassivePCMInterface
{
public:
  // public constructors & destructors
  PassivePCM ();
  virtual
  ~PassivePCM ();

  // PassivePCMInterface overloaded methods
  virtual void
  notifyError (const string& message, const string& objectId);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_PASSIVE_PCM_H_ */
