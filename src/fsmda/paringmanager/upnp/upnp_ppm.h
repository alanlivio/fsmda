#ifndef UPNP_PPMH_
#define UPNP_PPMH_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paringmanager/model/class_handling.h"
#include "fsmda/paringmanager/model/device_paring.h"
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   UpnpPpm class
 +---------------------------------------------------------------------*/
class UpnpPpm : public ClassHandlingPpmInterface,
    public DeviceParingPpmInterface
{
public:
  // public constructors & destructors
  UpnpPpm ();
  virtual
  ~UpnpPpm ();

  // ClassHandlingPpmInterface overloaded methods
  virtual void
  addClass (const string& applicationId, unsigned int classIndex);
  virtual void
  removeClass (const string& applicationId, unsigned int classIndex);
  virtual void
  addClassDescription (const string& applicationId, unsigned int classIndex,
		       const string& classType, unsigned int maxDevices,
		       unsigned int minDevices, const string& hardwareReq,
		       const string& softwareReq, const string& networkReq);

  // DeviceParingPpmInterface overloaded methods
  virtual void
  addDeviceToClass (const string& applicationId, const string& deviceAddr,
		    unsigned int classIndex, const string& deviceDesc);
  virtual void
  getChildIndex (const string& applicationId, const string& deviceAddr,
		 unsigned int classIndex);
};

#endif /* UPNP_PPMH_ */
