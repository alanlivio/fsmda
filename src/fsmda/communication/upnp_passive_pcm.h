#ifndef FSMDA_COMMUNICATION_SERVICES_UPNP_PASSIVE_PCM_H_
#define FSMDA_COMMUNICATION_SERVICES_UPNP_PASSIVE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include "fsmda/model/passive_object_interfaces.h"
#include "fsmda/communication/communication_service_interface.h"

using std::string;

/*----------------------------------------------------------------------
 |   UpnpPassivePcm  class
 +---------------------------------------------------------------------*/
class UpnpPassivePcm : public PassivePcmInterface,
                       public CommunicationServiceInterface {
 public:
  // public constructors & destructors
  UpnpPassivePcm();
  virtual ~UpnpPassivePcm();

  // PassivePCMInterface overloaded methods
  virtual void NotifyError(const string& message, const string& object_id);

  // public CommunicationServiceInterface overload methods
  virtual int StartCommunicationService();
  virtual int StopCommunicationService();
  virtual bool IsCommunicationServiceStarted();
};

#endif  // FSMDA_COMMUNICATION_SERVICES_UPNP_PASSIVE_PCM_H_
