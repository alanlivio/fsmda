#ifndef FSMDA_DEVICE_PARING_H_
#define FSMDA_DEVICE_PARING_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   DeviceParingPPMInterface abstract class
 +---------------------------------------------------------------------*/
class DeviceParingPPMInterface
{
public:
  // public constructors & destructors
  virtual
  ~DeviceParingPPMInterface ()
  {
  }

  // public pure virtual methods
  virtual void
  addDeviceToClass (const string& applicationId, const string& deviceAddr,
		    unsigned int classIndex, const string& deviceDesc)=0;
  virtual void
  getChildIndex (const string& applicationId, const string& deviceAddr,
		 unsigned int classIndex)=0;
};

/*----------------------------------------------------------------------
 |   DeviceParingPCMInterface abstract class
 +---------------------------------------------------------------------*/
class DeviceParingPCMInterface
{
public:
  // public constructors & destructors
  virtual
  ~DeviceParingPCMInterface ()
  {
  }

  // public pure virtual methods
  virtual void
  classAnnouncement (const string& applicationID, unsigned int classIndex,
		     const string& classDesc, const string& classFunction)=0;
};

#endif /* FSMDA_DEVICE_PARING_H_ */
