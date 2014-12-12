#ifndef FSMDA_PAIRING_SERVICES_UPNP_CHILD_PAIRING_H_
#define FSMDA_PAIRING_SERVICES_UPNP_CHILD_PAIRING_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <NptTypes.h>
#include <PltAction.h>
#include <PltDeviceHost.h>
#include <PltHttp.h>
#include <PltUPnP.h>
#include <PltCtrlPoint.h>
#include "fsmda/pairing_services/pairing_service_interface.h"
#include "fsmda/model/device_pairing_interfaces.h"

/*----------------------------------------------------------------------
 |   forward definitions
 +---------------------------------------------------------------------*/
class ChildPairingManager;

/*----------------------------------------------------------------------
 |   UpnpChildPairing class
 +---------------------------------------------------------------------*/
class UpnpChildPairing : public PLT_DeviceHost,
                         public PLT_CtrlPointListener,
                         public PairingServiceInterface {
 public:
  // public constructors & destructors
  explicit UpnpChildPairing(ChildPairingManager* child_pairing_manager);
  virtual ~UpnpChildPairing();

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

  // PairingServiceInterface overloaded methods
  virtual int StartPairingService();
  virtual int StopPairingService();
  virtual bool IsPairingServiceStarted() { return m_Started; }

  // public methods
  bool IsPaired() { return paired_with_parent_; }

 private:
  bool paired_with_parent_;
  PLT_UPnP* upnp_instance_;
  PLT_DeviceHostReference* device_host_;
  PLT_Service* device_service_;
  PLT_CtrlPointReference* ctrl_point_;
  ChildPairingManager* child_pairing_manager_;
  PLT_Service* parent_pairing_service_;
};

#endif  // FSMDA_PAIRING_SERVICES_UPNP_CHILD_PAIRING_H_
