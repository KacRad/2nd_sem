#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <cmath>
#include "delta.h"

using namespace testing;

class TestDelta : public Test{
public:
    Delta Obj_Delta;
};

TEST_F(TestDelta, check_if_delta_is_greater_than_0){
    double in_a = 3;
    double in_b = 6;
    double in_c = 2;
    double border_val = 0;

    double ret = Obj_Delta.delta_equation(in_a, in_b, in_c);
    ASSERT_GT(ret, border_val);
}

TEST_F(TestDelta, check_if_delta_is_equal_to_0){
    double in_a = 1;
    double in_b = 6;
    double in_c = 9;
    double expected_val = 0;

    double ret = Obj_Delta.delta_equation(in_a, in_b, in_c);
    ASSERT_EQ(ret, expected_val);
}

TEST_F(TestDelta, check_if_delta_is_lesser_than_0){
    double in_a = 3;
    double in_b = 2;
    double in_c = 1;
    double border_val = 0;

    double ret = Obj_Delta.delta_equation(in_a, in_b, in_c);
    ASSERT_LT(ret, border_val);
}

TEST_F(TestDelta, in_1_6_9_out_neg_3){
    double in_a = 1;
    double in_b = 6;
    double in_c = 9;
    double expect_val = -3;

    double ret = Obj_Delta.solution(in_a, in_b, in_c);
    EXPECT_EQ(ret, expect_val);
}


TEST_F(TestDelta, in_3_6_2_out_neg_1_5773502691896255){
    double in_a = 3;
    double in_b = 6;
    double in_c = 2;
    double expect_val = -1.5773502691896255;

    double ret = Obj_Delta.solution(in_a, in_b, in_c);
    ASSERT_DOUBLE_EQ(ret, expect_val);
}

TEST_F(TestDelta, in_3_2_1_out_exception){
    double in_a = 3;
    double in_b = 2;
    double in_c = 1;

    EXPECT_ANY_THROW(Obj_Delta.solution(in_a, in_b, in_c););
}
