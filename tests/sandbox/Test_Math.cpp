#include <gtest/gtest.h>
#include "../../src/sandbox/SampleMath.h"

TEST(MathTest, Add) {
  SampleMath math;
  
  math.Add(1, 2);

  EXPECT_EQ(math.Add(1, 2), 3);
  EXPECT_EQ(math.Result(), 3);
}