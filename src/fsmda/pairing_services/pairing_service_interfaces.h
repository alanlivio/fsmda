#ifndef FSMDA_PAIRING_SERVICES_PAIRING_SERVICE_INTERFACES_H_
#define FSMDA_PAIRING_SERVICES_PAIRING_SERVICE_INTERFACES_H_
/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
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
class ParentPairingServiceInterface {
 public:
  // public constructors & destructors
  virtual ~ParentPairingServiceInterface() {}

  // public pure virtual methods
  virtual int SetServiceOwner(ParentPairingManager* service_owner) = 0;
  virtual int AddDeviceClassForDiscover(
      const string& application_id, unsigned int class_index,
      DeviceClassDescription* device_class_description) = 0;
  virtual int RemoveDeviceClassForDiscover(const string& application_id,
                                           unsigned int class_index) = 0;
  virtual int StartPairingService() = 0;
  virtual int StopPairingService() = 0;
  virtual bool IsPairingServiceStarted() = 0;
  virtual unsigned int GetNumberOfDiscoveredChildren() = 0;
};

/*----------------------------------------------------------------------
 |   ChildPairingServiceInterface class
 +---------------------------------------------------------------------*/
class ChildPairingServiceInterface {
 public:
  // public constructors & destructors
  virtual ~ChildPairingServiceInterface() {}

  // public pure virtual methods
  virtual int SetServiceOwner(ChildPairingManager* service_owner) = 0;
  virtual int SetDeviceDescription(DeviceDescription* device_description) = 0;
  virtual int StartPairingService() = 0;
  virtual int StopPairingService() = 0;
  virtual bool IsPairingServiceStarted() = 0;
  virtual bool PerformedHandShake() = 0;
};

#endif  // FSMDA_PAIRING_SERVICES_PAIRING_SERVICE_INTERFACES_H_
