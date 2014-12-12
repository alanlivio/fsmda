#ifndef FSMDA_PARING_SERVICES_PARING_SERVICE_INTERFACE_H_
#define FSMDA_PARING_SERVICES_PARING_SERVICE_INTERFACE_H_

/*----------------------------------------------------------------------
 |   ParingServiceInterface class
 +---------------------------------------------------------------------*/
class ParingServiceInterface {
 public:
  // public constructors & destructors
  virtual ~ParingServiceInterface() {}

  // public pure virtual methods
  virtual int StartParingService() = 0;
  virtual int StopParingService() = 0;
  virtual bool IsParingServiceStarted() = 0;
};

#endif  // FSMDA_PARING_SERVICES_PARING_SERVICE_INTERFACE_H_
