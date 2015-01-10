#ifndef FSMDA_COMMUNICATION_UPNP_ACTIVE_PCM_H_
#define FSMDA_COMMUNICATION_UPNP_ACTIVE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include <map>
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
  UpnpActivePcm(PLT_DeviceHostReference device_host,
                PLT_CtrlPointReference ctrl_point);
  virtual ~UpnpActivePcm();

  // ActiveClassInterface overloaded methods
  virtual void Prepare(const string& object_id, const string& object_src,
                       vector<Property> properties, vector<Event> evts);
  virtual void AddEvent(const string& object_id, Event evt);
  virtual void RemoveEvent(const string& object_id, const string& event_id);
  virtual void PostAction(const string& object_id, const string& event_id,
                          const string& action);
  virtual void RequestPropertyValue(const string& object_id,
                                    const string& name);
  virtual void SetPropertyValue(const string& object_id, const string& name,
                                const string& value, unsigned int duration);
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
  // called by UpnpParentPairingManager
  virtual NPT_Result OnAction(PLT_ActionReference& action,
                              const PLT_HttpRequestContext& context);

 private:
  PLT_DeviceHostReference device_host_;
  PLT_CtrlPointReference ctrl_point_;
  PLT_DeviceDataReference last_parent_;
  ActiveClassListenerInterface* hpe_;
};

#endif  // FSMDA_COMMUNICATION_UPNP_ACTIVE_PCM_H_
