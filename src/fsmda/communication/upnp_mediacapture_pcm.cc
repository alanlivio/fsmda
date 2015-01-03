/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication/upnp_mediacapture_pcm.h"

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::UpnpMediaCapturePcm
 +---------------------------------------------------------------------*/
UpnpMediaCapturePcm::UpnpMediaCapturePcm() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::~UpnpMediaCapturePcm
 +---------------------------------------------------------------------*/
UpnpMediaCapturePcm::~UpnpMediaCapturePcm() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::SendContent
 +---------------------------------------------------------------------*/
void UpnpMediaCapturePcm::SendContent(char* content, const string& resource_id,
                                      unsigned int child_index) {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::StartCommunicationService
 +---------------------------------------------------------------------*/
int UpnpMediaCapturePcm::StartCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::StopCommunicationService
 +---------------------------------------------------------------------*/
int UpnpMediaCapturePcm::StopCommunicationService() {}

/*----------------------------------------------------------------------
 |   UpnpMediaCapturePcm::IsCommunicationServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpMediaCapturePcm::IsCommunicationServiceStarted() {}
