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
UpnpParentParing::UpnpParentParing()
    : PLT_DeviceHost("/", NULL, UpnpFsmdaUtils::kPpmDeviceType,
                     UpnpFsmdaUtils::kPpmDeviceFriendlyName, true, 4444, true),
      device_service_(NULL),
      upnp_instance_(NULL),
      paired_childs_(0) {
  m_ModelDescription = UpnpFsmdaUtils::kPpmDeviceModelDescription;
  m_ModelURL = UpnpFsmdaUtils::kPpmDeviceModelUrl;
  m_ModelNumber = UpnpFsmdaUtils::kPpmDeviceNumber;
  m_ModelName = UpnpFsmdaUtils::kPpmDeviceModelName;
  m_Manufacturer = UpnpFsmdaUtils::kFsmdaManufacturer;
  m_ManufacturerURL = UpnpFsmdaUtils::kFsmdaManufacturerUrl;
  device_host_ = new PLT_DeviceHostReference(this);
  device_service_ = new PLT_Service(this, UpnpFsmdaUtils::kPpmServiceType,
                                    UpnpFsmdaUtils::kPpmServiceId,
                                    UpnpFsmdaUtils::kPpmServiceName);
  device_service_->SetSCPDXML((const char *)UpnpFsmdaUtils::kPpmServiceScpdXml);
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::~UpnpParentParing
 +---------------------------------------------------------------------*/
UpnpParentParing::~UpnpParentParing() {
  this->StopService();
  delete device_service_;
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result UpnpParentParing::SetupServices() {
  clog << "UpnpParentParing::SetupServices()" << endl;
  NPT_Result res;
  res = AddService(device_service_);
  return res;
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::OnAction
 +---------------------------------------------------------------------*/
NPT_Result UpnpParentParing::OnAction(PLT_ActionReference &action,
                                      const PLT_HttpRequestContext &context) {
  clog << "UpnpParentParing::OnAction()" << endl;
  NPT_String name = action->GetActionDesc().GetName();

  if (name.Compare("addDeviceToClass") == 0) {
    // handling addDeviceToClass call
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
    // handling getChildIndex call
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

NPT_Result UpnpParentParing::OnEventNotify(
    PLT_Service *service, NPT_List<PLT_StateVariable *> *vars) {}

NPT_Result UpnpParentParing::OnActionResponse(NPT_Result res,
                                              PLT_ActionReference &action,
                                              void *userdata) {}
NPT_Result UpnpParentParing::OnDeviceRemoved(PLT_DeviceDataReference &device) {}

NPT_Result UpnpParentParing::OnDeviceAdded(PLT_DeviceDataReference &device) {}

/*----------------------------------------------------------------------
 |   UpnpParentParing::StartService
 +---------------------------------------------------------------------*/
int UpnpParentParing::StartService() {
  clog << "UpnpParentParing::StartService" << endl;
  if (upnp_instance_ == NULL) {
    upnp_instance_ = UpnpFsmdaUtils::GetRunningUpnpInstance();
  }
  NPT_Result res = upnp_instance_->AddDevice(*device_host_);
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
  if (upnp_instance_ != NULL) {
    RemoveService(device_service_);
    upnp_instance_->RemoveDevice(*device_host_);
    UpnpFsmdaUtils::ReleaseUpnpInstance();
    upnp_instance_ = NULL;
  }
  return 0;
}
/*----------------------------------------------------------------------
 |   UpnpParentParing::IsServiceStarted
 +---------------------------------------------------------------------*/
bool UpnpParentParing::IsServiceStarted() { return m_Started; }
