#ifndef FSMDA_UPNP_UPNP_ACTIVE_PCM_H_
#define FSMDA_UPNP_UPNP_ACTIVE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include <map>
#include <vector>
#include <NptTypes.h>
#include <PltDeviceHost.h>
#include <PltUPnP.h>
#include <PltCtrlPoint.h>
#include "fsmda/model/active_objects_api.h"

using std::string;
using std::vector;
using std::map;

/*----------------------------------------------------------------------
 |   UpnpActivePcm class
 +---------------------------------------------------------------------*/
class UpnpActivePcm : public ActiveClassInterface,
                      public PLT_CtrlPointListener {
 public:
  // public constructors & destructors
  UpnpActivePcm(PLT_DeviceHostReference host_device,
                PLT_DeviceDataReference& remote_device,
                PLT_CtrlPointReference ctrl_point, const string& application_id,
                unsigned int class_index);
  virtual ~UpnpActivePcm();

  // ActiveClassInterface overloaded methods
  // called by HostHpe
  virtual void Prepare(const string& object_id, const string& object_src,
                       vector<Property> properties, vector<Event> evts);
  virtual void AddEvent(const string& object_id, Event evt);
  virtual void RemoveEvent(const string& object_id, const string& event_id);
  virtual void PostAction(const string& object_id, const string& event_id,
                          const string& action);
  virtual void RequestPropertyValue(const string& object_id,
                                    const string& property_name);
  virtual void SetPropertyValue(const string& object_id,
                                const string& property_name,
                                const string& property_value,
                                unsigned int property_duration);
  virtual void RegistryActiveClassListener(ActiveClassListenerInterface* hpe);

  // PLT_CtrlPointListener overloaded methods
  virtual NPT_Result OnDeviceAdded(PLT_DeviceDataReference& device);
  virtual NPT_Result OnDeviceRemoved(PLT_DeviceDataReference& device);
  virtual NPT_Result OnActionResponse(NPT_Result res,
                                      PLT_ActionReference& action,
                                      void* userdata);
  virtual NPT_Result OnEventNotify(PLT_Service* service,
                                   NPT_List<PLT_StateVariable*>* vars);

  // public methods
  // called by UpnpPpm
  virtual NPT_Result OnAction(PLT_ActionReference& action,
                              const PLT_HttpRequestContext& context);
  void UpdateRemoteHostAndExecuteStoredActions(
      PLT_DeviceDataReference& remote_device);

 private:
  PLT_DeviceHostReference device_host_;
  PLT_CtrlPointReference ctrl_point_;
  PLT_DeviceDataReference remote_device_;
  PLT_DeviceDataReference last_parent_;
  ActiveClassListenerInterface* hpe_;
  string application_id_;
  unsigned int class_index_;
  NPT_SharedVariable post_action_semaphore;
  NPT_SharedVariable request_var_action_semaphore;
  NPT_SharedVariable set_var_action_semaphore;
  NPT_SharedVariable prepare_action_semaphore;
  vector<PLT_ActionReference> invoked_actions_;
};

#endif  // FSMDA_UPNP_UPNP_ACTIVE_PCM_H_
