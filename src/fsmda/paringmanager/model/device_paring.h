#ifndef DEVICE_PARING_H_
#define DEVICE_PARING_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   DeviceParingCpmInterface abstract class
 +---------------------------------------------------------------------*/
class DeviceParingPpmInterface
{
public:
  // public constructors & destructors
  virtual
  ~DeviceParingPpmInterface ()
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
 |   DeviceParingCpmInterface abstract class
 +---------------------------------------------------------------------*/
class DeviceParingCpmInterface
{
public:
  // public constructors & destructors
  virtual
  ~DeviceParingCpmInterface ()
  {
  }

  // public pure virtual methods
  virtual void
  classAnnouncement (const string& applicationID, unsigned int classIndex,
		     const string& classDesc, const string& classFunction)=0;
};

#endif /* DEVICE_PARING_H_ */
