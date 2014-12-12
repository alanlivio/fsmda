#ifndef FSMDA_PARENT_PAIRING_MANAGER_H_
#define FSMDA_PARENT_PAIRING_MANAGER_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <map>
#include <set>
#include <string>
#include "fsmda/device_class_description.h"
#include "fsmda/model/active_object_interfaces.h"
#include "fsmda/model/mediacapture_object_interfaces.h"
#include "fsmda/model/ondemand_object_interfaces.h"
#include "fsmda/model/passive_object_interfaces.h"
#include "fsmda/model/class_handling_interfaces.h"
#include "fsmda/model/device_pairing_interfaces.h"
#include "fsmda/pairing_services/upnp_parent_pairing.h"

using std::string;
using std::map;
using std::set;

/*----------------------------------------------------------------------
 |   ParentPairingManager class
 +---------------------------------------------------------------------*/
class ParentPairingManager : public ClassHandlingPpmInterface,
                            public DevicePairingPpmInterface {
 public:
  // public constructors & destructors
  ParentPairingManager();
  virtual ~ParentPairingManager();

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

  // DevicePairingPpmInterface overloaded methods
  // called by remote ChildPairingManager
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
  int StartPairing();
  int StopPairing();
  bool IsPairingStarted();

 private:
  // private filds
  unsigned int upnp_registred_classes_size;
  map<const string, map<unsigned int, DeviceClassDescription*> >
      device_class_description_map_;
  UpnpParentPairing* upnp_parent_pairing_;
};

#endif  // FSMDA_PARENT_PAIRING_MANAGER_H_
