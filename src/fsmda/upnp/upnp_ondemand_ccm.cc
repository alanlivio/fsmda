/*----------------------------------------------------------------------
 |   include
 +---------------------------------------------------------------------*/

#include "fsmda/upnp/upnp_ondemand_ccm.h"
#include "fsmda/upnp/upnp_fsmda_utils.h"
#include "NptStrings.h"
#include "PltDeviceHost.h"
#include "PltFileMediaServer.h"
#include "PltUPnP.h"
#include <iostream>
#include <string>

using std::clog;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::UpnpOnDemandCcm
 +---------------------------------------------------------------------*/
UpnpOnDemandCcm::UpnpOnDemandCcm()
    : ondemand_folder_("/tmp/fsmda/ondemand/"),
      uuid_("fsmda-0000"),
      service_start_(false),
      upnp_reference_(NULL) {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::~UpnpOnDemandCcm
 +---------------------------------------------------------------------*/
UpnpOnDemandCcm::~UpnpOnDemandCcm() {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::~NotifyError
 +---------------------------------------------------------------------*/
void UpnpOnDemandCcm::NotifyError(const string& message,
                                  const string& object_id) {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::Start
 +---------------------------------------------------------------------*/
int UpnpOnDemandCcm::StartCommunicationService() { return 0; }

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::Stop
 +---------------------------------------------------------------------*/
int UpnpOnDemandCcm::StopCommunicationService() { return 0; }
/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::IsCommunicationServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpOnDemandCcm::IsCommunicationServiceStarted() { return service_start_; }

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandCcm::SetupServices() {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandCcm::OnAction(PLT_ActionReference& action,
                                     const PLT_HttpRequestContext& context) {}
/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::OnDeviceAdded
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandCcm::OnDeviceAdded(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::OnDeviceRemoved
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandCcm::OnDeviceRemoved(PLT_DeviceDataReference& device) {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::OnActionResponse
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandCcm::OnActionResponse(NPT_Result res,
                                             PLT_ActionReference& action,
                                             void* userdata) {}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::OnEventNotify
 +---------------------------------------------------------------------*/
NPT_Result UpnpOnDemandCcm::OnEventNotify(PLT_Service* service,
                                          NPT_List<PLT_StateVariable*>* vars) {}
