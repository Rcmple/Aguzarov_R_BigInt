#include "../BigInt/BigInt.h"
#include <gtest/gtest.h>
TEST(sub, justsub){
BigInt a(to_string(12345678));
BigInt b(to_string(3333333));
BigInt c = a - b;
ASSERT_EQ(c.to_str(), "9012345");
}

TEST(sub, bigger){
BigInt a(to_string(12344321));
BigInt b(to_string(43254366));
BigInt c = a - b;
ASSERT_EQ(c.to_str(), "-30910045");
}

TEST(sub, decimal){
BigInt a(to_string(0.0008));
BigInt b(to_string(0.7));
BigInt c = a - b;
ASSERT_EQ(c.to_str(), "-0.6992");
}