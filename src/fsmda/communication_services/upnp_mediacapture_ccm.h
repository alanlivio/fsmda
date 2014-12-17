#ifndef FSMDA_COMMUNICATION_SERVICES_UPNP_MEDIACAPTURE_CCM_H_
#define FSMDA_COMMUNICATION_SERVICES_UPNP_MEDIACAPTURE_CCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include "fsmda/model/mediacapture_object_interfaces.h"
#include "fsmda/communication_services/communication_service_interface.h"

using std::string;

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm class
 +---------------------------------------------------------------------*/
class UpnpMediaCaptureCcm : public MediaCaptureCcmInterface,
                            public CommunicationServiceInterface {
 public:
  // public constructors & destructors
  UpnpMediaCaptureCcm();
  virtual ~UpnpMediaCaptureCcm();

  // public CommunicationServiceInterface overload methods
  virtual int StartCommunicationService();
  virtual int StopCommunicationService();
  virtual bool IsCommunicationServiceStarted();

  // MediaCaptureCcmInterface overloaded methods
  virtual void RequestContent(const string& resource_id,
                              unsigned int device_index);
};

#endif  // FSMDA_COMMUNICATION_SERVICES_UPNP_MEDIACAPTURE_CCM_H_
