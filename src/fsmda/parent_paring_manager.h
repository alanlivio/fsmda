#ifndef FSMDA_PARENT_PARING_MANAGER_H_
#define FSMDA_PARENT_PARING_MANAGER_H_

#include <map>
#include <set>
#include <string>
#include "fsmda/model/active_object_interfaces.h"
#include "fsmda/model/mediacapture_object_interfaces.h"
#include "fsmda/model/ondemand_object_interfaces.h"
#include "fsmda/model/passive_object_interfaces.h"
#include "fsmda/model/class_handling_interfaces.h"
#include "fsmda/model/device_paring_interfaces.h"
#include "fsmda/device_class_description.h"
#include "fsmda/paring_services/upnp_parent_paring.h"

using std::string;
using std::map;
using std::set;

class ParentParingManager : public ClassHandlingPpmInterface,
                            public DeviceParingPpmInterface {
 public:
  // public constructors & destructors
  ParentParingManager();
  virtual ~ParentParingManager();

  // ClassHandlingPpmInterface overloaded methods
  // called by HypermediaEngine
  virtual void AddClass(const string& application_id, unsigned int class_index);
  virtual void RemoveClass(const string& application_id,
                           unsigned int class_index);
  virtual void AddClassDescription(
      const string& application_id, unsigned int class_index,
      const string& class_type, unsigned int max_devices,
      unsigned int min_devices, const string& hardware_requirements,
      const string& software_requirements, const string& network_requirements);

  // Extra ClassHandlingPpmInterface  methods
  // called by HypermediaEngine
  virtual void AddClassDescription(
      const string& application_id, unsigned int class_index,
      DeviceClassDescription* device_class_description);

  // Methods for factory parent communication managers
  // called by HypermediaEngine
  ActivePcmInterface* CreateActivePcm(const string& application_id,
                                      unsigned int class_index);
  MediaCapturePcmInterface* CreateMediaCapturePcm(const string& application_id,
                                                  unsigned int class_index);
  OnDemandPcmInterface* CreateOnDemandPcm(const string& application_id,
                                          unsigned int class_index);
  PassivePcmInterface* CreatePassivePcm(const string& application_id,
                                        unsigned int class_index);

  // DeviceParingPpmInterface overloaded methods
  // called by remote ChildParingManager
  virtual void AddDeviceToClass(const string& application_id,
                                const string& device_address,
                                unsigned int class_index,
                                const string& device_desc);
  virtual void GetChildIndex(const string& application_id,
                             const string& device_address,
                             unsigned int class_index);

  // Utils methods
  unsigned int GenerateAvaliableIndex(const string& application_id);
  unsigned int GetRegistredClassesSize(const string& application_id);
  int StartParing();
  int StopParing();

 private:
  // private filds
  unsigned int upnp_registred_classes_size;
  map<const string, map<unsigned int, DeviceClassDescription*> >
      device_class_description_map_;
  UpnpParentParing* upnp_parent_paring_;
};

#endif  // FSMDA_PARENT_PARING_MANAGER_H_
