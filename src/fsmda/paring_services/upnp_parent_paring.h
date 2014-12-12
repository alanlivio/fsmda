#ifndef FSMDA_PARING_SERVICES_UPNP_PARENT_PARING_H_
#define FSMDA_PARING_SERVICES_UPNP_PARENT_PARING_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>
#include <vector>
#include <NptTypes.h>
#include <PltDeviceHost.h>
#include <PltUPnP.h>
#include <PltCtrlPoint.h>
#include "fsmda/paring_services/paring_service_interface.h"
#include "fsmda/model/class_handling_interfaces.h"
#include "fsmda/model/device_paring_interfaces.h"

using std::string;
using std::vector;

/*----------------------------------------------------------------------
 |   forward definitions
 +---------------------------------------------------------------------*/
class ParentParingManager;

/*----------------------------------------------------------------------
 |   UpnpPpm class
 +---------------------------------------------------------------------*/
class UpnpParentParing : public PLT_DeviceHost,
                         public PLT_CtrlPointListener,
                         public ParingServiceInterface {
 public:
  // public constructors & destructors

  explicit UpnpParentParing(ParentParingManager* parent_paring_manager);
  virtual ~UpnpParentParing();

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
  virtual int StartParingService();
  virtual int StopParingService();
  virtual bool IsParingServiceStarted() { return m_Started; }
  unsigned int paired_childs() { return paired_childs_; }

 private:
  unsigned int paired_childs_;
  PLT_UPnP* upnp_instance_;
  PLT_DeviceHostReference* device_host_;
  PLT_Service* device_service_;
  PLT_CtrlPointReference* ctrl_point_;
  vector<PLT_DeviceDataReference> discoverd_cpm_;
  ParentParingManager* parent_paring_manager_;
};

#endif  // FSMDA_PARING_SERVICES_UPNP_PARENT_PARING_H_
