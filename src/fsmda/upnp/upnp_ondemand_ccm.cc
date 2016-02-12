

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

UpnpOnDemandCcm::UpnpOnDemandCcm()
    : ondemand_folder_("/tmp/fsmda/ondemand/"),
      uuid_("fsmda-0000"),
      service_start_(false),
      upnp_reference_(NULL) {}

UpnpOnDemandCcm::~UpnpOnDemandCcm() {}

void UpnpOnDemandCcm::NotifyError(const string& message,
                                  const string& object_id) {}

int UpnpOnDemandCcm::StartCommunicationService() { return 0; }

int UpnpOnDemandCcm::StopCommunicationService() { return 0; }

bool UpnpOnDemandCcm::IsCommunicationServiceStarted() { return service_start_; }

NPT_Result UpnpOnDemandCcm::SetupServices() {}

NPT_Result UpnpOnDemandCcm::OnAction(PLT_ActionReference& action,
                                     const PLT_HttpRequestContext& context) {}

NPT_Result UpnpOnDemandCcm::OnDeviceAdded(PLT_DeviceDataReference& device) {}

NPT_Result UpnpOnDemandCcm::OnDeviceRemoved(PLT_DeviceDataReference& device) {}

NPT_Result UpnpOnDemandCcm::OnActionResponse(NPT_Result res,
                                             PLT_ActionReference& action,
                                             void* userdata) {}

NPT_Result UpnpOnDemandCcm::OnEventNotify(PLT_Service* service,
                                          NPT_List<PLT_StateVariable*>* vars) {}
