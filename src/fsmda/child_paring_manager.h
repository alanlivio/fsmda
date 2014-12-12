#ifndef FSMDA_CHILD_PARING_MANAGER_H_
#define FSMDA_CHILD_PARING_MANAGER_H_

#include <map>
#include <string>
#include "fsmda/paring_services/upnp_child_paring.h"
#include "fsmda/model/active_object_interfaces.h"
#include "fsmda/model/mediacapture_object_interfaces.h"
#include "fsmda/model/ondemand_object_interfaces.h"
#include "fsmda/model/passive_object_interfaces.h"
#include "fsmda/model/class_handling_interfaces.h"
#include "fsmda/model/device_paring_interfaces.h"
#include "fsmda/device_class_description.h"

using std::string;
using std::map;

class ChildParingManager : public DeviceParingCpmInterface {
 public:
  // public constructors & destructors
  explicit ChildParingManager(const DeviceDescription& device_description);
  virtual ~ChildParingManager();

  // public methods
  int StartParing();
  int StopParing();
  bool IsParingStarted();

  // public DeviceParingCpmInterface overloaded methods
  // called by ParentParingManager
  virtual void ClassAnnouncement(const string& application_id,
                                 unsigned int class_index,
                                 const string& class_desc,
                                 const string& class_function);

  // Method for factory child communication managers
  ActiveCcmInterface* CreateActiveCcm(unsigned int class_index);
  MediaCaptureCcmInterface* CreateMediaCaptureCcm(unsigned int class_index);
  PassiveCcmInterface* CreatePassiveCcm(unsigned int class_index);
  OnDemandCcmInterface* CreateOndemandCcm(unsigned int class_index);

 private:
  map<unsigned int, DeviceClassDescription*> device_class_description_map_;
  DeviceDescription* device_description_;
  UpnpChildParing* upnp_child_paring_;
};

#endif  // FSMDA_CHILD_PARING_MANAGER_H_
