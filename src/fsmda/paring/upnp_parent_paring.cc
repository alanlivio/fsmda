/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paring/upnp_parent_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "NptResults.h"
#include "NptStrings.h"
#include "NptTypes.h"
#include "PltAction.h"
#include "PltHttp.h"
#include "PltService.h"
#include "PltStateVariable.h"
#include <iostream>
#include <string>

using std::clog;
using std::endl;

/*----------------------------------------------------------------------
 |   UpnpParentParing::UpnpParentParing
 +---------------------------------------------------------------------*/
UpnpParentParing::UpnpParentParing(const char* UUID)
    : PLT_DeviceHost("/", UUID, UpnpFsmdaUtils::kPpmDeviceType,
                     UpnpFsmdaUtils::kPpmDeviceFriendlyName),
      upnp_device_service_(NULL),
      upnp_reference_(NULL) {
  this->m_ModelDescription = UpnpFsmdaUtils::kPpmDeviceModelDescription;
  this->m_ModelURL = UpnpFsmdaUtils::kPpmDeviceModelUrl;
  this->m_ModelNumber = UpnpFsmdaUtils::kPpmDeviceNumber;
  this->m_ModelName = UpnpFsmdaUtils::kPpmDeviceModelName;
  this->m_Manufacturer = UpnpFsmdaUtils::kFsmdaManufacturer;
  this->m_ManufacturerURL = UpnpFsmdaUtils::kFsmdaManufacturerUrl;
  this->device_reference_ = new PLT_DeviceHostReference(this);
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::~UpnpParentParing
 +---------------------------------------------------------------------*/
UpnpParentParing::~UpnpParentParing() {
  this->StopService();
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpParentParing::SetupServices() {
  NPT_Result res;
  upnp_device_service_ = new PLT_Service(this, UpnpFsmdaUtils::kPpmServiceType,
                                         UpnpFsmdaUtils::kPpmServiceId,
                                         UpnpFsmdaUtils::kPpmServiceName);
  res = upnp_device_service_->SetSCPDXML(
      (const char*) UpnpFsmdaUtils::kPpmServiceScpdXml);
  res = AddService(upnp_device_service_);
  return res;
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpParentParing::OnAction(PLT_ActionReference& action,
                                      const PLT_HttpRequestContext& context) {
  NPT_String name = action->GetActionDesc().GetName();
  if (name.Compare("addDeviceToClass") == 0) {
    NPT_String applicationId;
    action->GetArgumentValue("applicationId", applicationId);
    NPT_String deviceAddr;
    action->GetArgumentValue("deviceAddr", deviceAddr);
    NPT_Int32 classIndex;
    action->GetArgumentValue("classIndex", classIndex);
    NPT_String deviceDesc;
    action->GetArgumentValue("deviceDesc", deviceDesc);
    clog << "--->UpnpParentParing::OnAction receive addDeviceToClass("
         << applicationId.GetChars() << "," << deviceAddr.GetChars() << ","
         << classIndex << "," << deviceDesc.GetChars() << ")" << endl;
    return NPT_SUCCESS;
  } else if (name.Compare("getChildIndex") == 0) {
    NPT_String applicationId;
    action->GetArgumentValue("applicationId", applicationId);
    NPT_String deviceAddr;
    action->GetArgumentValue("deviceAddr", deviceAddr);
    NPT_Int32 classIndex;
    action->GetArgumentValue("classIndex", classIndex);
    clog << "--->UpnpParentParing::OnAction receive getChildIndex("
         << applicationId.GetChars() << "," << deviceAddr.GetChars() << ","
         << classIndex << ")" << endl;
    action->SetArgumentValue("ret", "100");
    return NPT_SUCCESS;
  }
  action->SetError(501, "Action Failed");
  return NPT_FAILURE;
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::StartService
 +---------------------------------------------------------------------*/
int UpnpParentParing::StartService() {
  if (upnp_device_service_ != NULL && upnp_device_service_->IsValid()) {
    return 0;
  }
  if (upnp_reference_ == NULL) {
    upnp_reference_ = UpnpFsmdaUtils::RequestUpnpReference();
  }
  clog << "UpnpParentParing::start_service" << endl;
  NPT_Result res = upnp_reference_->AddDevice(*device_reference_);
  if (res != NPT_SUCCESS) {
    return -1;
  } else {
    return 0;
  }
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::StopService
 +---------------------------------------------------------------------*/
int UpnpParentParing::StopService() {
  if (upnp_reference_ != NULL) {
    upnp_reference_->RemoveDevice(*device_reference_);
    UpnpFsmdaUtils::ReleaseUpnpReference();
    upnp_reference_ = NULL;
  }
  return 0;
}
/*----------------------------------------------------------------------
 |   UpnpParentParing::IsServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpParentParing::IsServiceStarted() {
  return upnp_device_service_->IsValid();
}
