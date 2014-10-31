/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/gingancl/communication/active_ccm.h>

/*----------------------------------------------------------------------
 |   ActiveCCM::ActiveCCM
 +---------------------------------------------------------------------*/
ActiveCCM::ActiveCCM ()
{
}

/*----------------------------------------------------------------------
 |   ActiveCCM::~ActiveCCM
 +---------------------------------------------------------------------*/
ActiveCCM::~ActiveCCM ()
{

}

/*----------------------------------------------------------------------
 |   ActiveCCM::prepare
 +---------------------------------------------------------------------*/
void
ActiveCCM::prepare (const string& objectID, const string& objectSrc,
		    vector<Property> properties, vector<Event> evts)
{
}

/*----------------------------------------------------------------------
 |   ActiveCCM::addEvent
 +---------------------------------------------------------------------*/
void
ActiveCCM::addEvent (const string& objectID, Event evt)
{
}

/*----------------------------------------------------------------------
 |   ActiveCCM::removeEvent
 +---------------------------------------------------------------------*/
void
ActiveCCM::removeEvent (const string& objectID, const string& eventID)
{
}

/*----------------------------------------------------------------------
 |   ActiveCCM::postAction
 +---------------------------------------------------------------------*/
void
ActiveCCM::postAction (const string& objectID, const string& eventID,
		       const string& action)
{
}

/*----------------------------------------------------------------------
 |   ActiveCCM::reportPropertyValue
 +---------------------------------------------------------------------*/
void
ActiveCCM::reportPropertyValue (const string& objectID, const string& name,
				const string& value)
{
}

/*----------------------------------------------------------------------
 |   ActiveCCM::setPropertyValue
 +---------------------------------------------------------------------*/
void
ActiveCCM::setPropertyValue (const string& objectID, const string& name,
			     const string& value, unsigned int duration)
{
}
