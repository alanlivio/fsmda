#ifndef FSMDA_COMMUNICATION_MODEL_MEDIACAPTURE_OBJECT_INTERFACES_H_
#define FSMDA_COMMUNICATION_MODEL_MEDIACAPTURE_OBJECT_INTERFACES_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   MediaCapturePcmInterface abstract class
 +---------------------------------------------------------------------*/
class MediaCapturePcmInterface {
 public:
  // public constructors & destructors
  virtual ~MediaCapturePcmInterface() {}

  // public pure virtual methods
  virtual void SendContent(char* content, const string& resource_id,
                           unsigned int child_index) = 0;
};

/*----------------------------------------------------------------------
 |   MediaCaptureCcmInterface abstract class
 +---------------------------------------------------------------------*/
class MediaCaptureCcmInterface {
 public:
  // public constructors & destructors
  virtual ~MediaCaptureCcmInterface() {}

  // public pure virtual methods
  virtual void RequestContent(const string& resource_id,
                              unsigned int device_index) = 0;
};
#endif  // FSMDA_COMMUNICATION_MODEL_MEDIACAPTURE_OBJECT_INTERFACES_H_
