#ifndef FSMDA_COMMUNICATION_SERVICES_UPNP_MEDIACAPTURE_PCM_H_
#define FSMDA_COMMUNICATION_SERVICES_UPNP_MEDIACAPTURE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include "fsmda/model/mediacapture_object_interfaces.h"

using std::string;

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm class
 +---------------------------------------------------------------------*/
class UpnpMediaCapturePcm : public MediaCapturePcmInterface {
 public:
  // public constructors & destructors
  UpnpMediaCapturePcm();
  virtual ~UpnpMediaCapturePcm();

  // MediaCapturePcmInterface overloaded methods
  virtual void SendContent(char* content, const string& resource_id,
                           unsigned int child_index);
};

#endif  // FSMDA_COMMUNICATION_SERVICES_UPNP_MEDIACAPTURE_PCM_H_
