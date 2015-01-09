#ifndef FSMDA_PAIRING_UPNP_PARENT_PAIRING_H_
#define FSMDA_PAIRING_UPNP_PARENT_PAIRING_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>
#include <vector>
#include <map>
#include <NptTypes.h>
#include <PltDeviceHost.h>
#include <PltUPnP.h>
#include <PltCtrlPoint.h>
#include "fsmda/model/class_handling_api.h"
#include "fsmda/model/device_pairing_api.h"
#include "fsmda/model/passive_objects_api.h"
#include "fsmda/model/active_objects_api.h"
#include "fsmda/model/ondemand_objects_api.h"
#include "fsmda/model/mediacapture_objects_api.h"
#include "fsmda/pairing/pairing_service_interfaces.h"

using std::string;
using std::vector;
using std::map;

/*----------------------------------------------------------------------
 |   forward definitions
 +---------------------------------------------------------------------*/
class ParentPairingManager;

/*----------------------------------------------------------------------
 |   UpnpPpm class
 +---------------------------------------------------------------------*/
class UpnpParentPairing : public PLT_DeviceHost,
                          public PLT_CtrlPointListener,
                          public ChildPairingInterface,
                          public ParentPairingServiceInterface {
 public:
  // public constructors & destructors
  UpnpParentPairing();
  ~UpnpParentPairing();

  // ChildPairingInterface overloaded methods
  virtual void ClassAnnouncement(const string& application_id,
                                 unsigned int class_index,
                                 const string& class_desc,
                                 const string& class_function);

  // PLT_DeviceHost overloaded methods
  virtual NPT_Result SetupServices();
  virtual NPT_Result OnAction(PLT_ActionReference& action,
                              const PLT_HttpRequestContext& context);
  // PLT_CtrlPointListener overloaded methods
  virtual NPT_Result OnDeviceAdded(PLT_DeviceDataReference& device);
  virtual NPT_Result OnDeviceRemoved(PLT_DeviceDataReference& device);
  virtual NPT_Result OnActionResponse(NPT_Result res,
                                      PLT_ActionReference& action,
                                      void* userdata);
  virtual NPT_Result OnEventNotify(PLT_Service* service,
                                   NPT_List<PLT_StateVariable*>* vars);

  // ParentPairingServiceInterface overloaded methods
  // called by ParentPairingManager
  virtual int AddDeviceClassForDiscover(
      DeviceClassDiscoverParams* discover_params);
  virtual int RemoveDeviceClassForDiscover(
      DeviceClassDiscoverParams* discover_params);
  virtual int StartPairingService();
  virtual int StopPairingService();
  virtual int set_service_owner(ParentPairingManager* service_owner);
  virtual bool IsPairingServiceStarted();
  virtual unsigned int registred_children();
  ActiveClassInterface* CreateActivePcm(const string& application_id,
                                                unsigned int class_index);
  MediaCaptureClassListenerInterface* CreateMediaCapturePcm(
      const string& application_id, unsigned int class_index);
  OnDemandClassListenerInterface* CreateOnDemandPcm(
      const string& application_id, unsigned int class_index);
  PassiveClassListenerInterface* CreatePassivePcm(const string& application_id,
                                                  unsigned int class_index);

 private:
  PLT_UPnP* upnp_instance_;
  PLT_DeviceHostReference device_host_;
  PLT_CtrlPointReference ctrl_point_;
  PLT_Service* device_service_;
  vector<PLT_DeviceDataReference> discovered_children_;
  vector<DeviceClassDiscoverParams*> discover_params_list_;
  ParentPairingManager* parent_pairing_manager_;
};

#endif  // FSMDA_PAIRING_UPNP_PARENT_PAIRING_H_
