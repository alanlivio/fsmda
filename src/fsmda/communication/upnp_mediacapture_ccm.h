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
  virtual ~UpnpMediaCaptureCcm();

  // MediaCaptureCcmInterface overloaded methods
  virtual void RequestContent(const string& resource_id,
                              unsigned int device_index);
};

#endif  // FSMDA_COMMUNICATION_UPNP_MEDIACAPTURE_CCM_H_
