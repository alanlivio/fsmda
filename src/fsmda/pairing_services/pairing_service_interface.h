#ifndef FSMDA_PAIRING_SERVICES_PAIRING_SERVICE_INTERFACE_H_
#define FSMDA_PAIRING_SERVICES_PAIRING_SERVICE_INTERFACE_H_

/*----------------------------------------------------------------------
 |   PairingServiceInterface class
 +---------------------------------------------------------------------*/
class PairingServiceInterface {
 public:
  // public constructors & destructors
  virtual ~PairingServiceInterface() {}

  // public pure virtual methods
  virtual int StartPairingService() = 0;
  virtual int StopPairingService() = 0;
  virtual bool IsPairingServiceStarted() = 0;
};

#endif  // FSMDA_PAIRING_SERVICES_PAIRING_SERVICE_INTERFACE_H_
