#ifndef FSMDA_COMMUNICATION_SERVICES_UPNP_PASSIVE_PCM_H_
#define FSMDA_COMMUNICATION_SERVICES_UPNP_PASSIVE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include "fsmda/model/passive_object_interfaces.h"

using std::string;

/*----------------------------------------------------------------------
 |   UpnpPassivePcm  class
 +---------------------------------------------------------------------*/
class UpnpPassivePcm : public PassivePcmInterface {
 public:
  // public constructors & destructors
  UpnpPassivePcm();
  virtual ~UpnpPassivePcm();

  // PassivePCMInterface overloaded methods
  virtual void NotifyError(const string& message, const string& object_id);
};

#endif  // FSMDA_COMMUNICATION_SERVICES_UPNP_PASSIVE_PCM_H_
