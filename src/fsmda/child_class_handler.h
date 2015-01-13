#ifndef FSMDA_CHILD_CLASS_HANDLER_H_
#define FSMDA_CHILD_CLASS_HANDLER_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <map>
#include <string>
#include "fsmda/model/active_objects_api.h"
#include "fsmda/upnp/upnp_active_ccm.h"
#include "fsmda/upnp/upnp_passive_ccm.h"
#include "fsmda/upnp/upnp_ondemand_ccm.h"
#include "fsmda/upnp/upnp_mediacapture_ccm.h"
#include "fsmda//device_class_description.h"
#include "fsmda//device_description.h"
#include "fsmda/upnp/upnp_cpm.h"

using std::string;
using std::map;

/*----------------------------------------------------------------------
 |   ChildClassHandler class
 +---------------------------------------------------------------------*/
class ChildClassHandler {
 public:
  // public constructors & destructors
  explicit ChildClassHandler(const DeviceDescription&);
  virtual ~ChildClassHandler();

  // public methods
  // called Remote Player
  int StartPairing();
  int StopPairing();
  bool IsPairingStarted();
  bool paired();
  virtual void set_paired(bool paired_);
  DeviceDescription* device_description();
  ActiveClassListenerInterface* CreateActiveCcm(const string& application_id,
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
  UpnpCpm* upnp_cpm_;
  bool paired_;
};

#endif  // FSMDA_CHILD_CLASS_HANDLER_H_
