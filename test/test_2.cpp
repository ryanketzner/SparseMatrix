#include "tjds.hpp"
#include "gtest/gtest.h"

TEST(TJDS,TestBuildTJDS)
{
    std::string file = "../input/test_1_tjds.mtx";

    TJDS<std::string> tjds(file);

    std::vector<std::string> expected_value_list({"a25","a12","a14","a46","a11",
                                                  "a23","a45","a22","a34","a56",
                                                  "a31","a33","a55","a42","a44",
                                                  "a66","a65"});
    EXPECT_EQ(tjds.value_list,expected_value_list);

    std::vector<int> expected_row_indices({1,0,0,3,0,1,3,1,2,4,2,2,4,3,3,5,5});
    EXPECT_EQ(tjds.row_indices,expected_row_indices);

    std::vector<int> expected_start_pos({0,6,12,16,17});
    EXPECT_EQ(tjds.start_position,expected_start_pos);

    std::vector<int> expected_permutation({4,1,3,5,0,2});
    EXPECT_EQ(tjds.permutation,expected_permutation);
}

TEST(TJDS, TestPermuteVector)
{
    std::string file = "../input/test_1_tjds.mtx";

    TJDS<std::string> tjds(file);
    std::vector<std::string> x({"1","2","3","4","5","6"});
    std::vector<std::string> permuted = tjds.get_permuted_vector(x);

    std::vector<std::string> expected({"5","2","4","6","1","3"});
    EXPECT_EQ(permuted,expected);
}

TEST(TJDS, TestMult)
{
    std::string file = "../input/test_1.mtx";
    TJDS<int> A(file);

    std::vector<int> x({1,2,3,4,5,6});
    std::vector<int> y = A*x;

    std::vector<int> expected_y({0,39,66,80,175,12});

    EXPECT_EQ(y,expected_y);
}

TEST(TJDS, TestMultiplyVector_1000)
{
    std::string file = "../input/test_1.mtx";
    TJDS<long> A(file);

    std::vector<long> x({1,2,3,4,5,6});

    const int exp = 1000;
    std::vector<long> y = A*x;
    for (int i = 0; i < exp-1; i++)
    {
        y = A*y;
    }

    std::vector<long> expected_y({-219034273575977048, 5322504499393071497, -7646502977385207889,
                                   3724247356017279656, -566243747678808860, 7259317634997531088});

    EXPECT_EQ(y,expected_y);
}


TEST(TJDS, TestPowVector_1000)
{
    std::string file = "../input/test_1.mtx";
    TJDS<long> A(file);

    std::vector<long> x({1,2,3,4,5,6});

    const int exp = 1000;
    std::vector<long> y = A.pow(x,exp);

    std::vector<long> expected_y({-219034273575977048, 5322504499393071497, -7646502977385207889,
                                   3724247356017279656, -566243747678808860, 7259317634997531088});

    EXPECT_EQ(y,expected_y);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}