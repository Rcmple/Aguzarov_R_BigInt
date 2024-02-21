#include "../BigInt/BigInt.h"
#include <gtest/gtest.h>
unsigned BigInt::accuracy = 10;

TEST(plus, justplus){
BigInt a(to_string(1234567890));
BigInt b(to_string(9876543210));
BigInt c = a + b;
ASSERT_EQ(c.to_str(), "11111111100");
}

TEST(plus, plusnegative){
BigInt a(to_string(-63214796265));
BigInt b(to_string(-3288632585));
BigInt c = a + b;
ASSERT_EQ(c.to_str(), "-66503428850");
}

TEST(plus, plusnegativpositive){
BigInt a(to_string(-63214796265));
BigInt b(to_string(100000000));
BigInt c = a + b;
ASSERT_EQ(c.to_str(), "-63114796265");
}

TEST(plus, plusdecimal){
BigInt a(to_string(0.35));
BigInt b(to_string(0.00007));
BigInt c = a + b;
ASSERT_EQ(c.to_str(), "0.35007");
}
