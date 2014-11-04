/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/paringmanager/upnp/upnp_child_paring.h"
#include "fsmda/paringmanager/upnp/upnp_parent_paring.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "NptResults.h"
#include "NptStrings.h"
#include "NptTypes.h"
#include "PltService.h"
#include <iostream>
#include <string>

/*----------------------------------------------------------------------
 |   UpnpParentParing::UpnpParentParing
 +---------------------------------------------------------------------*/
UpnpParentParing::UpnpParentParing (const char* UUID) :
    PLT_DeviceHost ("/", UUID, UpnpFsmdaUtils::UPNP_FSMDA_PPM_DEVICE_TYPE,
		    UpnpFsmdaUtils::UPNP_FSMDA_PPM_FRIENDLY_NAME), service_start_ (
	false), upnp_reference_ (NULL)

{
  this->m_ModelDescription = UpnpFsmdaUtils::UPNP_FSMDA_PPM_MODEL_DESCRIPTION;
  this->m_ModelURL = UpnpFsmdaUtils::UPNP_FSMDA_PPM_MODEL_URL;
  this->m_ModelNumber = UpnpFsmdaUtils::UPNP_FSMDA_PPM_MODEL_NUMBER;
  this->m_ModelName = UpnpFsmdaUtils::UPNP_FSMDA_PPM_MODEL_NAME;
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
  PLT_Service* service = new PLT_Service (this,
					  "urn:schemas-upnp-org:service:Test:1",
					  "urn:upnp-org:serviceId:Test.001",
					  "Test");

  res = service->SetSCPDXML (
      (const char*) UpnpFsmdaUtils::PARENT_PARING_MANAGER_SCPDXML);
  res = AddService (service);

  service->SetStateVariable ("Status", "True");

  return NPT_SUCCESS;
}

int
UpnpParentParing::start_service ()
{
  if (upnp_reference_ == NULL)
    upnp_reference_ = UpnpFsmdaUtils::requestUpnpReference ();
  clog << "OnDemandCCM::start_service" << endl;
  PLT_DeviceHostReference device_reference (this);
  upnp_reference_->AddDevice (device_reference);
  service_start_ = true;
  return 0;
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
