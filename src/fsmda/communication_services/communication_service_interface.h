#ifndef FSMDA_COMMUNICATION_SERVICES_COMMUNICATION_SERVICE_INTERFACE_H_
#define FSMDA_COMMUNICATION_SERVICES_COMMUNICATION_SERVICE_INTERFACE_H_
/*----------------------------------------------------------------------
 |   ServiceCmInterface class
 +---------------------------------------------------------------------*/
class CommunicationServiceInterface {
 public:
  // public constructors & destructors
  virtual ~CommunicationServiceInterface() {}

  // public pure virtual methods
  virtual int StartCommunicationService() = 0;
  virtual int StopCommunicationService() = 0;
  virtual bool IsCommunicationServiceStarted() = 0;
};

#endif  // FSMDA_COMMUNICATION_SERVICES_COMMUNICATION_SERVICE_INTERFACE_H_
