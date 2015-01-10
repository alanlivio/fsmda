#ifndef FSMDA_PARENT_PAIRING_MANAGER_H_
#define FSMDA_PARENT_PAIRING_MANAGER_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <map>
#include <set>
#include <string>
#include <vector>
#include "fsmda//device_class_description.h"
#include "fsmda/model/active_objects_api.h"
#include "fsmda/model/mediacapture_objects_api.h"
#include "fsmda/model/ondemand_objects_api.h"
#include "fsmda/model/passive_objects_api.h"
#include "fsmda/model/class_handling_api.h"
#include "fsmda/model/device_pairing_api.h"
#include "fsmda/upnp/upnp_ppm.h"

using std::string;
using std::map;
using std::set;
using std::vector;

/*----------------------------------------------------------------------
 |   ApplicationClassData class
 +---------------------------------------------------------------------*/

class ApplicationClassData {
 public:
  DeviceClassDescription* device_class_description_;
  vector<string> registred_devices_;
};

/*----------------------------------------------------------------------
 |   ParentClassHandler class
 +---------------------------------------------------------------------*/
class ParentClassHandler : public ParentClassHandlingInterface {
 public:
  // public constructors & destructors
  ParentClassHandler();
  virtual ~ParentClassHandler();

  // public ParentClassHandlingInterface overloaded methods
  // called by HypermediaEngine
  virtual void AddClass(const string& application_id, unsigned int class_index);
  virtual void RemoveClass(const string& application_id,
                           unsigned int class_index);
  virtual void AddClassDescription(
      const string& application_id, unsigned int class_index,
      const string& class_type, unsigned int max_devices,
      unsigned int min_devices, const string& hardware_requirements,
      const string& software_requirements, const string& network_requirements);
  virtual void AddClassDescription(
      const string& application_id, unsigned int class_index,
      DeviceClassDescription* device_class_description);
  virtual void SetClassHandlingHpe(const string& application_id,
                                   HpeClassHandlingInterface* hpe);

  // public methods
  // called by HypermediaEngine
  unsigned int GenerateAvaliableIndex(const string& application_id);
  unsigned int GetNumberOfRegistredClasses(const string& application_id);
  unsigned int GetNumberOfRegistredChildren(const string& application_id,
                                            unsigned int class_index);
  int StartPairing();
  int StopPairing();
  bool IsPairingStarted();
  PassiveClassListenerInterface* CreatePassivePcm(const string& application_id,
                                                  unsigned int class_index);
  ActiveClassInterface* CreateActivePcm(const string& application_id,
                                        unsigned int class_index);
  MediaCaptureClassListenerInterface* CreateMediaCapturePcm(
      const string& application_id, unsigned int class_index);
  OnDemandClassListenerInterface* CreateOnDemandPcm(
      const string& application_id, unsigned int class_index);

  // public methods
  // called by Ppm
  HpeClassHandlingInterface* GetClassHandlingHpe(const string& application_id);
  virtual void AddDeviceToClass(const string& application_id,
                                const string& device_address,
                                unsigned int class_index,
                                const string& device_desc);
  virtual void GetChildIndex(const string& application_id,
                             const string& device_address,
                             unsigned int class_index);

 private:
  // private filds
  map<const string, HpeClassHandlingInterface*> hpes_map_;
  unsigned int upnp_registred_classes_size;
  map<const string, map<unsigned int, ApplicationClassData*> >
      application_class_data_map_;
  UpnpPpm* upnp_ppm_;
};

#endif  // FSMDA_PARENT_PAIRING_MANAGER_H_
