#ifndef UPNP_CPMH_
#define UPNP_CPMH_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paringmanager/model/device_paring.h"
#include "NptTypes.h"
#include "PltDeviceHost.h"
#include "PltUPnP.h"

/*----------------------------------------------------------------------
 |   UpnpChildParing class
 +---------------------------------------------------------------------*/
class UpnpChildParing : public PLT_DeviceHost
{
public:
  // public constructors & destructors
  UpnpChildParing (const char* UUID = "");
  virtual
  ~UpnpChildParing ();

  // PLT_DeviceHost methods
  virtual NPT_Result
  SetupServices ();

  // public methods
  int start_service ();
  int stop_service ();
  bool is_service_started ();

private:
  bool service_start_;
  PLT_UPnP* upnp_reference_;
};

#endif /* UPNP_CPMH_ */
