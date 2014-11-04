#ifndef PARENT_PARING_MANAGER_H_
#define PARENT_PARING_MANAGER_H_

#include "fsmda/communicationmanager/model/active_object_interfaces.h"
#include "fsmda/communicationmanager/model/mediacapture_object_interfaces.h"
#include "fsmda/communicationmanager/model/ondemand_object_interfaces.h"
#include "fsmda/communicationmanager/model/passive_object_interfaces.h"
#include "fsmda/paringmanager/device_class_description.h"
#include "fsmda/paringmanager/model/class_handling_interfaces.h"
#include "fsmda/paringmanager/model/device_paring_interfaces.h"
#include <map>
#include <string>

using namespace std;

class ParentParingManager : public ClassHandlingPpmInterface, public DeviceParingPpmInterface
{
public:
  // public constructors & destructors
  ParentParingManager ();
  virtual
  ~ParentParingManager ();

  // Method for factory parent communication managers
  ActivePcmInterface*
  createActivePcm (unsigned int classIntex);
  MediaCapturePcmInterface*
  createMediaCapturePcm (unsigned int classIntex);
  OnDemandPcmInterface*
  createOnDemandPcm (unsigned int classIntex);
  PassivePcmInterface*
  createPassivePcm (unsigned int classIntex);

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

private:
  map<unsigned int, DeviceClassDescription* > map_classDescription_;

};

#endif /* PARENT_PARING_MANAGER_H_ */
