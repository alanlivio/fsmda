#ifndef UPNP_ACTIVE_CCM_H_
#define UPNP_ACTIVE_CCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communicationmanager/model/active_object_interfaces.h"
#include <string>
#include <vector>

using namespace std;

/*----------------------------------------------------------------------
 |   UpnpActiveCcm class
 +---------------------------------------------------------------------*/
class UpnpActiveCcm : public ActiveCcmInterface
{
public:
  // public constructors & destructors
  UpnpActiveCcm ();
  virtual
  ~UpnpActiveCcm ();

  // ActiveCcmInterface overloaded methods
  virtual void
  prepare (const string& objectID, const string& objectSrc,
	   vector<Property> properties, vector<Event> evts);
  virtual void
  addEvent (const string& objectID, Event evt);
  virtual void
  removeEvent (const string& objectID, const string& eventID);
  virtual void
  postAction (const string& objectID, const string& eventID,
	      const string& action);
  virtual void
  reportPropertyValue (const string& objectID, const string& name,
		       const string& value);
  virtual void
  setPropertyValue (const string& objectID, const string& name,
		    const string& value, unsigned int duration);
};

#endif /* UPNP_ACTIVE_CCM_H_ */
