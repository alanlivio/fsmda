#ifndef FSMDA_COMMUNICATION_MODEL_ACTIVE_OBJECT_INTERFACES_H_
#define FSMDA_COMMUNICATION_MODEL_ACTIVE_OBJECT_INTERFACES_H_

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
  string property_name_;
  string property_value_;
};

/*----------------------------------------------------------------------
 |   Event class
 +---------------------------------------------------------------------*/
class Event {
  string event_id_;
  string event_type_;
  string event_desc_;
};

/*----------------------------------------------------------------------
 |   ActivePcmInterface abstract class
 +---------------------------------------------------------------------*/
class ActivePcmInterface {
 public:
  // public constructors & destructors
  virtual ~ActivePcmInterface() {}

  // public pure virtual methods
  virtual void RequestPropertyValue(const string& object_id,
                                    const string& name) = 0;
  virtual void NotifyEventTransition(const string& object_id,
                                     const string& event_id,
                                     const string& transition) = 0;
  virtual void NotifyError(const string& object_id, const string& message) = 0;
};

/*----------------------------------------------------------------------
 |   ActiveCcmInterface abstract class
 +---------------------------------------------------------------------*/
class ActiveCcmInterface {
 public:
  // public constructors & destructors
  virtual ~ActiveCcmInterface() {}

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
};

#endif  // FSMDA_COMMUNICATION_MODEL_ACTIVE_OBJECT_INTERFACES_H_
