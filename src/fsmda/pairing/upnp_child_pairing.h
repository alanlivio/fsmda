#ifndef FSMDA_PAIRING_UPNP_CHILD_PAIRING_H_
#define FSMDA_PAIRING_UPNP_CHILD_PAIRING_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <map>
#include <string>
#include <NptTypes.h>
#include <PltDeviceHost.h>
#include <PltUPnP.h>
#include <PltCtrlPoint.h>
#include "fsmda/pairing/pairing_service_interfaces.h"
#include "fsmda/model/device_pairing_api.h"

using std::map;
using std::string;

/*----------------------------------------------------------------------
 |   forward definitions
 +---------------------------------------------------------------------*/
class ChildPairingManager;

/*----------------------------------------------------------------------
 |   UpnpChildPairing class
 +---------------------------------------------------------------------*/
class UpnpChildPairing : public PLT_DeviceHost,
                         public PLT_CtrlPointListener,
                         public DevicePairingPpmInterface,
                         public ChildPairingServiceInterface {
 public:
  // public constructors & destructors
  UpnpChildPairing();
  ~UpnpChildPairing();

  // DevicePairingPpmInterface overloaded methods
  virtual void AddDeviceToClass(const string& application_id,
                                const string& device_address,
                                unsigned int class_index,
                                const string& device_desc);
  virtual void GetChildIndex(const string& application_id,
                             const string& device_address,
                             unsigned int class_index);

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

  // ParentPairingServiceInterface overloaded methods
  // called by ChildPairingManager
  virtual int StartPairingService();
  virtual int StopPairingService();
  virtual bool IsPairingServiceStarted();
  virtual int set_service_owner(ChildPairingManager* service_owner);

 private:
  bool handshake_performed_;
  PLT_UPnP* upnp_instance_;
  PLT_DeviceHostReference device_host_;
  PLT_CtrlPointReference ctrl_point_;
  PLT_Service* device_service_;
  ChildPairingManager* child_pairing_manager_;
  PLT_Service* parent_pairing_;
  PLT_DeviceDataReference last_parent_;
  NPT_SharedVariable last_parent_semaphore;
};

#endif  // FSMDA_PAIRING_UPNP_CHILD_PAIRING_H_
