#ifndef FSMDA_PARENT_PAIRING_MANAGER_H_
#define FSMDA_PARENT_PAIRING_MANAGER_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <map>
#include <set>
#include <string>
#include <vector>
#include "fsmda/device_class_description.h"
#include "fsmda/model/active_objects_api.h"
#include "fsmda/model/mediacapture_objects_api.h"
#include "fsmda/model/ondemand_objects_api.h"
#include "fsmda/model/passive_objects_api.h"
#include "fsmda/model/class_handling_api.h"
#include "fsmda/model/device_pairing_api.h"
#include "fsmda/pairing/upnp_parent_pairing.h"
#include "fsmda/communication/communication_service_interface.h"

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
  CommunicationServiceInterface* communication_service;
  vector<string> registred_devices_;
};

/*----------------------------------------------------------------------
 |   ParentPairingManager class
 +---------------------------------------------------------------------*/
class ParentPairingManager : public ClassHandlingPpmInterface,
                             public DevicePairingPpmInterface {
 public:
  // public constructors & destructors
  ParentPairingManager();
  virtual ~ParentPairingManager();

  // public DevicePairingPpmInterface overloaded methods
  // called by remote ChildPairingManager
  virtual void AddDeviceToClass(const string& application_id,
                                const string& device_address,
                                unsigned int class_index,
                                const string& device_desc);
  virtual void GetChildIndex(const string& application_id,
                             const string& device_address,
                             unsigned int class_index);

  // public ClassHandlingPpmInterface overloaded methods
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
  virtual void SetClassHandlingHPE(const string& application_id,
                                   ClassHandlingHpeInterface* hpe);
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
  virtual unsigned int GetNumberOfRegistredChildren(
      const string& application_id, unsigned int class_index);

  int StartPairing();
  int StopPairing();
  bool IsPairingStarted();

 private:
  // private filds
  unsigned int upnp_registred_classes_size;
  map<const string, map<unsigned int, ApplicationClassData*> >
      application_class_data_map_;
  UpnpParentPairing* upnp_parent_pairing_;
  map<const string, ClassHandlingHpeInterface*> hpes_map_;
};

#endif  // FSMDA_PARENT_PAIRING_MANAGER_H_
