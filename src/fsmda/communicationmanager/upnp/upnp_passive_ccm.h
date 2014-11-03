#ifndef UPNP_PASSIVE_CCM_H_
#define UPNP_PASSIVE_CCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communicationmanager/model/passive_object_control.h"
#include <string>

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm  class
 +---------------------------------------------------------------------*/
class UpnpPassiveCcm : public PassiveCcmInterface
{
public:
  // public constructors & destructors
  UpnpPassiveCcm ();
  virtual
  ~UpnpPassiveCcm ();

  // PassiveCCMInterface overloaded methods
  virtual void
  prepare (const string& position);
  virtual void
  sendContent (char* content);
};

#endif /* UPNP_PASSIVE_CCM_H_ */
