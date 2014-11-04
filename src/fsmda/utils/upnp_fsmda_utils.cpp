/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/utils/platinumkit.h"
#include "NptList.h"
#include "NptLogging.h"
#include "NptNetwork.h"
#include "NptTime.h"
#include "PltConstants.h"
#include "PltUPnP.h"
#include "PltUtilities.h"
#include <string>

/*----------------------------------------------------------------------
 |   class fields
 +---------------------------------------------------------------------*/
PLT_UPnP* PlatinumKit::upnp_singleton_ = NULL;
unsigned int PlatinumKit::references_count_ = 0;
bool PlatinumKit::upnp_running_ = false;

/*----------------------------------------------------------------------
 |   PlatinumKit::requestUpnpReference
 +---------------------------------------------------------------------*/
PLT_UPnP*
PlatinumKit::requestUpnpReference ()
{
  if (PlatinumKit::upnp_singleton_ == NULL)
    {
      // setup Neptune logging
      NPT_LogManager::GetDefault ().Configure (
	  "plist:.level=FINE;.handlers=ConsoleHandler;.ConsoleHandler.colors=off;.ConsoleHandler.filter=42");

      // setup upnp service
      PLT_Constants::GetInstance ().SetDefaultDeviceLease (
	  NPT_TimeInterval (60.));
      NPT_List<NPT_IpAddress> list;
      PLT_UPnPMessageHelper::GetIPAddresses (list);
      PlatinumKit::upnp_singleton_ = new PLT_UPnP ();
      PlatinumKit::upnp_singleton_->Start ();
      PlatinumKit::references_count_ = 0;
      PlatinumKit::upnp_running_ = true;
    }
  return PlatinumKit::upnp_singleton_;
}

/*----------------------------------------------------------------------
 |   PlatinumKit::releaseUpnpReference
 +---------------------------------------------------------------------*/
void
PlatinumKit::releaseUpnpReference ()
{
  if (PlatinumKit::references_count_ == 0)
    return;
  else if (PlatinumKit::references_count_ == 1)
    {
      PlatinumKit::upnp_singleton_->Stop ();
      delete upnp_singleton_;
      PlatinumKit::upnp_singleton_ = NULL;
      PlatinumKit::references_count_ = 0;
      PlatinumKit::upnp_running_ = false;
    }
  else
    PlatinumKit::references_count_--;
}

