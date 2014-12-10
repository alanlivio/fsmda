#ifndef FSMDA_PARING_PARENT_PARING_MANAGER_H_
#define FSMDA_PARING_PARENT_PARING_MANAGER_H_

#include "fsmda/communication/model/active_object_interfaces.h"
#include "fsmda/communication/model/mediacapture_object_interfaces.h"
#include "fsmda/communication/model/ondemand_object_interfaces.h"
#include "fsmda/communication/model/passive_object_interfaces.h"
#include "fsmda/paring/device_class_description.h"
#include "fsmda/paring/model/class_handling_interfaces.h"
#include "fsmda/paring/model/device_paring_interfaces.h"
#include <map>
#include <string>

using std::string;
using std::map;

class ParentParingManager : public ClassHandlingPpmInterface,
                            public DeviceParingPpmInterface {
 public:
  // public constructors & destructors
  ParentParingManager();
  virtual ~ParentParingManager();

  // ClassHandlingPpmInterface overloaded methods
  virtual void AddClass(const string& application_id, unsigned int class_index);
  virtual void RemoveClass(const string& application_id,
                           unsigned int class_index);
  virtual void AddClassDescription(
      const string& application_id, unsigned int class_index,
      const string& class_type, unsigned int max_devices,
      unsigned int min_devices, const string& hardware_requirements,
      const string& software_requirements, const string& network_requirements);

  // DeviceParingPpmInterface overloaded methods
  virtual void AddDeviceToClass(const string& application_id,
                                const string& device_address,
                                unsigned int class_index,
                                const string& device_desc);
  virtual void GetChildIndex(const string& application_id,
                             const string& device_address,
                             unsigned int class_index);

  // Methods for factory parent communication managers
  ActivePcmInterface* CreateActivePcm(const string& application_id,
                                      unsigned int class_index);
  MediaCapturePcmInterface* CreateMediaCapturePcm(const string& application_id,
                                                  unsigned int class_index);
  OnDemandPcmInterface* CreateOnDemandPcm(const string& application_id,
                                          unsigned int class_index);
  PassivePcmInterface* CreatePassivePcm(const string& application_id,
                                        unsigned int class_index);

  // Utils methods
  unsigned int GenerateAvaliableIndex(const string& application_id);
  unsigned int GetNumberOfRegistredClasses(const string& application_id);

 private:
  map<const string, map<unsigned int, DeviceClassDescription*> >
      device_class_description_map_;
  unsigned int registred_classes_size_;
};

#endif  // FSMDA_PARING_PARENT_PARING_MANAGER_H_
