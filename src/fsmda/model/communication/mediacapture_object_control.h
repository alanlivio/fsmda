#ifndef FSMDA_MEDIA_CAPTURE_OBJECT_CONTROL_H_
#define FSMDA_MEDIA_CAPTURE_OBJECT_CONTROL_H_

#include <string>
#include <vector>
using namespace std;

class MediaCapturePCMInterface {
 public:
  virtual ~MediaCapturePCMInterface()=0;
  virtual void sendContent(char* content, string resourceId, unsigned int childIndex)=0;
};

class MediaCaptureCCMInterface {
 public:
  virtual ~MediaCaptureCCMInterface()=0;
  virtual void requestContent(string resourceId, unsigned int deviceIndex)=0;
};
#endif /* FSMDA_MEDIA_CAPTURE_OBJECT_CONTROL_H_ */
