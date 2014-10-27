#ifndef FSMDA_DEVICEPARING_H_
#define FSMDA_DEVICEPARING_H_

#include <string>

using namespace std;

class DeviceParingPPMInterface {
 public:
  virtual ~DeviceParingPPMInterface()=0;

  virtual void addDeviceToClass(string applicationId, string deviceAddr,
                                unsigned int classIndex, string deviceDesc)=0;
  virtual void getChildIndex(string applicationId, string deviceAddr,
                             unsigned int classIndex)=0;
};

class DeviceParingHPEInterface {
 public:
  virtual ~DeviceParingHPEInterface()=0;

  // Functions used by a Parent PM
  virtual void classAnnouncement(string applicationID, unsigned int classIndex,
                                 string classDesc, string classFunction)=0;
};

#endif /* FSMDA_DEVICEPARING_H_ */
