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
ActiveCCM::prepare (string objectID, string objectSrc,
		    vector<Property> properties, vector<Event> evts)
{
}
void
ActiveCCM::addEvent (string objectID, Event evt)
{
}

void
ActiveCCM::removeEvent (string objectID, string eventID)
{
}

void
ActiveCCM::postAction (string objectID, string eventID, string action)
{
}

void
ActiveCCM::reportPropertyValue (string objectID, string name, string value)
{
}

void
ActiveCCM::setPropertyValue (string objectID, string name, string value,
			     unsigned int duration)
{
}
