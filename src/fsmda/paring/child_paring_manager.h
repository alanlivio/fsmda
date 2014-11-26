#ifndef PARENT_PARING_MANAGER_H_
#define PARENT_PARING_MANAGER_H_

#include "fsmda/communication/model/active_object_interfaces.h"
#include "fsmda/communication/model/mediacapture_object_interfaces.h"
#include "fsmda/communication/model/ondemand_object_interfaces.h"
#include "fsmda/communication/model/passive_object_interfaces.h"
#include "fsmda/paring/device_class_description.h"
#include "fsmda/paring/model/class_handling_interfaces.h"
#include "fsmda/paring/model/device_paring_interfaces.h"
#include <map>
#include <string>

using namespace std;

class ChildParingManager : public DeviceParingCpmInterface {
 public:
  // public constructors & destructors
  ChildParingManager();
  virtual
  ~ChildParingManager();

  // Method for factory child communication managers
  ActiveCcmInterface*
  createActiveCcm(unsigned int classIntex);
  MediaCaptureCcmInterface*
  createMediaCaptureCcm(unsigned int classIntex);
  PassiveCcmInterface*
  createPassiveCcm(unsigned int classIntex);

  // DeviceParingCpmInterface overloaded methods
  virtual void
  classAnnouncement(const string& applicationID, unsigned int classIndex,
                    const string& classDesc, const string& classFunction);
 private:
  map<unsigned int, DeviceClassDescription*> map_classDescription_;

};

#endif /* PARENT_PARING_MANAGER_H_ */
