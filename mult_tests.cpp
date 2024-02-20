#include "BigInt/BigInt.h"
#include <gtest/gtest.h>
TEST(mult, justmult){
BigInt a(to_string(1324234678));
BigInt b(to_string(345342));
BigInt c = a * b;
ASSERT_EQ(c.to_str(), "457313852169876");
}

TEST(mult, justmult2){
BigInt a(to_string(25));
BigInt b(to_string(39));
BigInt c = a * b;
ASSERT_EQ(c.to_str(), "975");
}

TEST(mult, multnegative){
BigInt a(to_string(-865653435));
BigInt b(to_string(-1264));
BigInt c = a * b;
ASSERT_EQ(c.to_str(), "1094185941840");
}

TEST(mult, multnegativepositive){
BigInt a(to_string(724235));
BigInt b(to_string(-6543));
BigInt c = a * b;
ASSERT_EQ(c.to_str(), "-4738669605");
}

TEST(mult, multbig){
string s = "100000000000000000000000000";
BigInt a(s);
BigInt b(s);
BigInt c = a * b;
ASSERT_EQ(c.to_str(), "10000000000000000000000000000000000000000000000000000");
}

TEST(mult, multdecimal){
BigInt a(to_string(0.235425));
BigInt b(to_string(0.00324));
BigInt c = a * b;
ASSERT_EQ(c.to_str(), "0.000762777");
}