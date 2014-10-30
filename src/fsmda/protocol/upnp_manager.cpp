/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <fsmda/protocol/upnp_manager.h>
#include <NptList.h>
#include <NptLogging.h>
#include <NptNetwork.h>
#include <NptStrings.h>
#include <NptTime.h>
#include <PltConstants.h>
#include <PltDeviceHost.h>
#include <PltFileMediaServer.h>
#include <PltUtilities.h>

/*----------------------------------------------------------------------
 |   class fields
 +---------------------------------------------------------------------*/
UPnPManager* UPnPManager::singleton = NULL;

const char* UPnPManager::UPNP_FSMDA_ONDEMAND_CLASS_MODEL_NAME =
    "fsmda-ondemand-device";
const char* UPnPManager::UPNP_FSMDA_ONDEMAND_CLASS_FRIENDLY_NAME =
    "FSMDA OndDemand device";
const char* UPnPManager::UPNP_FSMDA_ONDEMAND_CLASS_MODEL_DESCRIPTION =
    "FSMDA OndDemand device description";
const char* UPnPManager::UPNP_FSMDA_ONDEMAND_CLASS_MODEL_URL =
    "http://www.ncl.org.br/fsmda/ondemand";
const char* UPnPManager::UPNP_FSMDA_ONDEMAND_CLASS_MODEL_NUMBER = "1.0";
const char* UPnPManager::UPNP_FSMDA_MANUFACTURER = "FSMDA";
const char* UPnPManager::UPNP_FSMDA_MANUFACTURER_URL =
    "http://www.ncl.org.br/fsmda/ondemand";

/*----------------------------------------------------------------------
 |   UPnPManager::UPnPManager
 +---------------------------------------------------------------------*/
UPnPManager::UPnPManager () :
    intialized_platinumkit_ (false)
{

}

/*----------------------------------------------------------------------
 |   UPnPManager::~UPnPManager
 +---------------------------------------------------------------------*/
UPnPManager::~UPnPManager ()
{
}

/*----------------------------------------------------------------------
 |   UPnPManager::offerOnDemandDeviceClassContent
 +---------------------------------------------------------------------*/
int
UPnPManager::offerOnDemandDeviceClassContent (const string& uuid,
					      const string& folder)
{
  if (!this->intialized_platinumkit_)
    this->initialize_platinumkit ();

  //Create UPnP server if not exist
  if (upnp_map_.find (uuid) == upnp_map_.end ())
    {
      PLT_UPnP upnp;
      PLT_DeviceHostReference device (
	  new PLT_FileMediaServer (folder.c_str (),
				   UPNP_FSMDA_ONDEMAND_CLASS_FRIENDLY_NAME,
				   true, uuid.c_str ()));
      device->m_ModelDescription = UPNP_FSMDA_ONDEMAND_CLASS_MODEL_DESCRIPTION;
      device->m_ModelURL = UPNP_FSMDA_ONDEMAND_CLASS_MODEL_URL;
      device->m_ModelNumber = UPNP_FSMDA_ONDEMAND_CLASS_MODEL_NUMBER;
      device->m_ModelName = UPNP_FSMDA_ONDEMAND_CLASS_MODEL_NAME;
      device->m_Manufacturer = UPNP_FSMDA_MANUFACTURER;
      device->m_ManufacturerURL = UPNP_FSMDA_MANUFACTURER_URL;
      upnp.AddDevice (device);
      upnp_map_[uuid] = upnp;
    }

  //Start FileMediaServer
  upnp_map_[uuid].Start ();
  return 0;
}

/*----------------------------------------------------------------------
 |   UPnPManager::removeOfferOnDemandDeviceClassContent
 +---------------------------------------------------------------------*/
int
UPnPManager::removeOfferOnDemandDeviceClassContent (const string& uuid,
						    const string& folder)
{
  upnp_map_[uuid].Stop ();
  return 0;
}

/*----------------------------------------------------------------------
 |   UPnPManager::initialize_platinumkit
 +---------------------------------------------------------------------*/
void
UPnPManager::initialize_platinumkit ()
{
  // setup Neptune logging
  NPT_LogManager::GetDefault ().Configure (
      "plist:.level=FINE;.handlers=ConsoleHandler;.ConsoleHandler.colors=off;.ConsoleHandler.filter=42");

  // for faster DLNA faster testing
  PLT_Constants::GetInstance ().SetDefaultDeviceLease (NPT_TimeInterval (60.));

  NPT_List<NPT_IpAddress> list;
  PLT_UPnPMessageHelper::GetIPAddresses (list);

  this->intialized_platinumkit_ = true;
}

/*----------------------------------------------------------------------
 |   UPnPManager::initialize_platinumkit
 +---------------------------------------------------------------------*/
UPnPManager*
UPnPManager::getInstance ()
{
  if (UPnPManager::singleton == NULL)
    UPnPManager::singleton = new UPnPManager;
  return UPnPManager::singleton;
}
