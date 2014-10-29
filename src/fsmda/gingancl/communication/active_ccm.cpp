#include "active_ccm.h"

ActiveCCM::ActiveCCM ()
{
  // TODO Auto-generated constructor stub

}

ActiveCCM::~ActiveCCM ()
{
  // TODO Auto-generated destructor stub
}

//////////////////// ActiveCCMInterface functions ////////////////////
void
ActiveCCM::prepare (const string&  objectID, const string&  objectSrc,
		    vector<Property> properties, vector<Event> evts)
{
}
void
ActiveCCM::addEvent (const string&  objectID, Event evt)
{
}

void
ActiveCCM::removeEvent (const string&  objectID, const string&  eventID)
{
}

void
ActiveCCM::postAction (const string&  objectID, const string&  eventID, const string&  action)
{
}

void
ActiveCCM::reportPropertyValue (const string&  objectID, const string&  name, const string&  value)
{
}

void
ActiveCCM::setPropertyValue (const string&  objectID, const string&  name, const string&  value,
			     unsigned int duration)
{
}
