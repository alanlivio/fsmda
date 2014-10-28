#ifndef FSMDA_GINGANCL_COMMUNICATION_MEDIA_CAPTURE_CCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_MEDIA_CAPTURE_CCM_H_

#include "fsmda/model/communication/mediacapture_object_control.h"

class MediaCaptureCCM : public MediaCaptureCCMInterface
{
public:
  MediaCaptureCCM ();

  virtual
  ~MediaCaptureCCM ();

  //////////////////// MediaCaptureCCMInterface functions ////////////////////
  virtual void
  requestContent (string resourceId, unsigned int deviceIndex);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_MEDIA_CAPTURE_CCM_H_ */
