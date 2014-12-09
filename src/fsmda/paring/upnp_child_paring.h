#ifndef FSMDA_PARING_UPNP_CHILD_PARING_H_
#define FSMDA_PARING_UPNP_CHILD_PARING_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paring/model/device_paring_interfaces.h"
#include "NptTypes.h"
#include "PltAction.h"
#include "PltDeviceHost.h"
#include "PltHttp.h"
#include "PltUPnP.h"
#include "PltCtrlPoint.h"

/*----------------------------------------------------------------------
 |   UpnpChildParing class
 +---------------------------------------------------------------------*/
class UpnpChildParing : public PLT_DeviceHost, public PLT_CtrlPointListener {
 public:
  // public constructors & destructors
  UpnpChildParing();
  virtual ~UpnpChildParing();

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

  // public methods
  int StartService();
  int StopService();
  bool IsServiceStarted();
  bool IsPaired();

 private:
  PLT_UPnP* upnp_instance_;
  PLT_DeviceHostReference* device_host_;
  PLT_Service* device_service_;
  PLT_CtrlPointReference* ctrl_point_;
  bool paired_with_parent_;
};

#endif  // FSMDA_PARING_UPNP_CHILD_PARING_H_
