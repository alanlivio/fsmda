#ifndef FSMDA_PARING_UPNP_PARENT_PARING_H_
#define FSMDA_PARING_UPNP_PARENT_PARING_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paring/model/class_handling_interfaces.h"
#include "fsmda/paring/model/device_paring_interfaces.h"
#include "NptTypes.h"
#include "PltDeviceHost.h"
#include "PltUPnP.h"
#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   UpnpPpm class
 +---------------------------------------------------------------------*/
class UpnpParentParing : public PLT_DeviceHost {
 public:
  // public constructors & destructors

  explicit UpnpParentParing(const char* UUID = "");
  virtual
  ~UpnpParentParing();

  // PLT_DeviceHost overloaded methods
  virtual NPT_Result
  SetupServices();
  virtual NPT_Result
  OnAction(PLT_ActionReference& action,
           const PLT_HttpRequestContext& context);

  // public methods
  int
  start_service();
  int
  stop_service();
  bool
  is_service_started();

 private:
  bool service_start_;
  PLT_UPnP* upnp_reference_;
  PLT_DeviceHostReference * device_reference_;
};

#endif  // FSMDA_PARING_UPNP_PARENT_PARING_H_
