#ifndef FSMDA_PARING_UPNP_PARENT_PARING_H_
#define FSMDA_PARING_UPNP_PARENT_PARING_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>
#include <vector>
#include "fsmda/paring/model/class_handling_interfaces.h"
#include "fsmda/paring/model/device_paring_interfaces.h"
#include "NptTypes.h"
#include "PltDeviceHost.h"
#include "PltUPnP.h"
#include "PltCtrlPoint.h"

using std::string;
using std::vector;

/*----------------------------------------------------------------------
 |   forward definitions
 +---------------------------------------------------------------------*/
class ParentParingManager;

/*----------------------------------------------------------------------
 |   UpnpPpm class
 +---------------------------------------------------------------------*/
class UpnpParentParing : public PLT_DeviceHost, public PLT_CtrlPointListener {
 public:
  // public constructors & destructors

  UpnpParentParing();
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
  int StartService();
  int StopService();
  void SetParentParingManager(ParentParingManager* parent_paring_manager);
  bool IsServiceStarted() { return m_Started; }
  unsigned int paired_childs() { return paired_childs_; }

 private:
  PLT_UPnP* upnp_instance_;
  PLT_DeviceHostReference* device_host_;
  PLT_Service* device_service_;
  PLT_CtrlPointReference* ctrl_point_;
  unsigned int paired_childs_;
  vector<PLT_DeviceDataReference> discoverd_cpm_;
  ParentParingManager* parent_paring_manager_;
};

#endif  // FSMDA_PARING_UPNP_PARENT_PARING_H_
