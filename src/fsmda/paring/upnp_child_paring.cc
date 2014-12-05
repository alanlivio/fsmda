/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paring/upnp_child_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "NptConfig.h"
#include "NptResults.h"
#include "NptStrings.h"
#include "PltFileMediaServer.h"
#include "PltService.h"
#include "PltStateVariable.h"
#include <iostream>
#include <string>

using std::clog;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpChildParing::UpnpChildParing
 +---------------------------------------------------------------------*/
UpnpChildParing::UpnpChildParing(const char* UUID)
    : PLT_DeviceHost("/", UUID, UpnpFsmdaUtils::kPpmDeviceType,
                     UpnpFsmdaUtils::kCpmDeviceFriendlyName),
      upnp_device_service_(NULL),
      upnp_reference_(NULL) {
  this->m_ModelDescription = UpnpFsmdaUtils::kCpmDeviceModelDescription;
  this->m_ModelURL = UpnpFsmdaUtils::kCpmDeviceModelUrl;
  this->m_ModelNumber = UpnpFsmdaUtils::kCpmDeviceModelNumber;
  this->m_ModelName = UpnpFsmdaUtils::kCpmDeviceModelName;
  this->m_Manufacturer = UpnpFsmdaUtils::kFsmdaManufacturer;
  this->m_ManufacturerURL = UpnpFsmdaUtils::kFsmdaManufacturerUrl;
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
  upnp_device_service_ = new PLT_Service(this, UpnpFsmdaUtils::kCpmServiceType,
                                         UpnpFsmdaUtils::kCpmServiceId,
                                         UpnpFsmdaUtils::kCpmServiceName);
  res = upnp_device_service_->SetSCPDXML(
      (const char*) UpnpFsmdaUtils::kCpmServiceScpdXml);
  res = AddService(upnp_device_service_);
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
  if (upnp_device_service_ != NULL && upnp_device_service_->IsValid()) {
    return 0;
  }
  if (upnp_reference_ == NULL)
    upnp_reference_ = UpnpFsmdaUtils::requestUpnpReference();
  clog << "UpnpParentParing::start_service" << endl;
  PLT_DeviceHostReference device_reference(this);
  NPT_Result res = upnp_reference_->AddDevice(device_reference);
  if (res != NPT_SUCCESS) {
    return -1;
  } else {
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
  return 0;
}
/*----------------------------------------------------------------------
 |   UpnpChildParing::is_service_started
 +---------------------------------------------------------------------*/
bool UpnpChildParing::is_service_started() {
  return upnp_device_service_->IsValid();
}

