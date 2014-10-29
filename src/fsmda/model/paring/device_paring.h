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
  addDeviceToClass (const string& applicationId, const string& deviceAddr,
		    unsigned int classIndex, const string& deviceDesc)=0;
  virtual void
  getChildIndex (const string& applicationId, const string& deviceAddr,
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
  classAnnouncement (const string& applicationID, unsigned int classIndex,
		     const string& classDesc, const string& classFunction)=0;

};

#endif /* FSMDA_DEVICE_PARING_H_ */
