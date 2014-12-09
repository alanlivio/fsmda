############################## Variables ######################################
GMOCKGTEST_CPPFLAGS =\
  -I./gmock/\
  -I./gmock/include\
  -I./gtest/\
  -I./gtest/include/
  
############################## Tests options ##################################
# Build rules for tests.
# TESTS_ENVIRONMENT: Set environment variables for the test run
# TESTS: Define programs run automatically by "make check" 
# UNIT_TESTS: Define programs run automatically by "make check-unit-tests"
# check_PROGRAMS: Define programs built by "make check" but not necessarily run
# check_LTLIBRARIES: Define libraries built by "make check"
# check_SCRIPTS: Define scripts built by "make check"

#TESTS_ENVIRONMENT =
AM_COLOR_TESTS = always
AM_TESTS_FD_REDIRECT = 
CLEANFILES = *.log *.trs
TESTS = testsuit_gtest

############################# Tests libraries #################################
### Tests libraries
check_LTLIBRARIES = \
  libgmockgtest.la 
  
### Tests libraries sources
libgmockgtest_la_SOURCES = \
  gtest/src/gtest-all.cc

### Tests libraries compiler options
libgmockgtest_la_CPPFLAGS =\
  $(GMOCKGTEST_CPPFLAGS)\
  $(GTEST_EXTRA_CPPFLAGS)

libgmockgtest_la_LDFLAGS =\
  $(GTEST_EXTRA_LDFLAGS)
  
############################# Testes gtests-based ###########################
### Tests programs
check_PROGRAMS = testsuit_gtest paring2_test_helper

### Tests programs sources
testsuit_gtest_SOURCES = \
  testsuit_gtest.cc\
  communication1_test.cc\
  paring1_test.cc\
  paring2_test.cc\
  utils1_test.cc

#testsuit_gtest_SOURCES = \
  testsuit_gtest.cc\
  simple_test.cc

paring2_test_helper_SOURCES = \
  paring2_test_helper.cc

### Tests programs compiler options
testsuit_gtest_CPPFLAGS = \
  $(PLATINUMKIT_CFLAGS)\
  $(LIBXML2_CFLAGS)\
  $(GMOCKGTEST_CPPFLAGS)

paring2_test_helper_CPPFLAGS = \
  $(PLATINUMKIT_CFLAGS)\
  $(LIBXML2_CFLAGS)

### Tests programs linker options
testsuit_gtest_LDADD = \
  $(top_srcdir)/src/libfsmda.la\
  $(PLATINUMKIT_LIBS)\
  $(LIBXML2_LIBS)\
  $(top_srcdir)/tests/libgmockgtest.la

paring2_test_helper_LDADD = \
  $(top_srcdir)/src/libfsmda.la\
  $(PLATINUMKIT_LIBS)\
  $(LIBXML2_LIBS)
