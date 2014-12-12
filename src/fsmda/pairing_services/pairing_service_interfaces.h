#ifndef FSMDA_PAIRING_SERVICES_PAIRING_SERVICE_INTERFACE_H_
#define FSMDA_PAIRING_SERVICES_PAIRING_SERVICE_INTERFACE_H_

/*----------------------------------------------------------------------
 |   forward definitions
 +---------------------------------------------------------------------*/
class ParentPairingManager;
class ChildPairingManager;

/*----------------------------------------------------------------------
 |   PairingServiceInterface class
 +---------------------------------------------------------------------*/
class ParentPairingServiceInterface {
 public:
  // public constructors & destructors
  virtual ~ParentPairingServiceInterface() {}

  // public pure virtual methods
  virtual int SetServiceOwner(ParentPairingManager* service_owner) = 0;
  virtual int StartPairingService() = 0;
  virtual int StopPairingService() = 0;
  virtual bool IsPairingServiceStarted() = 0;
  virtual bool GetNumberOfDiscoveredChildren() = 0;
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
  virtual int StartPairingService() = 0;
  virtual int StopPairingService() = 0;
  virtual bool IsPairingServiceStarted() = 0;
  virtual bool PerformedHandShake() = 0;
};

#endif  // FSMDA_PAIRING_SERVICES_PAIRING_SERVICE_INTERFACE_H_
