#ifndef FSMDA_COMMUNICATION_UPNP_ONDEMAND_PCM_H_
#define FSMDA_COMMUNICATION_UPNP_ONDEMAND_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication/model/ondemand_object_interfaces.h"
#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm class
 +---------------------------------------------------------------------*/
class UpnpOnDemandPcm : public OnDemandPcmInterface {
 public:
  // public constructors & destructors
  UpnpOnDemandPcm();
  virtual
  ~UpnpOnDemandPcm();

  // OnDemandPCMInterface overloaded methods
  virtual void
  notifyOnDemandContent(const string& action, const string& location);
};

#endif  // FSMDA_COMMUNICATION_UPNP_ONDEMAND_PCM_H_
