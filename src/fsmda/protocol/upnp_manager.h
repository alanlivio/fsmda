#ifndef FSMDA_PROTOCOL_UPNP_H_
#define FSMDA_PROTOCOL_UPNP_H_

/*----------------------------------------------------------------------
 |   include
 +---------------------------------------------------------------------*/

#include <PltUPnP.h>
#include <map>
#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   UPnPManager class
 +---------------------------------------------------------------------*/
class UPnPManager
{
public:
  // class fields and methods
  static const char* UPNP_FSMDA_ONDEMAND_CLASS_FRIENDLY_NAME;
  static const char* UPNP_FSMDA_ONDEMAND_CLASS_MODEL_DESCRIPTION;
  static const char* UPNP_FSMDA_ONDEMAND_CLASS_MODEL_URL;
  static const char* UPNP_FSMDA_ONDEMAND_CLASS_MODEL_NUMBER;
  static const char* UPNP_FSMDA_ONDEMAND_CLASS_MODEL_NAME;
  static const char* UPNP_FSMDA_MANUFACTURER;
  static const char* UPNP_FSMDA_MANUFACTURER_URL;
  static UPnPManager* getInstance();

  // public constructors & destructors

  virtual
  ~UPnPManager ();

  // public methods
  int
  offerOnDemandDeviceClassContent (const string& uuid, const string& folder);
  int
  removeOfferOnDemandDeviceClassContent (const string& uuid,
					 const string& folder);
private:
  // class fields and methods
  static UPnPManager* singleton;

  // private fields
  map<const string, PLT_UPnP> upnp_map_;
  bool intialized_platinumkit_;
  // private methods
  UPnPManager ();
  void
  initialize_platinumkit ();

};

#endif /* FSMDA_SERVICES_UPNP_SERVICE_H_ */
