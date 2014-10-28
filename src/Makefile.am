############################## Headers ####################################
# Headers
nobase_pkginclude_HEADERS =\
  fsmda/model/communication/ondemand_object_control.h\
  fsmda/model/communication/active_object_control.h\
  fsmda/model/communication/passive_object_control.h\
  fsmda/model/communication/mediacapture_object_control.h\
  fsmda/model/paring/class_handling.h\
  fsmda/model/paring/device_paring.h\
  fsmda/services/upnp_service.h\
  fsmda/gingancl/paring/parent_paring_manager.h\
  fsmda/gingancl/paring/child_paring_manager.h

############################## Libraries ####################################
# Libraries
lib_LTLIBRARIES = libfsmda.la

# Libraries sources
libfsmda_la_SOURCES = \
  fsmda/gingancl/paring/parent_paring_manager.cpp\
  fsmda/gingancl/paring/child_paring_manager.cpp

# Libraries compiler options
libfsmda_la_CPPFLAGS = -I./ $(PLATINUMKIT_CFLAGS)

# Libraries linker options
libfsmda_la_LDFLAGS =  $(PLATINUMKIT_LIBS)

############################## pkg-config ####################################
# Libraries pkg-config file
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfsmda.pc
