/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paringmanager/upnp/upnp_child_paring.h"
#include "fsmda/paringmanager/upnp/upnp_parent_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "NptConfig.h"
#include "NptResults.h"
#include "NptStrings.h"
#include "PltFileMediaServer.h"
#include "PltService.h"
#include "PltStateVariable.h"
#include <iostream>
#include <string>

/*----------------------------------------------------------------------
 |   UpnpChildParing::UpnpChildParing
 +---------------------------------------------------------------------*/
UpnpChildParing::UpnpChildParing(const char* UUID)
    : PLT_DeviceHost("/", UUID, UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_TYPE,
                     UpnpFsmdaUtils::UPNP_FSMDA_CPM_DEVICE_FRIENDLY_NAME),
      service_start_(false),
      upnp_reference_(NULL) {
  this->m_ModelDescription =
      UpnpFsmdaUtils::UPNP_FSMDA_CPM_DEVICE_MODEL_DESCRIPTION;
  this->m_ModelURL = UpnpFsmdaUtils::UPNP_FSMDA_CPM_DEVICE_MODEL_URL;
  this->m_ModelNumber = UpnpFsmdaUtils::UPNP_FSMDA_CPM_DEVICE_MODEL_NUMBER;
  this->m_ModelName = UpnpFsmdaUtils::UPNP_FSMDA_CPM_DEVICE_MODEL_NAME;
  this->m_Manufacturer = UpnpFsmdaUtils::UPNP_FSMDA_MANUFACTURER;
  this->m_ManufacturerURL = UpnpFsmdaUtils::UPNP_FSMDA_MANUFACTURER_URL;
}

/*----------------------------------------------------------------------
 |   UpnpChildParing::~UpnpChildParing
 +---------------------------------------------------------------------*/
UpnpChildParing::~UpnpChildParing() {
}

/*----------------------------------------------------------------------
 |   UpnpChildParing::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpChildParing::SetupServices() {
  NPT_Result res;
  PLT_Service* service = new PLT_Service(
      this, UpnpFsmdaUtils::UPNP_FSMDA_CPM_SERVICE_TYPE,
      UpnpFsmdaUtils::UPNP_FSMDA_CPM_SERVICE_ID,
      UpnpFsmdaUtils::UPNP_FSMDA_CPM_SERVICE_NAME);
  res = service->SetSCPDXML(
      (const char*) UpnpFsmdaUtils::UPNP_FSMDA_CPM_SERVICE_SCPDXML);
  res = AddService(service);
  return res;
}

/*----------------------------------------------------------------------
 |   UpnpChildParing::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpChildParing::OnAction(PLT_ActionReference& action,
                                     const PLT_HttpRequestContext& context) {
  NPT_String name = action->GetActionDesc().GetName();
  if (name.Compare("classAnnouncement") == 0) {
    NPT_String applicationId;
    action->GetArgumentValue("applicationId", applicationId);
    NPT_Int32 classIndex;
    action->GetArgumentValue("classIndex", classIndex);
    NPT_String classDesc;
    action->GetArgumentValue("classDesc", classDesc);
    NPT_String classFunction;
    action->GetArgumentValue("classFunction", classFunction);
    clog << "--->UpnpChildParing::OnAction receive classAnnouncement("
         << applicationId.GetChars() << "," << classIndex << ","
         << classDesc.GetChars() << "," << classFunction.GetChars() << ")"
         << endl;
    return NPT_SUCCESS;
  }
  action->SetError(501, "Action Failed");
  return NPT_FAILURE;
}

/*----------------------------------------------------------------------
 |   UpnpChildParing::start_service
 +---------------------------------------------------------------------*/
int UpnpChildParing::start_service() {
  if (service_start_)
    return 0;
  if (upnp_reference_ == NULL)
    upnp_reference_ = UpnpFsmdaUtils::requestUpnpReference();
  clog << "UpnpParentParing::start_service" << endl;
  PLT_DeviceHostReference device_reference(this);
  NPT_Result res = upnp_reference_->AddDevice(device_reference);
  if (res != NPT_SUCCESS)
    return -1;
  else {
    service_start_ = true;
    return 0;
  }
}

/*----------------------------------------------------------------------
 |   UpnpChildParing::stop_service
 +---------------------------------------------------------------------*/
int UpnpChildParing::stop_service() {
  if (upnp_reference_ != NULL)
    UpnpFsmdaUtils::releaseUpnpReference();
  upnp_reference_ = NULL;
  service_start_ = false;
  return 0;
}
/*----------------------------------------------------------------------
 |   UpnpChildParing::is_service_started
 +---------------------------------------------------------------------*/
bool UpnpChildParing::is_service_started() {
  return service_start_;
}

