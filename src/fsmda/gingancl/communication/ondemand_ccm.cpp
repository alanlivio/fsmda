/*----------------------------------------------------------------------
 |   include
 +---------------------------------------------------------------------*/

#include <fsmda/gingancl/communication/ondemand_ccm.h>
#include <fsmda/protocol/upnp_manager.h>
#include <iostream>

using namespace std;

/*----------------------------------------------------------------------
 |   OnDemandCCM::OnDemandCCM
 +---------------------------------------------------------------------*/
OnDemandCCM::OnDemandCCM () :
    default_folder_ ("/tmp/fsmda/ondemand/"), default_uui_ ("fsmda-0000"), service_start_ (
	false)
{

}

/*----------------------------------------------------------------------
 |   OnDemandCCM::~OnDemandCCM
 +---------------------------------------------------------------------*/
OnDemandCCM::~OnDemandCCM ()
{
}

/*----------------------------------------------------------------------
 |   OnDemandCCM::~OnDemandCCM
 +---------------------------------------------------------------------*/
int
OnDemandCCM::start_communication_service ()
{
  clog << "OnDemandCCM::start_communication_service" << endl;
  UPnPManager::getInstance ()->offerOnDemandContent (this->default_uui_,
						     this->default_folder_);
  service_start_ = true;
  return 0;
}

/*----------------------------------------------------------------------
 |   OnDemandCCM::~OnDemandCCM
 +---------------------------------------------------------------------*/
int
OnDemandCCM::stop_communication_service ()
{
  UPnPManager::getInstance ()->removeOfferOnDemandDeviceClassContent (
      this->default_uui_, this->default_folder_);
  service_start_ = false;
  return 0;
}
/*----------------------------------------------------------------------
 |   OnDemandCCM::is_service_started
 +---------------------------------------------------------------------*/
bool
OnDemandCCM::is_service_started ()
{
  return service_start_;
}
