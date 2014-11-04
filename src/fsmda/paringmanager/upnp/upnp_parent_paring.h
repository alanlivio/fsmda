#ifndef UPNP_PPMH_
#define UPNP_PPMH_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paringmanager/model/class_handling_interfaces.h"
#include "fsmda/paringmanager/model/device_paring_interfaces.h"
#include "NptTypes.h"
#include "PltDeviceHost.h"
#include "PltUPnP.h"
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   UpnpPpm class
 +---------------------------------------------------------------------*/
class UpnpParentParing : public PLT_DeviceHost
{
public:
  // public constructors & destructors

  UpnpParentParing (const char* UUID = "");
  virtual
  ~UpnpParentParing ();

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

#endif /* UPNP_PPMH_ */
