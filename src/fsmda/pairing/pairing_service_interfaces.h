#ifndef FSMDA_PAIRING_PAIRING_SERVICE_INTERFACES_H_
#define FSMDA_PAIRING_PAIRING_SERVICE_INTERFACES_H_
/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <fsmda/model/device_pairing_api.h>
#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   forward definitions
 +---------------------------------------------------------------------*/
class ParentPairingManager;
class ChildPairingManager;
class DeviceDescription;
class DeviceClassDescription;

/*----------------------------------------------------------------------
 |   PairingServiceInterface class
 +---------------------------------------------------------------------*/
class DeviceClassDiscoverParams {
 public:
  explicit DeviceClassDiscoverParams(
      const string& application_id, unsigned int class_index,
      DeviceClassDescription* device_class_description)
      : application_id_(application_id),
        class_index_(class_index),
        device_class_description_(device_class_description) {}
  string application_id_;
  unsigned int class_index_;
  DeviceClassDescription* device_class_description_;
};

/*----------------------------------------------------------------------
 |   PairingServiceInterface class
 +---------------------------------------------------------------------*/
class ParentPairingServiceInterface {
 public:
  // public constructors & destructors
  virtual ~ParentPairingServiceInterface() {}

  // public pure virtual methods
  virtual int AddDeviceClassForDiscover(
      DeviceClassDiscoverParams* discover_params) = 0;
  virtual int RemoveDeviceClassForDiscover(
      DeviceClassDiscoverParams* discover_params) = 0;
  virtual int StartPairingService() = 0;
  virtual int StopPairingService() = 0;
  virtual int set_service_owner(ParentPairingManager* service_owner) = 0;
  virtual bool pairing_service_started() = 0;
  virtual unsigned int registred_children() = 0;
};

/*----------------------------------------------------------------------
 |   ChildPairingServiceInterface class
 +---------------------------------------------------------------------*/
class ChildPairingServiceInterface {
 public:
  // public constructors & destructors
  virtual ~ChildPairingServiceInterface() {}

  // public pure virtual methods
  virtual int StartPairingService() = 0;
  virtual int StopPairingService() = 0;
  virtual bool pairing_service_started() = 0;
  virtual int set_service_owner(ChildPairingManager* service_owner) = 0;
  virtual bool handshak_performed() = 0;
};

#endif  // FSMDA_PAIRING_PAIRING_SERVICE_INTERFACES_H_
