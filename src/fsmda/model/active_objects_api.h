#ifndef FSMDA_MODEL_ACTIVE_OBJECTS_API_H_
#define FSMDA_MODEL_ACTIVE_OBJECTS_API_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include <vector>

using std::string;
using std::vector;

/*----------------------------------------------------------------------
 |   Property class
 +---------------------------------------------------------------------*/
class Property {
 public:
  string property_name_;
  string property_value_;
  const string ToString() { return property_name_ + "=" + property_value_; }
  static const string ToString(vector<Property> properties) {
    string res = "{";
    for (int i = 0; i < properties.size(); i++)
      res + properties[i].ToString() + ",";
    res += "}";
    return res;
  }
};

/*----------------------------------------------------------------------
 |   Event class
 +---------------------------------------------------------------------*/
class Event {
 public:
  string event_id_;
  string event_type_;
  string event_desc_;
  const string ToString() {
    return event_id_ + "," + event_type_ + "," + event_desc_;
  }
  static const string ToString(vector<Event> events) {
    string res = "{";
    for (int i = 0; i < events.size(); i++) res + events[i].ToString() + ",";
    res += "}";
    return res;
  }
};

/*----------------------------------------------------------------------
 |   ActivePlayerInterface and ActivePlayerListenerInterface interfaces.
 |   It is use between Active Child Communication Manager
 |   and RemotePlayer
 +---------------------------------------------------------------------*/
class ActivePlayerListenerInterface {
 public:
  // public constructors & destructors
  virtual ~ActivePlayerListenerInterface() {}

  // public pure virtual methods
  virtual void ReportPropertyValue(const string& name, const string& value) = 0;
  virtual void NotifyEventTransition(const string& event_id,
                                     const string& transition) = 0;
  virtual void NotifyError(const string& message) = 0;
};

class ActivePlayerInterface {
 public:
  // public constructors & destructors
  virtual ~ActivePlayerInterface() {}

  // public pure virtual methods
  virtual void Prepare(const string& object_src, vector<Property> properties,
                       vector<Event> events) = 0;
  virtual void AddEvent(Event evt) = 0;
  virtual void RemoveEvent(const string& event_id) = 0;
  virtual void PostAction(const string& event_id, const string& action) = 0;
  virtual void RequestPropertyValue(const string& name) = 0;
  virtual void SetPropertyValue(const string& name, const string& value,
                                unsigned int duration) = 0;
  virtual void RegistryPlayerListener(
      ActivePlayerListenerInterface* listener) = 0;
};

/*----------------------------------------------------------------------
 |   ActiveClassListenerInterface and ActiveClassInterface interfaces.
 |   It is use in two cases:
 |   1. Between HostHpe and Active Parent Communication Manager.
 |   2. Between Active Parent Communication Manager and Active Child
 |   Communication Manager.
 +---------------------------------------------------------------------*/
class ActiveClassListenerInterface {
 public:
  // public constructors & destructors
  virtual ~ActiveClassListenerInterface() {}

  // public pure virtual methods
  virtual void ReportPropertyValue(const string& object_id, const string& name,
                                   const string& value) = 0;
  virtual void NotifyEventTransition(const string& object_id,
                                     const string& event_id,
                                     const string& transition) = 0;
  virtual void NotifyError(const string& object_id, const string& message) = 0;
};

class ActiveClassInterface {
 public:
  // public constructors & destructors
  virtual ~ActiveClassInterface() {}

  // public pure virtual methods
  virtual void Prepare(const string& object_id, const string& object_src,
                       vector<Property> properties, vector<Event> events) = 0;
  virtual void AddEvent(const string& object_id, Event evt) = 0;
  virtual void RemoveEvent(const string& object_id, const string& event_id) = 0;
  virtual void PostAction(const string& object_id, const string& event_id,
                          const string& action) = 0;
  virtual void RequestPropertyValue(const string& object_id,
                                    const string& name) = 0;

  virtual void SetPropertyValue(const string& object_id, const string& name,
                                const string& value, unsigned int duration) = 0;
  virtual void RegistryActiveClassListener(
      ActiveClassListenerInterface* listener) = 0;
};

#endif  // FSMDA_MODEL_ACTIVE_OBJECTS_API_H_
