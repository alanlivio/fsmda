#ifndef FSMDA_COMMUNICATION_SERVICES_UPNP_PASSIVE_CCM_H_
#define FSMDA_COMMUNICATION_SERVICES_UPNP_PASSIVE_CCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include "fsmda/model/passive_object_interfaces.h"

/*----------------------------------------------------------------------
 |   UpnpPassiveCcm  class
 +---------------------------------------------------------------------*/
class UpnpPassiveCcm : public PassiveCcmInterface {
 public:
  // public constructors & destructors
  UpnpPassiveCcm();
  virtual ~UpnpPassiveCcm();

  // PassiveCCMInterface overloaded methods
  virtual void Prepare(const string& position);
  virtual void SendContent(char* content);
};

#endif  // FSMDA_COMMUNICATION_SERVICES_UPNP_PASSIVE_CCM_H_
