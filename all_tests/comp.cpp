#include "../BigInt/BigInt.h"
#include <gtest/gtest.h>

TEST(comp, justcomp){
    BigInt a(to_string(132423467823432));
    BigInt b(to_string(132423467823432));
    bool c = (a == b);
    ASSERT_EQ(c, true);
}

TEST(comp, compbelow){
    BigInt a(to_string(0.000045));
    BigInt b(to_string(0.0000000001));
    bool c = (a < b);
    ASSERT_EQ(c, false);
}

TEST(comp, compabove){
    BigInt a(to_string(0.000045));
    BigInt b(to_string(0.000045));
    bool c = (a >= b);
    ASSERT_EQ(c, true);
}

TEST(comp, compnegativeandpositive){
    BigInt a(to_string(-0.000045));
    BigInt b(to_string(0.000045));
    bool c = (a == b);
    ASSERT_EQ(c, false);
}

TEST(comp, longcomp){
    BigInt a(to_string(0.000000000000000000000000000000000001));
    BigInt b(to_string(0.000000000000000000000000000000000001));
    bool c = (a == b);
    ASSERT_EQ(c, true);
}
