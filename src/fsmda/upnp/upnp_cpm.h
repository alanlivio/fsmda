#ifndef FSMDA_UPNP_UPNP_CPM_H_
#define FSMDA_UPNP_UPNP_CPM_H_

#include <map>
#include <string>
#include <NptTypes.h>
#include <PltDeviceHost.h>
#include <PltUPnP.h>
#include <PltCtrlPoint.h>
#include "fsmda/model/device_pairing_api.h"
#include "fsmda/model/class_handling_api.h"
#include "fsmda/model/passive_objects_api.h"
#include "fsmda/model/active_objects_api.h"
#include "fsmda/model/ondemand_objects_api.h"
#include "fsmda/model/mediacapture_objects_api.h"
#include "fsmda/upnp/upnp_active_ccm.h"
#include "fsmda/upnp/upnp_passive_ccm.h"
#include "fsmda/upnp/upnp_ondemand_ccm.h"
#include "fsmda/upnp/upnp_mediacapture_ccm.h"

using std::map;
using std::string;


class ChildClassHandler;


class UpnpCpm : public PLT_DeviceHost,
                public PLT_CtrlPointListener,
                public ParentPairingInterface {
 public:
  // public constructors & destructors
  UpnpCpm();
  ~UpnpCpm();

  // ParentPairingInterface overloaded methods
  // called byParentClassHandler
  virtual void AddDeviceToClass(const string& application_id,
                                const string& device_address,
                                unsigned int class_index,
                                const string& device_desc);
  virtual void GetChildIndex(const string& application_id,
                             const string& device_address,
                             unsigned int class_index);

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
  // called by ChildClassHandler
  virtual int StartPairingService();
  virtual int StopPairingService();
  virtual bool IsPairingServiceStarted();
  virtual int set_service_owner(ChildClassHandler* service_owner);
  ActiveClassListenerInterface* CreateActiveCcm(const string& application_id,
                                                unsigned int class_index);
  MediaCaptureClassInterface* CreateMediaCaptureCcm(
      const string& application_id, unsigned int class_index);
  OnDemandClassInterface* CreateOnDemandCcm(const string& application_id,
                                            unsigned int class_index);
  PassiveClassInterface* CreatePassiveCcm(const string& application_id,
                                          unsigned int class_index);

 private:
  PLT_UPnP* upnp_instance_;
  PLT_DeviceHostReference device_host_;
  PLT_CtrlPointReference ctrl_point_;
  PLT_Service* ppm_service_;
  PLT_Service* passive_service_;
  PLT_Service* active_service_;
  PLT_Service* ondemand_service_;
  PLT_Service* mediacapture_service_;
  ChildClassHandler* child_class_handler_;
  PLT_DeviceDataReference last_parent_;
  NPT_SharedVariable last_parent_semaphore;
  map<const string, map<unsigned int, UpnpPassiveCcm*> > passive_ccm_map_;
  map<const string, map<unsigned int, UpnpActiveCcm*> > active_ccm_map_;
  map<const string, map<unsigned int, UpnpOnDemandCcm*> > ondemand_ccm_map_;
  map<const string, map<unsigned int, UpnpMediaCaptureCcm*> >
      mediacapture_ccm_map_;
};

#endif  // FSMDA_UPNP_UPNP_CPM_H_
