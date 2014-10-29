#ifndef FSMDA_GINGANCL_COMMUNICATION_MEDIA_CAPTURE_PCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_MEDIA_CAPTURE_PCM_H_

#include "fsmda/model/communication/mediacapture_object_control.h"

class MediaCapturePCM : public MediaCapturePCMInterface
{
public:
  MediaCapturePCM ();

  virtual
  ~MediaCapturePCM ();

  //////////////////// MediaCapturePCMInterface functions ////////////////////
  virtual void
  sendContent (char* content, const string& resourceId, unsigned int childIndex);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_MEDIA_CAPTURE_PCM_H_ */
