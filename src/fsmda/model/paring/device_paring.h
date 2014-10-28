#ifndef FSMDA_DEVICE_PARING_H_
#define FSMDA_DEVICE_PARING_H_

#include <string>

using namespace std;

class DeviceParingPPMInterface
{
public:
  virtual
  ~DeviceParingPPMInterface ()
  {
  }

  virtual void
  addDeviceToClass (string applicationId, string deviceAddr,
		    unsigned int classIndex, string deviceDesc)=0;
  virtual void
  getChildIndex (string applicationId, string deviceAddr,
		 unsigned int classIndex)=0;
};

class DeviceParingPCMInterface
{
public:
  virtual
  ~DeviceParingPCMInterface ()
  {
  }

  virtual void
  classAnnouncement (string applicationID, unsigned int classIndex,
		     string classDesc, string classFunction)=0;

};

#endif /* FSMDA_DEVICE_PARING_H_ */
