#ifndef MEDIA_CAPTURE_PCM_H_
#define MEDIA_CAPTURE_PCM_H_

/*----------------------------------------------------------------------
 |   include
 +---------------------------------------------------------------------*/

#include "fsmda/communicationmanager/model/mediacapture_object_interfaces.h"
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm class
 +---------------------------------------------------------------------*/
class UpnpMediaCapturePcm : public MediaCapturePcmInterface
{
public:
  // public constructors & destructors
  UpnpMediaCapturePcm ();
  virtual
  ~UpnpMediaCapturePcm ();

  // MediaCapturePcmInterface overloaded methods
  virtual void
  sendContent (char* content, const string& resourceId,
	       unsigned int childIndex);
};

#endif /* MEDIA_CAPTURE_PCM_H_ */
