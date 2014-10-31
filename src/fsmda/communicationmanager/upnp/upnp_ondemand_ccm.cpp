/*----------------------------------------------------------------------
 |   include
 +---------------------------------------------------------------------*/

#include "fsmda/communicationmanager/upnp/upnp_manager.h"
#include "fsmda/communicationmanager/upnp/upnp_ondemand_ccm.h"
#include <iostream>

using namespace std;

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::UpnpOnDemandCcm
 +---------------------------------------------------------------------*/
UpnpOnDemandCcm::UpnpOnDemandCcm () :
    default_folder_ ("/tmp/fsmda/ondemand/"), default_uui_ ("fsmda-0000"), service_start_ (
	false)
{

}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::~UpnpOnDemandCcm
 +---------------------------------------------------------------------*/
UpnpOnDemandCcm::~UpnpOnDemandCcm ()
{
}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::start_communication_service
 +---------------------------------------------------------------------*/
int
UpnpOnDemandCcm::start_communication_service ()
{
  clog << "OnDemandCCM::start_communication_service" << endl;
  UpnpManager::getInstance ()->offerOnDemandContent (this->default_uui_,
						     this->default_folder_);
  service_start_ = true;
  return 0;
}

/*----------------------------------------------------------------------
 |   UpnpOnDemandCcm::stop_communication_service
 +---------------------------------------------------------------------*/
int
UpnpOnDemandCcm::stop_communication_service ()
{
  UpnpManager::getInstance ()->removeOfferOnDemandDeviceClassContent (
      this->default_uui_, this->default_folder_);
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
