#ifndef FSMDA_PARING_SERVICES_UPNP_CHILD_PARING_H_
#define FSMDA_PARING_SERVICES_UPNP_CHILD_PARING_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <NptTypes.h>
#include <PltAction.h>
#include <PltDeviceHost.h>
#include <PltHttp.h>
#include <PltUPnP.h>
#include <PltCtrlPoint.h>
#include "fsmda/paring_services/paring_service_interface.h"
#include "fsmda/model/device_paring_interfaces.h"

/*----------------------------------------------------------------------
 |   forward definitions
 +---------------------------------------------------------------------*/
class ChildParingManager;

/*----------------------------------------------------------------------
 |   UpnpChildParing class
 +---------------------------------------------------------------------*/
class UpnpChildParing : public PLT_DeviceHost,
                        public PLT_CtrlPointListener,
                        public ParingServiceInterface {
 public:
  // public constructors & destructors
  explicit UpnpChildParing(ChildParingManager* child_paring_manager);
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

  // ParingServiceInterface overloaded methods
  virtual int StartParingService();
  virtual int StopParingService();
  virtual bool IsParingServiceStarted() { return m_Started; }

  // public methods
  bool IsPaired() { return paired_with_parent_; }

 private:
  bool paired_with_parent_;
  PLT_UPnP* upnp_instance_;
  PLT_DeviceHostReference* device_host_;
  PLT_Service* device_service_;
  PLT_CtrlPointReference* ctrl_point_;
  ChildParingManager* child_paring_manager_;
};

#endif  // FSMDA_PARING_SERVICES_UPNP_CHILD_PARING_H_
