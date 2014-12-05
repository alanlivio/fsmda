#ifndef FSMDA_COMMUNICATION_UPNP_MEDIACAPTURE_PCM_H_
#define FSMDA_COMMUNICATION_UPNP_MEDIACAPTURE_PCM_H_

/*----------------------------------------------------------------------
 |   include
 +---------------------------------------------------------------------*/

#include "fsmda/communication/model/mediacapture_object_interfaces.h"
#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm class
 +---------------------------------------------------------------------*/
class UpnpMediaCapturePcm : public MediaCapturePcmInterface {
 public:
  // public constructors & destructors
  UpnpMediaCapturePcm();
  virtual
  ~UpnpMediaCapturePcm();

  // MediaCapturePcmInterface overloaded methods
  virtual void
  sendContent(char* content, const string& resourceId, unsigned int childIndex);
};

#endif  // FSMDA_COMMUNICATION_UPNP_MEDIACAPTURE_PCM_H_
