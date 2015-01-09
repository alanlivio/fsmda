#ifndef FSMDA_CHILD_PAIRING_MANAGER_H_
#define FSMDA_CHILD_PAIRING_MANAGER_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <map>
#include <string>
#include "fsmda/model/active_objects_api.h"
#include "fsmda/communication/upnp_active_ccm.h"
#include "fsmda/communication/upnp_passive_ccm.h"
#include "fsmda/communication/upnp_ondemand_ccm.h"
#include "fsmda/communication/upnp_mediacapture_ccm.h"
#include "fsmda/class_handling/device_class_description.h"
#include "fsmda/class_handling/device_description.h"
#include "fsmda/pairing/upnp_child_pairing.h"

using std::string;
using std::map;

/*----------------------------------------------------------------------
 |   ChildPairingManager class
 +---------------------------------------------------------------------*/
class ChildPairingManager : public ChildPairingInterface {
 public:
  // public constructors & destructors
  explicit ChildPairingManager(const DeviceDescription&);
  virtual ~ChildPairingManager();

  // public methods
  // called by ParentPairingManager
  int StartPairing();
  int StopPairing();
  bool IsPairingStarted();
  bool paired();
  virtual void set_paired(bool paired_);
  DeviceDescription* device_description();

  // public ChildPairingInterface overloaded methods
  // called by ParentPairingManager
  virtual void ClassAnnouncement(const string& application_id,
                                 unsigned int class_index,
                                 const string& class_desc,
                                 const string& class_function);

  // Method for factory child communication managers
  // called by ParentPairingManager
  ActiveClassInterface* CreateActiveCcm(const string& application_id,
                                        unsigned int class_index);
  MediaCaptureClassInterface* CreateMediaCaptureCcm(
      const string& application_id, unsigned int class_index);
  PassiveClassInterface* CreatePassiveCcm(const string& application_id,
                                          unsigned int class_index);
  OnDemandClassInterface* CreateOndemandCcm(const string& application_id,
                                            unsigned int class_index);

 private:
  map<unsigned int, DeviceClassDescription*> device_class_description_map_;
  DeviceDescription* device_description_;
  UpnpChildPairing* upnp_child_pairing_;
  bool paired_;
};

#endif  // FSMDA_CHILD_PAIRING_MANAGER_H_
