# Tests options
TESTS = t0_test
AM_COLOR_TESTS = always

# Tests programs
check_PROGRAMS = t0_test

# Tests sources
t0_test_SOURCES = test0.cpp

# Tests compiler options
t0_test_CPPLAGS = -I$(top_builddir)/include

# Tests linker options
t0_test_LDADD = $(top_builddir)/src/libtemplate.la

# Tests clean
CLEANFILES = *.log *.trs