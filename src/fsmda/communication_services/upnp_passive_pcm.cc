/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication_services/upnp_passive_pcm.h"

/*----------------------------------------------------------------------
 |   UPnPPassivePCM::UPnPPassivePCM
 +---------------------------------------------------------------------*/
UpnpPassivePcm::UpnpPassivePcm() {}

/*----------------------------------------------------------------------
 |   UPnPPassivePCM::~UPnPPassivePCM
 +---------------------------------------------------------------------*/
UpnpPassivePcm::~UpnpPassivePcm() {}

/*----------------------------------------------------------------------
 |   UPnPPassivePCM::NotifyError
 +---------------------------------------------------------------------*/
void UpnpPassivePcm::NotifyError(const string& message,
                                 const string& object_id) {}

/*----------------------------------------------------------------------
 |   UPnPPassivePCM::StartCommunicationService
 +---------------------------------------------------------------------*/
int UpnpPassivePcm::StartCommunicationService() {}

/*----------------------------------------------------------------------
 |   UPnPPassivePCM::StopCommunicationService
 +---------------------------------------------------------------------*/
int UpnpPassivePcm::StopCommunicationService() {}

/*----------------------------------------------------------------------
 |   UPnPPassivePCM::StopCommunicationService
 +---------------------------------------------------------------------*/
bool UpnpPassivePcm::IsCommunicationServiceStarted() {}
