#ifndef FSMDA_COMMUNICATION_UPNP_ACTIVE_PCM_H_
#define FSMDA_COMMUNICATION_UPNP_ACTIVE_PCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include "fsmda/communication/model/active_object_interfaces.h"
#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   UpnpActivePcm class
 +---------------------------------------------------------------------*/
class UpnpActivePcm : public ActivePcmInterface {
 public:
  // public constructors & destructors
  UpnpActivePcm();
  virtual
  ~UpnpActivePcm();

  // ActivePcmInterface overloaded methods
  virtual void
  requestPropertyValue(const string& objectID, const string& name);
  virtual void
  notifyEventTransition(const string& objectID, const string& eventID,
                        const string& transition);
  virtual void
  notifyError(const string& objectID, const string& message);
};

#endif  // FSMDA_COMMUNICATION_UPNP_ACTIVE_PCM_H_
