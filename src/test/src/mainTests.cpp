#include <stdio.h>

#include <gtest/gtest.h>

#include <UtilsTest.h>
#include <SettingManagerTest.h>
#include "../headers/HTTPHandlerTests.h"

int main(int argc, char **argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
