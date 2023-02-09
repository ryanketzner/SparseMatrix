#include "sparse.hpp"
#include "gtest/gtest.h"

// TEST(SparseMatrixTest, TestMatrix1)
// {
//     std::string file = "/home/reno/Documents/UCF/sparse/test_1.mtx";
//     SparseMatrix<int> sparse_3(file);

//     sparse_3.printRowPtr();
// 	sparse_3.printColInd();
// 	sparse_3.printVals();
// }

TEST(SparseMatrixTest, TestMultiplyVector)
{
    std::string file = "/home/reno/Documents/UCF/sparse/test_1.mtx";
    SparseMatrix<int> A(file);

    std::vector<int> x({1,2,3,4,5,6});
    std::vector<int> y = A*x;

    std::vector<int> expected_y({0,39,66,80,175,12});

    EXPECT_EQ(y,expected_y);
}

TEST(SparseMatrixTest, TestPowVector)
{
    std::string file = "/home/reno/Documents/UCF/sparse/test_1.mtx";
    SparseMatrix<int> A(file);

    std::vector<int> x({1,2,3,4,5,6});
    std::vector<int> y = A.pow(x,1);

    std::vector<int> expected_y({0,39,66,80,175,12});

    EXPECT_EQ(y,expected_y);
}

TEST(SparseMatrixTest, TestMultiplyVector_1000)
{
    std::string file = "/home/reno/Documents/UCF/sparse/test_1.mtx";
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
    std::string file = "/home/reno/Documents/UCF/sparse/test_1.mtx";
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