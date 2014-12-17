/* Copyright 2014 libtemplate team */

#include "gtest/gtest.h"
#include <iostream>
#include <fstream>

using ::std::cout;
using ::std::clog;

int main(int argc, char **argv) {
  // redirect clog to /dev/null/
  static std::ofstream logOutput;
  logOutput.open("/dev/null");
  clog.rdbuf(logOutput.rdbuf());

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
