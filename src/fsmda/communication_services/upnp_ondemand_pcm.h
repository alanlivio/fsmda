#ifndef FSMDA_COMMUNICATION_SERVICES_UPNP_ONDEMAND_PCM_H_
#define FSMDA_COMMUNICATION_SERVICES_UPNP_ONDEMAND_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include "fsmda/model/ondemand_object_interfaces.h"

using std::string;

/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm class
 +---------------------------------------------------------------------*/
class UpnpOnDemandPcm : public OnDemandPcmInterface {
 public:
  // public constructors & destructors
  UpnpOnDemandPcm();
  virtual ~UpnpOnDemandPcm();

  // OnDemandPCMInterface overloaded methods
  virtual void NotifyOnDemandContent(const string& action,
                                     const string& location);
};

#endif  // FSMDA_COMMUNICATION_SERVICES_UPNP_ONDEMAND_PCM_H_
