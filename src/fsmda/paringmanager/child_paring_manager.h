#ifndef PARENT_PARING_MANAGER_H_
#define PARENT_PARING_MANAGER_H_

#include "fsmda/communicationmanager/model/active_object_control.h"
#include "fsmda/communicationmanager/model/mediacapture_object_control.h"
#include "fsmda/communicationmanager/model/ondemand_object_control.h"
#include "fsmda/communicationmanager/model/passive_object_control.h"
#include "fsmda/paringmanager/device_class_description.h"
#include "fsmda/paringmanager/model/class_handling.h"
#include "fsmda/paringmanager/model/device_paring.h"
#include <map>
#include <string>

using namespace std;

class ChildParingManager : public DeviceParingPcmInterface
{
public:
  // public constructors & destructors
  ChildParingManager ();
  virtual
  ~ChildParingManager ();

  // Method for factory child communication managers
  ActiveCcmInterface*
  createActiveCcm (unsigned int classIntex);
  MediaCaptureCcmInterface*
  createMediaCaptureCcm (unsigned int classIntex);
  PassiveCcmInterface*
  createPassiveCcm (unsigned int classIntex);

  // ClassHandlingChildParingManagerInterface overloaded methods
  // public pure virtual methods
  virtual void
  classAnnouncement (const string& applicationID, unsigned int classIndex,
		     const string& classDesc, const string& classFunction);
private:
  map<unsigned int, DeviceClassDescription*> map_classDescription_;

};

#endif /* PARENT_PARING_MANAGER_H_ */
