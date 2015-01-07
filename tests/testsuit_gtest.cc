/* Copyright 2014 libtemplate team */

#include "gtest/gtest.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::clog;
using std::cerr;

int main(int argc, char **argv) {
  // redirect clog to /dev/null/
  static std::ofstream logOutput;
  logOutput.open("/dev/null");
  clog.rdbuf(logOutput.rdbuf());

  // configure gtest
  //  ::testing::FLAGS_gtest_repeat = 2;
  //  ::testing::FLAGS_gtest_output = "/tmp/res.xml";
  ::testing::FLAGS_gtest_break_on_failure = true;
  ::testing::FLAGS_gtest_list_tests = false;
  ::testing::FLAGS_gtest_print_time = 0;
  ::testing::FLAGS_gtest_color = "yes";
  //  ::testing::FLAGS_gtest_filter = "PairingAsParent.*";
  ::testing::FLAGS_gtest_filter = "*.*InDifferentProcesses";
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
