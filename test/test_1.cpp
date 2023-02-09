#include "sparse.hpp"
#include "gtest/gtest.h"

TEST(SparseMatrixTest, TestSetup)
{
    std::string file = "../input/test_1.mtx";
    SparseMatrix<int> A(file);

    std::vector<int> row_ptr = A.getRowPtr();
    std::vector<int> col_ind = A.getColInd();

    std::vector<int> expected_row_ptr({0,2,5,8,12,16,19});
    std::vector<int> expected_col_ind({0,4,0,1,5,1,2,3,0,2,3,4,1,3,4,5,1,4,5});

    EXPECT_EQ(expected_row_ptr,row_ptr);
    EXPECT_EQ(expected_col_ind,col_ind);
}

TEST(SparseMatrixTest, TestMultiplyVector)
{
    std::string file = "../input/test_1.mtx";
    SparseMatrix<int> A(file);

    std::vector<int> x({1,2,3,4,5,6});
    std::vector<int> y = A*x;

    std::vector<int> expected_y({0,39,66,80,175,12});

    EXPECT_EQ(y,expected_y);
}

TEST(SparseMatrixTest, TestPowVector)
{
    std::string file = "../input/test_1.mtx";
    SparseMatrix<int> A(file);

    std::vector<int> x({1,2,3,4,5,6});
    std::vector<int> y = A.pow(x,1);

    std::vector<int> expected_y({0,39,66,80,175,12});

    EXPECT_EQ(y,expected_y);
}

TEST(SparseMatrixTest, TestMultiplyVector_1000)
{
    std::string file = "../input/test_1.mtx";
    SparseMatrix<long> A(file);

    std::vector<long> x({1,2,3,4,5,6});

    int exp = 1000;
    std::vector<long> y = A*x;
    for (int i = 0; i < exp-1; i++)
    {
        y = A*y;
    }

    std::vector<long> expected_y({-219034273575977048, 5322504499393071497, -7646502977385207889,
                                   3724247356017279656, -566243747678808860, 7259317634997531088});

    EXPECT_EQ(y,expected_y);
}


TEST(SparseMatrixTest, TestPowVector_1000)
{
    std::string file = "../input/test_1.mtx";
    SparseMatrix<long> A(file);

    std::vector<long> x({1,2,3,4,5,6});

    int exp = 1000;
    std::vector<long> y = A.pow(x,exp);

    std::vector<long> expected_y({-219034273575977048, 5322504499393071497, -7646502977385207889,
                                   3724247356017279656, -566243747678808860, 7259317634997531088});

    EXPECT_EQ(y,expected_y);
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}