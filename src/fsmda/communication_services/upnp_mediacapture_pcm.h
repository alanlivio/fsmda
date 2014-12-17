#ifndef FSMDA_COMMUNICATION_SERVICES_UPNP_MEDIACAPTURE_PCM_H_
#define FSMDA_COMMUNICATION_SERVICES_UPNP_MEDIACAPTURE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include "fsmda/model/mediacapture_object_interfaces.h"
#include "fsmda/communication_services/communication_service_interface.h"

using std::string;

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm class
 +---------------------------------------------------------------------*/
class UpnpMediaCapturePcm : public MediaCapturePcmInterface,
                            public CommunicationServiceInterface {
 public:
  // public constructors & destructors
  UpnpMediaCapturePcm();
  virtual ~UpnpMediaCapturePcm();

  // public CommunicationServiceInterface overload methods
  virtual int StartCommunicationService();
  virtual int StopCommunicationService();
  virtual bool IsCommunicationServiceStarted();

  // MediaCapturePcmInterface overloaded methods
  virtual void SendContent(char* content, const string& resource_id,
                           unsigned int child_index);
};

#endif  // FSMDA_COMMUNICATION_SERVICES_UPNP_MEDIACAPTURE_PCM_H_
