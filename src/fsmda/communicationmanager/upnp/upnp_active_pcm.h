#ifndef UPNP_ACTIVE_PCM_H_
#define UPNP_ACTIVE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communicationmanager/model/active_object_interfaces.h"
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   UpnpActivePcm class
 +---------------------------------------------------------------------*/
class UpnpActivePcm : public ActivePcmInterface
{
public:
  // public constructors & destructors
  UpnpActivePcm ();
  virtual
  ~UpnpActivePcm ();

  // ActivePcmInterface overloaded methods
  virtual void
  requestPropertyValue (const string& objectID, const string& name);
  virtual void
  notifyEventTransition (const string& objectID, const string& eventID,
			 const string& transition);
  virtual void
  notifyError (const string& objectID, const string& message);
};

#endif /* UPNP_ACTIVE_PCM_H_ */
