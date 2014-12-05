/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication/model/active_object_interfaces.h"
#include "fsmda/communication/upnp_active_ccm.h"

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::UpnpActiveCcm
 +---------------------------------------------------------------------*/
UpnpActiveCcm::UpnpActiveCcm() {
}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::~UpnpActiveCcm
 +---------------------------------------------------------------------*/
UpnpActiveCcm::~UpnpActiveCcm() {

}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::prepare
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::prepare(const string& objectID, const string& objectSrc,
                            vector<Property> properties, vector<Event> evts) {
}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::addEvent
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::addEvent(const string& objectID, Event evt) {
}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::removeEvent
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::removeEvent(const string& objectID, const string& eventID) {
}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::postAction
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::postAction(const string& objectID, const string& eventID,
                               const string& action) {
}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::reportPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::reportPropertyValue(const string& objectID,
                                        const string& name,
                                        const string& value) {
}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::setPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::setPropertyValue(const string& objectID, const string& name,
                                     const string& value,
                                     unsigned int duration) {
}
