#ifndef FSMDA_COMMUNICATION_SERVICES_UPNP_ONDEMAND_PCM_H_
#define FSMDA_COMMUNICATION_SERVICES_UPNP_ONDEMAND_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include "fsmda/model/ondemand_object_interfaces.h"
#include "fsmda/communication_services/communication_service_interface.h"

using std::string;

/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm class
 +---------------------------------------------------------------------*/
class UpnpOnDemandPcm : public OnDemandPcmInterface,
                        public CommunicationServiceInterface {
 public:
  // public constructors & destructors
  UpnpOnDemandPcm();
  virtual ~UpnpOnDemandPcm();

  // public CommunicationServiceInterface overload methods
  virtual int StartCommunicationService();
  virtual int StopCommunicationService();
  virtual bool IsCommunicationServiceStarted();

  // OnDemandPCMInterface overloaded methods
  virtual void NotifyOnDemandContent(const string& action,
                                     const string& location);
};

#endif  // FSMDA_COMMUNICATION_SERVICES_UPNP_ONDEMAND_PCM_H_
