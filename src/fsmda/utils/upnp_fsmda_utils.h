#ifndef PLATINUMKIT_H_
#define PLATINUMKIT_H_

/*----------------------------------------------------------------------
 |   include
 +---------------------------------------------------------------------*/

#include "PltUPnP.h"

using namespace std;

/*----------------------------------------------------------------------
 |   PlatinumKit class
 +---------------------------------------------------------------------*/
class PlatinumKit
{
public:
  // class fields and methods
  static PLT_UPnP*
  requestUpnpReference ();
  static void
  releaseUpnpReference ();

private:
  // private constructors & destructors
  PlatinumKit (){}
  ~PlatinumKit (){}

  // private fields
  static PLT_UPnP * upnp_singleton_;
  static bool upnp_running_;
  static unsigned int references_count_;
};

#endif /* PLATINUMKIT_H_ */
