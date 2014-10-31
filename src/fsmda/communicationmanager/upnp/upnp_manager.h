#ifndef FSMDA_PROTOCOL_UPNP_H_
#define FSMDA_PROTOCOL_UPNP_H_

/*----------------------------------------------------------------------
 |   include
 +---------------------------------------------------------------------*/

#include "PltUPnP.h"
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
  static UPnPManager*
  getInstance ();

  static void
  releaseInstance ();

  // public methods
  int
  offerOnDemandContent (const string& uuid, const string& folder);
  int
  removeOfferOnDemandDeviceClassContent (const string& uuid,
					 const string& folder);
private:
  // class fields and methods
  static UPnPManager* singleton;
  // private constructors & destructors
  UPnPManager ();
  virtual
  ~UPnPManager ();

  // private fields
  map<string, PLT_UPnP> upnp_map_;
  bool platinumkit_intialized_;
  PLT_UPnP * upnp_service_;

  // private methods
  void
  initialize_platinumkit ();
  void
  release_platinumkit ();

};

#endif /* FSMDA_SERVICES_UPNP_SERVICE_H_ */
