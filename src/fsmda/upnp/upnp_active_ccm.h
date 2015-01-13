#ifndef FSMDA_UPNP_UPNP_ACTIVE_CCM_H_
#define FSMDA_UPNP_UPNP_ACTIVE_CCM_H_

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
  UpnpActiveCcm(PLT_DeviceHostReference host_device,
                PLT_DeviceDataReference& remote_device,
                PLT_CtrlPointReference ctrl_point, const string& application_id,
                unsigned int class_index);
  virtual ~UpnpActiveCcm();

  // ActiveClassListenerInterface overloaded methods
  // called by RemotePlayer
  virtual void ReportPropertyValue(const string& object_id, const string& name,
                                   const string& value);

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

  // public methods
  // called by UpnpCpmManger
  virtual NPT_Result OnAction(PLT_ActionReference& action,
                              const PLT_HttpRequestContext& context);

 private:
  PLT_DeviceHostReference host_device_;
  PLT_DeviceDataReference remote_device_;
  PLT_CtrlPointReference ctrl_point_;
  PLT_DeviceDataReference last_parent_;
  ActivePlayerInterface* player_;
  string application_id_;
  unsigned int class_index_;
};

#endif  // FSMDA_UPNP_UPNP_ACTIVE_CCM_H_
