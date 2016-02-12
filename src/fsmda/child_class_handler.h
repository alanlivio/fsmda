#ifndef FSMDA_CHILD_CLASS_HANDLER_H_
#define FSMDA_CHILD_CLASS_HANDLER_H_

#include <map>
#include <string>
#include "fsmda/model/active_objects_api.h"
#include "fsmda/upnp/upnp_active_ccm.h"
#include "fsmda/upnp/upnp_passive_ccm.h"
#include "fsmda/upnp/upnp_ondemand_ccm.h"
#include "fsmda/upnp/upnp_mediacapture_ccm.h"
#include "fsmda/device_class_description.h"
#include "fsmda/device_description.h"
#include "fsmda/upnp/upnp_cpm.h"

using std::string;
using std::map;

class ChildClassHandler
{
public:
  // public constructors & destructors
  ChildClassHandler(const DeviceDescription&);
  virtual ~ChildClassHandler();

  // public methods
  // called Remote Device
  int start_pairing();
  int stop_pairing();
  bool is_pairing_started();
  bool paired();
  DeviceDescription* device_description();
  void set_passive_player(PassiveClassInterface* player);
  void set_active_player(ActivePlayerInterface* player);
  void set_ondemand_player(OnDemandClassInterface* player);
  void set_mediacapture_player(MediaCaptureClassInterface* player);

  // public melthods
  // called para cpm
  virtual void set_paired(bool paired_);
  PassiveClassInterface* passive_player();
  ActivePlayerInterface* active_player();
  OnDemandClassInterface* ondemand_player();
  MediaCaptureClassInterface* mediacapture_player();

private:
  PassiveClassInterface* passive_player_;
  ActivePlayerInterface* active_player_;
  OnDemandClassInterface* ondemand_player_;
  MediaCaptureClassInterface* mediacapture_player_;
  map<unsigned int, DeviceClassDescription*> device_class_description_map_;
  DeviceDescription* device_description_;
  UpnpCpm* upnp_cpm_;
  bool paired_;
};

#endif // FSMDA_CHILD_CLASS_HANDLER_H_
