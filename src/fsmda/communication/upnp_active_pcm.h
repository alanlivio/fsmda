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
  virtual ~UpnpActivePcm();

  // ActivePcmInterface overloaded methods
  virtual void RequestPropertyValue(const string& object_id,
                                    const string& name);
  virtual void NotifyEventTransition(const string& object_id,
                                     const string& event_id,
                                     const string& transition);
  virtual void NotifyError(const string& object_id, const string& message);
};

#endif  // FSMDA_COMMUNICATION_UPNP_ACTIVE_PCM_H_