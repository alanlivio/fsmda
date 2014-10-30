#ifndef FSMDA_MEDIA_CAPTURE_OBJECT_CONTROL_H_
#define FSMDA_MEDIA_CAPTURE_OBJECT_CONTROL_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/

#include <string>

using namespace std;

/*----------------------------------------------------------------------
 |   MediaCapturePCMInterface abstract class
 +---------------------------------------------------------------------*/
class MediaCapturePCMInterface
{
public:
  // public constructors & destructors
  virtual
  ~MediaCapturePCMInterface ()
  {
  }

  // public pure virtual methods
  virtual void
  sendContent (char* content, const string& resourceId,
	       unsigned int childIndex)=0;
};

/*----------------------------------------------------------------------
 |   MediaCaptureCCMInterface abstract class
 +---------------------------------------------------------------------*/
class MediaCaptureCCMInterface
{
public:
  // public constructors & destructors
  virtual
  ~MediaCaptureCCMInterface ()
  {
  }

  // public pure virtual methods
  virtual void
  requestContent (const string& resourceId, unsigned int deviceIndex)=0;
};
#endif /* FSMDA_MEDIA_CAPTURE_OBJECT_CONTROL_H_ */
