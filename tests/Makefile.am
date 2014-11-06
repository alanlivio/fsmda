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
TESTS = t0_test t1_test t2_test

############################## Tests libraries #################################
#### Tests libraries
#check_LTLIBRARIES = \
#  libgmockgtest.la 
#  
#### Tests libraries sources
#libgmockgtest_la_SOURCES = \
#  gtest/src/gtest-all.cc
#
#### Tests libraries compiler options
#libgmockgtest_la_CPPFLAGS =\
#  $(GMOCKGTEST_CPPFLAGS)\
#  $(GTEST_EXTRA_CPPFLAGS)
#
#libgmockgtest_la_LDFLAGS =\
#  $(GTEST_EXTRA_LDFLAGS)

############################## Tests scripts #################################
#check_SCRIPTS = \
#  helloworld_script_test.sh

############################## Tests programs #################################
### Tests programs
check_PROGRAMS = t0_test t1_test t2_test

### Tests programs sources
t0_test_SOURCES = test0.cpp
t1_test_SOURCES = test1.cpp
t2_test_SOURCES = test2.cpp

### Tests programs compiler options
t0_test_CPPFLAGS = $(PLATINUMKIT_CFLAGS) $(LIBXML2_CFLAGS)
t1_test_CPPFLAGS = $(PLATINUMKIT_CFLAGS) $(LIBXML2_CFLAGS)
t2_test_CPPFLAGS = $(PLATINUMKIT_CFLAGS) $(LIBXML2_CFLAGS)

### Tests programs linker options
t0_test_LDADD = $(top_srcdir)/src/libfsmda.la $(PLATINUMKIT_LIBS) $(LIBXML2_LIBS)
t1_test_LDADD = $(top_srcdir)/src/libfsmda.la $(PLATINUMKIT_LIBS) $(LIBXML2_LIBS)
t2_test_LDADD = $(top_srcdir)/src/libfsmda.la $(PLATINUMKIT_LIBS) $(LIBXML2_LIBS)
  
############################## Testes gtests-based ###########################
#### Tests programs
#check_PROGRAMS += helloworld_gtest
#
#### Tests programs sources
#helloworld_gtest_SOURCES = helloworld_gtest.cc
#
#### Tests programs compiler options
#helloworld_gtest_CPPFLAGS = \
#  $(GMOCKGTEST_CPPFLAGS)
#
#### Tests programs linker options
#helloworld_gtest_LDADD = \
#  $(top_builddir)/src/libtemplate.la\
#  libgmockgtest.la