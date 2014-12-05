#ifndef FSMDA_COMMUNICATION_UPNP_PASSIVE_PCM_H_
#define FSMDA_COMMUNICATION_UPNP_PASSIVE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication/model/passive_object_interfaces.h"
#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   UpnpPassivePcm  class
 +---------------------------------------------------------------------*/
class UpnpPassivePcm : public PassivePcmInterface {
 public:
  // public constructors & destructors
  UpnpPassivePcm();
  virtual
  ~UpnpPassivePcm();

  // PassivePCMInterface overloaded methods
  virtual void
  notifyError(const string& message, const string& objectId);
};

#endif  // FSMDA_COMMUNICATION_UPNP_PASSIVE_PCM_H_
