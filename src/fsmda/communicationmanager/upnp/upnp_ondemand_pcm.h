#ifndef UPNP_ONDEMAND_PCM_H_
#define UPNP_ONDEMAND_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communicationmanager/model/ondemand_object_control.h"
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   UpnpOnDemandPcm class
 +---------------------------------------------------------------------*/
class UpnpOnDemandPcm : public OnDemandPcmInterface
{
public:
  // public constructors & destructors
  UpnpOnDemandPcm ();
  virtual
  ~UpnpOnDemandPcm ();

  // OnDemandPCMInterface overloaded methods
  virtual void
  notifyOnDemandContent (const string& action, const string& location);
};

#endif /* UPNP_ONDEMAND_PCM_H_ */
