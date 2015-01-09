#ifndef FSMDA_COMMUNICATION_UPNP_ACTIVE_CCM_H_
#define FSMDA_COMMUNICATION_UPNP_ACTIVE_CCM_H_

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
#include "fsmda/model/active_objects_api.h"

using std::string;
using std::vector;
using std::map;

/*----------------------------------------------------------------------
 |   UpnpActiveCcm class
 +---------------------------------------------------------------------*/
class UpnpActiveCcm : public ActiveClassListenerInterface,
                      public PLT_CtrlPointListener {
 public:
  // public constructors & destructors
  UpnpActiveCcm(PLT_DeviceHostReference device_host,
                PLT_CtrlPointReference ctrl_point);
  virtual ~UpnpActiveCcm();

  // ActiveClassListenerInterface overloaded methods
  virtual void RequestPropertyValue(const string& object_id,
                                    const string& name);
  virtual void NotifyEventTransition(const string& object_id,
                                     const string& event_id,
                                     const string& transition);
  virtual void NotifyError(const string& object_id, const string& message);

  // PLT_CtrlPointListener overloaded methods
  virtual NPT_Result OnDeviceAdded(PLT_DeviceDataReference& device);
  virtual NPT_Result OnDeviceRemoved(PLT_DeviceDataReference& device);
  virtual NPT_Result OnActionResponse(NPT_Result res,
                                      PLT_ActionReference& action,
                                      void* userdata);
  virtual NPT_Result OnEventNotify(PLT_Service* service,
                                   NPT_List<PLT_StateVariable*>* vars);

  // called by PLT_DeviceHost
  virtual NPT_Result OnAction(PLT_ActionReference& action,
                              const PLT_HttpRequestContext& context);

  // public methods
  virtual void SetActivePlayer(ActivePlayerInterface* player);

 private:
  PLT_DeviceHostReference device_host_;
  PLT_CtrlPointReference ctrl_point_;
  PLT_DeviceDataReference last_parent_;
  ActivePlayerInterface* player_;
};

#endif  // FSMDA_COMMUNICATION_UPNP_ACTIVE_CCM_H_
