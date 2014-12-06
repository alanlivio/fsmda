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

/*----------------------------------------------------------------------
 |   UpnpChildParing class
 +---------------------------------------------------------------------*/
class UpnpChildParing : public PLT_DeviceHost {
 public:
  // public constructors & destructors
  explicit UpnpChildParing(const char* uuid = "");
  virtual ~UpnpChildParing();

  // PLT_DeviceHost overloaded methods
  virtual NPT_Result SetupServices();
  virtual NPT_Result OnAction(PLT_ActionReference& action,
                              const PLT_HttpRequestContext& context);

  // public methods
  int StartService();
  int StopService();
  bool IsServiceStarted();

 private:
  PLT_UPnP* upnp_reference_;
  PLT_Service* upnp_device_service_;
};

#endif  // FSMDA_PARING_UPNP_CHILD_PARING_H_