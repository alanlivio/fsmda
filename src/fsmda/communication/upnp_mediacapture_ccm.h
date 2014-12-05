#ifndef FSMDA_COMMUNICATION_UPNP_MEDIACAPTURE_CCM_H_
#define FSMDA_COMMUNICATION_UPNP_MEDIACAPTURE_CCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication/model/mediacapture_object_interfaces.h"
#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm class
 +---------------------------------------------------------------------*/
class UpnpMediaCaptureCcm : public MediaCaptureCcmInterface {
 public:
  // public constructors & destructors
  UpnpMediaCaptureCcm();
  virtual
  ~UpnpMediaCaptureCcm();

  // MediaCaptureCcmInterface overloaded methods
  virtual void
  requestContent(const string& resourceId, unsigned int deviceIndex);
};

#endif  // FSMDA_COMMUNICATION_UPNP_MEDIACAPTURE_CCM_H_
