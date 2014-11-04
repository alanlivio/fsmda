#ifndef UPNP_PASSIVE_PCM_H_
#define UPNP_PASSIVE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communicationmanager/model/passive_object_interfaces.h"
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   UpnpPassivePcm  class
 +---------------------------------------------------------------------*/
class UpnpPassivePcm : public PassivePcmInterface
{
public:
  // public constructors & destructors
  UpnpPassivePcm ();
  virtual
  ~UpnpPassivePcm ();

  // PassivePCMInterface overloaded methods
  virtual void
  notifyError (const string& message, const string& objectId);
};

#endif /* UPNP_PASSIVE_PCM_H_ */
