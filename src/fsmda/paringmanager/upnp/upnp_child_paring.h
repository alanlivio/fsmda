#ifndef UPNP_CPMH_
#define UPNP_CPMH_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paringmanager/model/device_paring.h"

/*----------------------------------------------------------------------
 |   UpnpCpm class
 +---------------------------------------------------------------------*/
class UpnpCpm : public DeviceParingPcmInterface
{
public:
  // public constructors & destructors
  UpnpCpm ();
  virtual
  ~UpnpCpm ();

  // DeviceParingPcmInterface overloaded methods
  virtual void
  classAnnouncement (const string& applicationID, unsigned int classIndex,
		     const string& classDesc, const string& classFunction);
};

#endif /* UPNP_CPMH_ */
