/*----------------------------------------------------------------------
 |   include
 +---------------------------------------------------------------------*/

#include "fsmda/communicationmanager/upnp/upnp_ondemand_ccm.h"
#include "fsmda/utils/upnp_fsmda_utils.h"
#include "NptStrings.h"
#include "PltDeviceHost.h"
#include "PltFileMediaServer.h"
#include <iostream>
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   class fields
 +---------------------------------------------------------------------*/
const char* UpnpOnDemandCcm::UPNP_FSMDA_ONDEMAND_CLASS_MODEL_NAME =
    "fsmda-ondemand-device";
const char* UpnpOnDemandCcm::UPNP_FSMDA_ONDEMAND_CLASS_FRIENDLY_NAME =
    "FSMDA OndDemand device";
const char* UpnpOnDemandCcm::UPNP_FSMDA_ONDEMAND_CLASS_MODEL_DESCRIPTION =
    "FSMDA OndDemand device description";
const char* UpnpOnDemandCcm::UPNP_FSMDA_ONDEMAND_CLASS_MODEL_URL =
    "http://www.ncl.org.br/fsmda/ondemand";
const char* UpnpOnDemandCcm::UPNP_FSMDA_ONDEMAND_CLASS_MODEL_NUMBER = "1.0";
const char* UpnpOnDemandCcm::UPNP_FSMDA_MANUFACTURER = "FSMDA";
const char* UpnpOnDemandCcm::UPNP_FSMDA_MANUFACTURER_URL =
    "http://www.ncl.org.br/fsmda/ondemand";

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::UpnpOnDemandCcm
 +---------------------------------------------------------------------*/
UpnpOnDemandCcm::UpnpOnDemandCcm () :
    ondemand_folder_ ("/tmp/fsmda/ondemand/"), uuid_ ("fsmda-0000"), service_start_ (
	false), upnp_reference_ (NULL)
{
}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::~UpnpOnDemandCcm
 +---------------------------------------------------------------------*/
UpnpOnDemandCcm::~UpnpOnDemandCcm ()
{
  if (upnp_reference_ != NULL)
    upnp_reference_ = UpnpFsmdaUtils::requestUpnpReference ();
}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::start_communication_service
 +---------------------------------------------------------------------*/
int
UpnpOnDemandCcm::start_communication_service ()
{
  if (upnp_reference_ == NULL)
    upnp_reference_ = UpnpFsmdaUtils::requestUpnpReference ();

  clog << "OnDemandCCM::start_communication_service" << endl;
  PLT_DeviceHostReference device (
      new PLT_FileMediaServer (this->ondemand_folder_.c_str (),
			       UPNP_FSMDA_ONDEMAND_CLASS_FRIENDLY_NAME, true,
			       this->uuid_.c_str ()));
  device->m_ModelDescription = UPNP_FSMDA_ONDEMAND_CLASS_MODEL_DESCRIPTION;
  device->m_ModelURL = UPNP_FSMDA_ONDEMAND_CLASS_MODEL_URL;
  device->m_ModelNumber = UPNP_FSMDA_ONDEMAND_CLASS_MODEL_NUMBER;
  device->m_ModelName = UPNP_FSMDA_ONDEMAND_CLASS_MODEL_NAME;
  device->m_Manufacturer = UPNP_FSMDA_MANUFACTURER;
  device->m_ManufacturerURL = UPNP_FSMDA_MANUFACTURER_URL;
  upnp_reference_->AddDevice (device);
  service_start_ = true;
  return 0;
}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::stop_communication_service
 +---------------------------------------------------------------------*/
int
UpnpOnDemandCcm::stop_communication_service ()
{
  UpnpFsmdaUtils::releaseUpnpReference ();
  upnp_reference_ = NULL;
  service_start_ = false;
  return 0;
}
/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::is_service_started
 +---------------------------------------------------------------------*/
bool
UpnpOnDemandCcm::is_service_started ()
{
  return service_start_;
}
