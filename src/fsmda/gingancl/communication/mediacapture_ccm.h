#ifndef FSMDA_GINGANCL_COMMUNICATION_MEDIA_CAPTURE_CCM_H_
#define FSMDA_GINGANCL_COMMUNICATION_MEDIA_CAPTURE_CCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/model/communication/mediacapture_object_control.h>
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   MediaCaptureCCM class
 +---------------------------------------------------------------------*/
class MediaCaptureCCM : public MediaCaptureCCMInterface
{
public:
  // public constructors & destructors
  MediaCaptureCCM ();
  virtual
  ~MediaCaptureCCM ();

  // MediaCaptureCCMInterface overloaded methods
  virtual void
  requestContent (const string& resourceId, unsigned int deviceIndex);
};

#endif /* FSMDA_GINGANCL_COMMUNICATION_MEDIA_CAPTURE_CCM_H_ */
