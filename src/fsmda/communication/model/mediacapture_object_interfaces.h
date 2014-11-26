#ifndef MEDIA_CAPTURE_OBJECT_CONTROL_H_
#define MEDIA_CAPTURE_OBJECT_CONTROL_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   MediaCapturePcmInterface abstract class
 +---------------------------------------------------------------------*/
class MediaCapturePcmInterface {
 public:
  // public constructors & destructors
  virtual ~MediaCapturePcmInterface() {
  }

  // public pure virtual methods
  virtual void
  sendContent(char* content, const string& resourceId,
              unsigned int childIndex)=0;
};

/*----------------------------------------------------------------------
 |   MediaCaptureCcmInterface abstract class
 +---------------------------------------------------------------------*/
class MediaCaptureCcmInterface {
 public:
  // public constructors & destructors
  virtual ~MediaCaptureCcmInterface() {
  }

  // public pure virtual methods
  virtual void
  requestContent(const string& resourceId, unsigned int deviceIndex)=0;
};
#endif /* MEDIA_CAPTURE_OBJECT_CONTROL_H_ */
