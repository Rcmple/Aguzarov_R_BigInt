#include "BigInt/BigInt.h"
#include <gtest/gtest.h>

TEST(divide, justdivide){
BigInt a(to_string(9206251));
BigInt b(to_string(361));
BigInt c = a / b;
ASSERT_EQ(c.to_str(), "25502.0803324099");
}

TEST(divide, divdecimal){
BigInt a(to_string(325.43523));
BigInt b(to_string(23.43634));
BigInt c = a / b;
ASSERT_EQ(c.to_str(), "13.8859237406");
}

TEST(divide, smalltobig){
BigInt a(to_string(0.000123));
BigInt b(to_string(123));
BigInt c = a / b;
ASSERT_EQ(c.to_str(), "0.0000010000");
}