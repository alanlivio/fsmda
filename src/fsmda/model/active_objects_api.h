#ifndef FSMDA_MODEL_ACTIVE_OBJECTS_API_H_
#define FSMDA_MODEL_ACTIVE_OBJECTS_API_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

class Property {
 public:
  string property_name_;
  string property_value_;
  const string to_string() {
    return property_name_ + "=" + property_value_;
  }
  static const string to_string(vector<Property> properties) {
    string res = "{";
    for (int i = 0; i < properties.size(); i++)
      res + properties[i].to_string() + ",";
    res += "}";
    return res;
  }
};

class Event {
 public:
  string event_id_;
  string event_type_;
  string event_desc_;
  const string to_string() {
    return event_id_ + "," + event_type_ + "," + event_desc_;
  }
  static const string to_string(vector<Event> events) {
    string res = "{";
    for (int i = 0; i < events.size(); i++)
      res + events[i].to_string() + ",";
    res += "}";
    return res;
  }
};

// ActivePlayerInterface and ActivePlayerListenerInterface interfaces.
// It is use between Active Child Communication Manager
// and RemotePlayer
class ActivePlayerListenerInterface {
 public:
  // public constructors & destructors
  virtual ~ActivePlayerListenerInterface() {
  }

  // public pure virtual methods
  virtual void report_property_value(const string& name,
                                     const string& value) = 0;
  virtual void notify_event_transition(const string& event_id,
                                       const string& transition) = 0;
  virtual void notify_error(const string& message) = 0;
};

class ActivePlayerInterface {
 public:
  // public constructors & destructors
  virtual ~ActivePlayerInterface() {
  }

  // public pure virtual methods
  virtual void prepare(const string& object_src, vector<Property> properties,
                       vector<Event> events) = 0;
  virtual void add_event(Event evt) = 0;
  virtual void remove_event(const string& event_id) = 0;
  virtual void post_action(const string& event_id, const string& action) = 0;
  virtual void request_roperty_value(const string& name) = 0;
  virtual void set_property_value(const string& name, const string& value,
                                  unsigned int duration) = 0;
  virtual void registry_player_listener(
      ActivePlayerListenerInterface* listener) = 0;
};

// ActiveClassListenerInterface and ActiveClassInterface interfaces.
// It is use in two cases:
// 1. Between HostHpe and Active Parent Communication Manager.
// 2. Between Active Parent Communication Manager and Active Child
// Communication Manager.
class ActiveClassListenerInterface {
 public:
  // public constructors & destructors
  virtual ~ActiveClassListenerInterface() {
  }

  // public pure virtual methods
  virtual void report_property_value(const string& object_id,
                                     const string& name,
                                     const string& value) = 0;
  virtual void notify_event_transition(const string& object_id,
                                       const string& event_id,
                                       const string& transition) = 0;
  virtual void notify_error(const string& object_id, const string& message) = 0;
};

class ActiveClassInterface {
 public:
  // public constructors & destructors
  virtual ~ActiveClassInterface() {
  }

  // public pure virtual methods
  virtual void prepare(const string& object_id, const string& object_src,
                       vector<Property> properties, vector<Event> events) = 0;
  virtual void add_event(const string& object_id, Event evt) = 0;
  virtual void remove_event(const string& object_id,
                            const string& event_id) = 0;
  virtual void post_action(const string& object_id, const string& event_id,
                           const string& action) = 0;
  virtual void request_property_value(const string& object_id,
                                      const string& property_name) = 0;

  virtual void set_property_value(const string& object_id,
                                  const string& property_name,
                                  const string& property_value,
                                  unsigned int property_duration) = 0;
  virtual void registry_active_class_listener(
      ActiveClassListenerInterface* listener) = 0;
};

#endif  // FSMDA_MODEL_ACTIVE_OBJECTS_API_H_
