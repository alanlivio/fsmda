#ifndef FSMDA_GINGANCL_PARENTPARINGMANAGER_H_
#define FSMDA_GINGANCL_PARENTPARINGMANAGER_H_

#include "fsmda/model/paring/class_handling.h"
#include "fsmda/model/paring/device_paring.h"

class ParentParingManager : public ClassHandlingPPMInterface,
    public DeviceParingPPMInterface
{
public:
  ParentParingManager ();

  virtual
  ~ParentParingManager ();

  //////////////////// ClassHandlingPPMInterface functions ////////////////////
  virtual void
  addClass (string applicationId, unsigned int classIndex);

  virtual void
  removeClass (string applicationId, unsigned int classIndex);

  virtual void
  addClassDescription (string applicationId, unsigned int classIndex,
		       string classType, unsigned int maxDevices,
		       unsigned int minDevices, string hardwareReq,
		       string softwareReq, string networkReq);

  //////////////////// DeviceParingPPMInterface functions ////////////////////

  virtual void
  addDeviceToClass (string applicationId, string deviceAddr,
		    unsigned int classIndex, string deviceDesc);

  virtual void
  getChildIndex (string applicationId, string deviceAddr,
		 unsigned int classIndex);
};

#endif /* FSMDA_GINGANCL_PARENTPARINGMANAGER_H_ */
