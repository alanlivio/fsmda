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
};

/*----------------------------------------------------------------------
 |   Event class
 +---------------------------------------------------------------------*/
class Event {
 public:
  string event_id_;
  string event_type_;
  string event_desc_;
};

/*----------------------------------------------------------------------
 |   ActivePlayerInterface abstract class
 +---------------------------------------------------------------------*/
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
  virtual void ReportPropertyValue(const string& name, const string& value) = 0;
  virtual void SetPropertyValue(const string& name, const string& value,
                                unsigned int duration) = 0;
};

/*----------------------------------------------------------------------
 |   ActiveClassListenerInterface abstract class
 +---------------------------------------------------------------------*/
class ActiveClassListenerInterface {
 public:
  // public constructors & destructors
  virtual ~ActiveClassListenerInterface() {}

  // public pure virtual methods
  virtual void RequestPropertyValue(const string& object_id,
                                    const string& name) = 0;
  virtual void NotifyEventTransition(const string& object_id,
                                     const string& event_id,
                                     const string& transition) = 0;
  virtual void NotifyError(const string& object_id, const string& message) = 0;

  virtual void SetActivePlayer(ActivePlayerInterface* player) = 0;
};

/*----------------------------------------------------------------------
 |   ActiveClassInterface abstract class
 +---------------------------------------------------------------------*/
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
  virtual void ReportPropertyValue(const string& object_id, const string& name,
                                   const string& value) = 0;
  virtual void SetPropertyValue(const string& object_id, const string& name,
                                const string& value, unsigned int duration) = 0;
  virtual void SetHostHpe(ActiveClassListenerInterface* hpe) = 0;
};

#endif  // FSMDA_MODEL_ACTIVE_OBJECTS_API_H_
