/* Copyright 2014 libtemplate team */

#include "gtest/gtest.h"
#include <iostream>
#include <fstream>

using ::std::cout;
using ::std::clog;
using ::std::cerr;

int main(int argc, char **argv) {
  // configure gtest flags
  ::testing::InitGoogleTest(&argc, argv);

  // redirect clog to /dev/null/
  static std::ofstream logOutput;
  logOutput.open("/dev/null");
  clog.rdbuf(logOutput.rdbuf());

  //  // redirect clog to /dev/null/
  //  static std::ofstream errOutput;
  //  errOutput.open("/dev/null");
  //  cerr.rdbuf(errOutput.rdbuf());

  // configure gtest flags
  ::testing::FLAGS_gtest_break_on_failure = true;
  ::testing::FLAGS_gtest_list_tests = false;
  ::testing::FLAGS_gtest_print_time = 0;
  ::testing::FLAGS_gtest_color = "yes";
  //  ::testing::FLAGS_gtest_output = "/tmp/res.xml";
  ::testing::FLAGS_gtest_filter = "*";
//  ::testing::FLAGS_gtest_filter =
//      "UpnpPairingServicesTest.HandShakeWithOneDeviceInSameProcess:"
//      "UpnpUtilsTest.GetRunningUpnpInstance";
  //  ::testing::FLAGS_gtest_repeat = 2;

  return RUN_ALL_TESTS();
}
