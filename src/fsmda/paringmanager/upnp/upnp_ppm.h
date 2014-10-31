#ifndef FSMDA_GINGANCL_PARENTPARINGMANAGER_H_
#define FSMDA_GINGANCL_PARENTPARINGMANAGER_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/model/paring/class_handling.h>
#include <fsmda/model/paring/device_paring.h>
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   ParentParingManager class
 +---------------------------------------------------------------------*/
class ParentParingManager : public ClassHandlingPPMInterface,
    public DeviceParingPPMInterface
{
public:
  // public constructors & destructors
  ParentParingManager ();
  virtual
  ~ParentParingManager ();

  // ClassHandlingPPMInterface overloaded methods
  virtual void
  addClass (const string& applicationId, unsigned int classIndex);
  virtual void
  removeClass (const string& applicationId, unsigned int classIndex);
  virtual void
  addClassDescription (const string& applicationId, unsigned int classIndex,
		       const string& classType, unsigned int maxDevices,
		       unsigned int minDevices, const string& hardwareReq,
		       const string& softwareReq, const string& networkReq);

  // DeviceParingPPMInterface overloaded methods
  virtual void
  addDeviceToClass (const string& applicationId, const string& deviceAddr,
		    unsigned int classIndex, const string& deviceDesc);
  virtual void
  getChildIndex (const string& applicationId, const string& deviceAddr,
		 unsigned int classIndex);
};

#endif /* FSMDA_GINGANCL_PARENTPARINGMANAGER_H_ */
