/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paringmanager/upnp/upnp_child_paring.h"
#include "fsmda/paringmanager/upnp/upnp_parent_paring.h"
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

/*----------------------------------------------------------------------
 |   UpnpParentParing::UpnpParentParing
 +---------------------------------------------------------------------*/
UpnpParentParing::UpnpParentParing (const char* UUID) :
    PLT_DeviceHost ("/", UUID, UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_TYPE,
		    UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_FRIENDLY_NAME), service_start_ (
	false), upnp_reference_ (NULL)

{
  this->m_ModelDescription =
      UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_MODEL_DESCRIPTION;
  this->m_ModelURL = UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_MODEL_URL;
  this->m_ModelNumber = UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_MODEL_NUMBER;
  this->m_ModelName = UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_MODEL_NAME;
  this->m_Manufacturer = UpnpFsmdaUtils::UPNP_FSMDA_MANUFACTURER;
  this->m_ManufacturerURL = UpnpFsmdaUtils::UPNP_FSMDA_MANUFACTURER_URL;
  this->upnp_reference_ = UpnpFsmdaUtils::requestUpnpReference ();
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::~UpnpParentParing
 +---------------------------------------------------------------------*/
UpnpParentParing::~UpnpParentParing ()
{
  if (this->upnp_reference_ != NULL)
    UpnpFsmdaUtils::releaseUpnpReference ();
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::SetupServices
 +---------------------------------------------------------------------*/
NPT_Result
UpnpParentParing::SetupServices ()
{
  NPT_Result res;
  PLT_Service* service = new PLT_Service (
      this, UpnpFsmdaUtils::UPNP_FSMDA_PPM_SERVICE_TYPE,
      UpnpFsmdaUtils::UPNP_FSMDA_PPM_SERVICE_ID,
      UpnpFsmdaUtils::UPNP_FSMDA_PPM_SERVICE_NAME);
  res = service->SetSCPDXML (
      (const char*) UpnpFsmdaUtils::UPNP_FSMDA_PPM_SERVICE_SCPDXML);
  res = AddService (service);
  return res;
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::OnAction
 +---------------------------------------------------------------------*/
NPT_Result
UpnpParentParing::OnAction (PLT_ActionReference& action,
			    const PLT_HttpRequestContext& context)
{
  NPT_String name = action->GetActionDesc ().GetName ();
  if (name.Compare ("addDeviceToClass") == 0)
    {
      NPT_String applicationId;
      action->GetArgumentValue ("applicationId", applicationId);
      NPT_String deviceAddr;
      action->GetArgumentValue ("deviceAddr", deviceAddr);
      NPT_Int32 classIndex;
      action->GetArgumentValue ("classIndex", classIndex);
      NPT_String deviceDesc;
      action->GetArgumentValue ("deviceDesc", deviceDesc);
      clog << "--->UpnpParentParing::OnAction receive addDeviceToClass("
	  << applicationId.GetChars () << "," << deviceAddr.GetChars () << ","
	  << classIndex << "," << deviceDesc.GetChars () << ")" << endl;
      return NPT_SUCCESS;
    }
  else if (name.Compare ("getChildIndex") == 0)
    {
      NPT_String applicationId;
      action->GetArgumentValue ("applicationId", applicationId);
      NPT_String deviceAddr;
      action->GetArgumentValue ("deviceAddr", deviceAddr);
      NPT_Int32 classIndex;
      action->GetArgumentValue ("classIndex", classIndex);
      clog << "--->UpnpParentParing::OnAction receive getChildIndex("
	  << applicationId.GetChars () << "," << deviceAddr.GetChars () << ","
	  << classIndex << ")" << endl;
      action->SetArgumentValue ("ret", "100");
      return NPT_SUCCESS;
    }
  action->SetError (501, "Action Failed");
  return NPT_FAILURE;
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::start_service
 +---------------------------------------------------------------------*/
int
UpnpParentParing::start_service ()
{
  if (service_start_)
    return 0;
  if (upnp_reference_ == NULL)
    upnp_reference_ = UpnpFsmdaUtils::requestUpnpReference ();
  clog << "UpnpParentParing::start_service" << endl;
  PLT_DeviceHostReference device_reference (this);
  NPT_Result res = upnp_reference_->AddDevice (device_reference);
  if (res != NPT_SUCCESS)
    return -1;
  else
    {
      service_start_ = true;
      return 0;
    }
}

/*----------------------------------------------------------------------
 |   UpnpParentParing::stop_service
 +---------------------------------------------------------------------*/
int
UpnpParentParing::stop_service ()
{
  if (upnp_reference_ != NULL)
    UpnpFsmdaUtils::releaseUpnpReference ();
  upnp_reference_ = NULL;
  service_start_ = false;
  return 0;
}
/*----------------------------------------------------------------------
 |   UpnpParentParing::is_service_started
 +---------------------------------------------------------------------*/
bool
UpnpParentParing::is_service_started ()
{
  return service_start_;
}
