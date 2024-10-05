#include <gtest/gtest.h>
#include "../include/Matrix.hpp"
#include "../include/MatrixView.hpp"
#include "../include/MatrixViewHelper.hpp"

/**
 * @brief Test the constructor of the MatrixViewHelper class
 *
 * This test case verifies:
 * 1. The constructor correctly initializes the MatrixViewHelper with a reference to a MatrixView
 * 2. The row and column indices are set correctly
 */
TEST(MatrixViewHelperTest, Constructor)
{
    Matrix matrix(2, 3);
    MatrixView view(matrix, 0, 0);
    MatrixViewHelper helper(view, 0, 1);

    helper = 5.0;
    EXPECT_DOUBLE_EQ(view.getValue(0, 1), 5.0);
}

/**
 * @brief Test the assignment operator of the MatrixViewHelper class
 *
 * This test case verifies:
 * 1. The assignment operator correctly updates the value in the MatrixView
 * 2. The underlying Matrix is also updated accordingly
 */
TEST(MatrixViewHelperTest, AssignmentOperator)
{
    Matrix matrix(2, 2, 1.0);
    MatrixView view(matrix, 0, 0);
    MatrixViewHelper helper(view, 0, 0);

    helper = 3.0;
    EXPECT_DOUBLE_EQ(view.getValue(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(matrix.getValue(0, 0), 3.0);
}

/**
 * @brief Test the assignment operator of the MatrixViewHelper class with multiple updates
 *
 * This test case verifies:
 * 1. The assignment operator correctly updates the value in the MatrixView multiple times
 * 2. The latest value is reflected in the MatrixView
 */
TEST(MatrixViewHelperTest, AssignmentOperatorMultipleUpdates)
{
    Matrix matrix(3, 3, 0.0);
    MatrixView view(matrix, 0, 0);
    MatrixViewHelper helper(view, 1, 1);

    helper = 2.0;
    EXPECT_DOUBLE_EQ(view.getValue(1, 1), 2.0);
    helper = 4.0;
    EXPECT_DOUBLE_EQ(view.getValue(1, 1), 4.0);
}


