#include <cassert>
#include <cstring>
#include "libtemplate.h"

using namespace std;

int main() {
  LibTemplate test;
  assert(strcmp(test.get_hello(), "Hello world!") == 0);
  return 0;
}
