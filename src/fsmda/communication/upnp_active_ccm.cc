/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication/model/active_object_interfaces.h"
#include "fsmda/communication/upnp_active_ccm.h"

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::UpnpActiveCcm
 +---------------------------------------------------------------------*/
UpnpActiveCcm::UpnpActiveCcm() {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::~UpnpActiveCcm
 +---------------------------------------------------------------------*/
UpnpActiveCcm::~UpnpActiveCcm() {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::Prepare
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::Prepare(const string& object_id, const string& object_src,
                            vector<Property> properties, vector<Event> evts) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::AddEvent
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::AddEvent(const string& object_id, Event evt) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::RemoveEvent
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::RemoveEvent(const string& object_id,
                                const string& event_id) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::PostAction
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::PostAction(const string& object_id, const string& event_id,
                               const string& action) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::ReportPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::ReportPropertyValue(const string& object_id,
                                        const string& name,
                                        const string& value) {}

/*----------------------------------------------------------------------
 |   UpnpActiveCcm::SetPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActiveCcm::SetPropertyValue(const string& object_id,
                                     const string& name, const string& value,
                                     unsigned int duration) {}
