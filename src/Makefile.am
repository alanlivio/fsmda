############################## Headers ####################################
# Headers
nobase_pkginclude_HEADERS =\
  fsmda/services/upnp_service.h\
  fsmda/gingancl/ParentParingManager.h\
  fsmda/model/communication/ondemand_object_control.h\
  fsmda/model/communication/active_object_control.h\
  fsmda/model/communication/passive_object_control.h\
  fsmda/model/communication/mediacapture_object_control.h\
  fsmda/model/paring/class_handling.h\
  fsmda/model/paring/device_paring.h

############################## Libraries ####################################
# Libraries
lib_LTLIBRARIES = libfsmda.la

# Libraries sources
libfsmda_la_SOURCES = libfsmda.cpp

# Libraries compiler options
libfsmda_la_CPPFLAGS = $(PLATINUMKIT_CFLAGS)

# Libraries linker options
libfsmda_la_LDFLAGS =  $(PLATINUMKIT_LIBS)

############################## pkg-config ####################################
# Libraries pkg-config file
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfsmda.pc
