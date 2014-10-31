#ifndef FSMDA_GINGANCL_COMMUNICATION_PASSIVE_CCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_PASSIVE_CCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/model/communication/passive_object_control.h>
#include <string>

/*----------------------------------------------------------------------
 |   PassiveCCM  class
 +---------------------------------------------------------------------*/
class PassiveCCM : public PassiveCCMInterface
{
public:
  // public constructors & destructors
  PassiveCCM ();
  virtual
  ~PassiveCCM ();

  // PassiveCCMInterface overloaded methods
  virtual void
  prepare (const string& position);
  virtual void
  sendContent (char* content);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_PASSIVE_CCM_H_ */
