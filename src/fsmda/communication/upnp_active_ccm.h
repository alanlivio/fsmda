#ifndef FSMDA_COMMUNICATION_SERVICES_UPNP_ACTIVE_CCM_H_
#define FSMDA_COMMUNICATION_SERVICES_UPNP_ACTIVE_CCM_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
#include <vector>
#include <NptTypes.h>
#include <PltDeviceHost.h>
#include <PltUPnP.h>
#include <PltCtrlPoint.h>
#include "fsmda/model/active_object_interfaces.h"
#include "fsmda/communication/communication_service_interface.h"

using std::string;
using std::vector;

/*----------------------------------------------------------------------
 |   UpnpActiveCcm class
 +---------------------------------------------------------------------*/
class UpnpActiveCcm : public PLT_DeviceHost,
                      public PLT_CtrlPointListener,
                      public ActiveCcmInterface,
                      public CommunicationServiceInterface {
 public:
  // public constructors & destructors
  UpnpActiveCcm();
  virtual ~UpnpActiveCcm();

  // public CommunicationServiceInterface overload methods
  virtual int StartCommunicationService();
  virtual int StopCommunicationService();
  virtual bool IsCommunicationServiceStarted();

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

  // PLT_DeviceHost overloaded methods
  virtual NPT_Result SetupServices();
  virtual NPT_Result OnAction(PLT_ActionReference& action,
                              const PLT_HttpRequestContext& context);

  // PLT_CtrlPointListener overloaded methods
  virtual NPT_Result OnDeviceAdded(PLT_DeviceDataReference& device);
  virtual NPT_Result OnDeviceRemoved(PLT_DeviceDataReference& device);
  virtual NPT_Result OnActionResponse(NPT_Result res,
                                      PLT_ActionReference& action,
                                      void* userdata);
  virtual NPT_Result OnEventNotify(PLT_Service* service,
                                   NPT_List<PLT_StateVariable*>* vars);
};

#endif  // FSMDA_COMMUNICATION_SERVICES_UPNP_ACTIVE_CCM_H_
