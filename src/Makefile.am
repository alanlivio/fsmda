############################## Headers ####################################
# Headers
nobase_pkginclude_HEADERS =\
  fsmda/model/communication/ondemand_object_control.h\
  fsmda/model/communication/active_object_control.h\
  fsmda/model/communication/passive_object_control.h\
  fsmda/model/communication/mediacapture_object_control.h\
  fsmda/model/paring/class_handling.h\
  fsmda/model/paring/device_paring.h\
  fsmda/gingancl/paring/parent_paring_manager.h\
  fsmda/gingancl/paring/child_paring_manager.h\
  fsmda/protocol/upnp_manager.h

############################## Libraries ####################################
# Libraries
lib_LTLIBRARIES = libfsmda.la

# Libraries sources
libfsmda_la_SOURCES = \
  fsmda/gingancl/paring/parent_paring_manager.cpp\
  fsmda/gingancl/paring/child_paring_manager.cpp\
  fsmda/gingancl/paring/device_description.cpp\
  fsmda/gingancl/paring/device_class_description.cpp\
  fsmda/gingancl/communication/active_ccm.cpp\
  fsmda/gingancl/communication/active_pcm.cpp\
  fsmda/gingancl/communication/passive_ccm.cpp\
  fsmda/gingancl/communication/passive_pcm.cpp\
  fsmda/gingancl/communication/mediacapture_pcm.cpp\
  fsmda/gingancl/communication/mediacapture_ccm.cpp\
  fsmda/gingancl/communication/ondemand_pcm.cpp\
  fsmda/gingancl/communication/ondemand_ccm.cpp\
  fsmda/protocol/upnp_manager.cpp
  

# Libraries compiler options
libfsmda_la_CPPFLAGS = -I./ $(PLATINUMKIT_CFLAGS) $(LIBXML2_CFLAGS)

# Libraries linker options
libfsmda_la_LDFLAGS =  $(PLATINUMKIT_LIBS) $(LIBXML2_LIBS)

############################## pkg-config ####################################
# Libraries pkg-config file
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfsmda.pc
