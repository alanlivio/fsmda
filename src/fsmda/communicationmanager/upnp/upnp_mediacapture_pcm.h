#ifndef FSMDA_GINGANCL_COMMUNICATION_MEDIA_CAPTURE_PCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_MEDIA_CAPTURE_PCM_H_

/*----------------------------------------------------------------------
 |   include
 +---------------------------------------------------------------------*/

#include <fsmda/model/communication/mediacapture_object_control.h>
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   MediaCapturePCM class
 +---------------------------------------------------------------------*/
class MediaCapturePCM : public MediaCapturePCMInterface
{
public:
  // public constructors & destructors
  MediaCapturePCM ();
  virtual
  ~MediaCapturePCM ();

  // MediaCaptureCCMInterface overloaded methods
  virtual void
  sendContent (char* content, const string& resourceId,
	       unsigned int childIndex);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_MEDIA_CAPTURE_PCM_H_ */
