/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication_services/upnp_active_pcm.h"

/*----------------------------------------------------------------------
 |   UpnpActivePcm::UpnpActivePcm
 +---------------------------------------------------------------------*/
UpnpActivePcm::UpnpActivePcm() {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::~UpnpActivePcm
 +---------------------------------------------------------------------*/
UpnpActivePcm::~UpnpActivePcm() {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::RequestPropertyValue
 +---------------------------------------------------------------------*/
void UpnpActivePcm::RequestPropertyValue(const string& object_id,
                                         const string& name) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::NotifyEventTransition
 +---------------------------------------------------------------------*/
void UpnpActivePcm::NotifyEventTransition(const string& object_id,
                                          const string& event_id,
                                          const string& transition) {}

/*----------------------------------------------------------------------
 |   UpnpActivePcm::NotifyError
 +---------------------------------------------------------------------*/
void UpnpActivePcm::NotifyError(const string& object_id,
                                const string& message) {}
