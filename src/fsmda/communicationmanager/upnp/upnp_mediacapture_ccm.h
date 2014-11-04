#ifndef UPNP_MEDIA_CAPTURE_CCM_H_
#define UPNP_MEDIA_CAPTURE_CCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communicationmanager/model/mediacapture_object_interfaces.h"
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   UpnpMediaCaptureCcm class
 +---------------------------------------------------------------------*/
class UpnpMediaCaptureCcm : public MediaCaptureCcmInterface
{
public:
  // public constructors & destructors
  UpnpMediaCaptureCcm ();
  virtual
  ~UpnpMediaCaptureCcm ();

  // MediaCaptureCcmInterface overloaded methods
  virtual void
  requestContent (const string& resourceId, unsigned int deviceIndex);
};

#endif /* UPNP_MEDIA_CAPTURE_CCM_H_ */
