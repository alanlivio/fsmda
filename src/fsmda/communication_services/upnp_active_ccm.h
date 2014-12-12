#ifndef FSMDA_COMMUNICATION_SERVICES_UPNP_ACTIVE_CCM_H_
#define FSMDA_COMMUNICATION_SERVICES_UPNP_ACTIVE_CCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include <vector>
#include "fsmda/model/active_object_interfaces.h"

using std::string;
using std::vector;

/*----------------------------------------------------------------------
 |   UpnpActiveCcm class
 +---------------------------------------------------------------------*/
class UpnpActiveCcm : public ActiveCcmInterface {
 public:
  // public constructors & destructors
  UpnpActiveCcm();
  virtual ~UpnpActiveCcm();

  // ActiveCcmInterface overloaded methods
  virtual void Prepare(const string& object_id, const string& object_src,
                       vector<Property> properties, vector<Event> evts);
  virtual void AddEvent(const string& object_id, Event evt);
  virtual void RemoveEvent(const string& object_id, const string& event_id);
  virtual void PostAction(const string& object_id, const string& event_id,
                          const string& action);
  virtual void ReportPropertyValue(const string& object_id, const string& name,
                                   const string& value);
  virtual void SetPropertyValue(const string& object_id, const string& name,
                                const string& value, unsigned int duration);
};

#endif  // FSMDA_COMMUNICATION_SERVICES_UPNP_ACTIVE_CCM_H_