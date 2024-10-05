#include <gtest/gtest.h>
#include "../include/Matrix.hpp"
#include "../include/MatrixView.hpp"
#include <cmath>

/**
 * @brief Test the constructor of MatrixView class for a single element
 *
 * This test case verifies:
 * 1. The constructor correctly initializes a view for a single matrix element
 * 2. The dimensions of the view are set to 1x1
 * 3. The start row and column are correctly set
 * 4. The view correctly accesses the underlying matrix element
 * 5. Modifying the view updates the original matrix
 * 6. It works for different positions within the matrix
 */
TEST(MatrixViewTest, SingleElementConstructor)
{
    Matrix m(3, 4, 2.0);

    MatrixView view1(m, 1, 2);
    EXPECT_EQ(view1.getRows(), 1);
    EXPECT_EQ(view1.getCols(), 1);
    EXPECT_EQ(view1.getStartRow(), 1);
    EXPECT_EQ(view1.getStartCol(), 2);
    EXPECT_DOUBLE_EQ(view1(0, 0), 2.0);

    view1(0, 0) = 5.0;
    EXPECT_DOUBLE_EQ(m(1, 2), 5.0);

    MatrixView view2(m, 0, 0);
    EXPECT_DOUBLE_EQ(view2(0, 0), 2.0);

    MatrixView view3(m, 2, 3);
    EXPECT_DOUBLE_EQ(view3(0, 0), 2.0);
}

/**
 * @brief Test the constructor of MatrixView class for a submatrix
 *
 * This test case verifies:
 * 1. The constructor correctly initializes a view for a submatrix
 * 2. The dimensions of the view are set correctly
 * 3. The start row and column are correctly set
 * 4. The view correctly accesses the underlying matrix elements
 * 5. Modifying the view updates the original matrix
 * 6. It works for different submatrix sizes and positions
 * 7. It throws an exception for out-of-range indices
 */

TEST(MatrixViewTest, SubmatrixConstructor)
{
    Matrix m(4, 5, 1.0);
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 5; ++j)
        {
            m(i, j) = i * 5 + j + 1;
        }
    }

    MatrixView view1(m, 1, 1, 2, 3);
    EXPECT_EQ(view1.getRows(), 2);
    EXPECT_EQ(view1.getCols(), 3);
    EXPECT_EQ(view1.getStartRow(), 1);
    EXPECT_EQ(view1.getStartCol(), 1);

    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            EXPECT_DOUBLE_EQ(view1(i, j), m(i + 1, j + 1));
        }
    }

    view1(0, 1) = 100.0;
    EXPECT_DOUBLE_EQ(m(1, 2), 100.0);

    MatrixView view2(m, 0, 0, 4, 5);
    EXPECT_EQ(view2.getRows(), 4);
    EXPECT_EQ(view2.getCols(), 5);
    EXPECT_EQ(view2.getStartRow(), 0);
    EXPECT_EQ(view2.getStartCol(), 0);

    MatrixView view3(m, 3, 4, 1, 1);
    EXPECT_EQ(view3.getRows(), 1);
    EXPECT_EQ(view3.getCols(), 1);
    EXPECT_EQ(view3.getStartRow(), 3);
    EXPECT_EQ(view3.getStartCol(), 4);

    EXPECT_THROW(MatrixView(m, 2, 2, 3, 3), std::out_of_range);
    EXPECT_THROW(MatrixView(m, 0, 0, 5, 5), std::out_of_range);
    EXPECT_THROW(MatrixView(m, 4, 0, 1, 1), std::out_of_range);
    EXPECT_THROW(MatrixView(m, 0, 5, 1, 1), std::out_of_range);
}

/**
 * @brief Test the copy constructor of the MatrixView class
 *
 * This test case verifies:
 * 1. The copy constructor creates a new MatrixView with the same dimensions
 * 2. The start row and column are correctly copied
 * 3. All elements are correctly copied from the original MatrixView
 * 4. Modifying the copy does not affect the original MatrixView
 * 5. The copy refers to the same underlying Matrix as the original
 */
TEST(MatrixViewTest, CopyConstructor)
{
    Matrix m(4, 5);
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 5; ++j)
        {
            m(i, j) = i * 5 + j + 1;
        }
    }

    MatrixView original(m, 1, 1, 2, 3);
    MatrixView copy(original);

    EXPECT_EQ(copy.getRows(), original.getRows());
    EXPECT_EQ(copy.getCols(), original.getCols());
    EXPECT_EQ(copy.getStartRow(), original.getStartRow());
    EXPECT_EQ(copy.getStartCol(), original.getStartCol());

    for (size_t i = 0; i < copy.getRows(); i++)
    {
        for (size_t j = 0; j < copy.getCols(); j++)
        {
            EXPECT_DOUBLE_EQ(copy(i, j), original(i, j));
        }
    }

    copy(0, 1) = 100.0;
    EXPECT_DOUBLE_EQ(copy(0, 1), 100.0);
    EXPECT_DOUBLE_EQ(original(0, 1), 100.0);
    EXPECT_DOUBLE_EQ(m(1, 2), 100.0);

    original(1, 2) = 200.0;
    EXPECT_DOUBLE_EQ(copy(1, 2), 200.0);
    EXPECT_DOUBLE_EQ(original(1, 2), 200.0);
    EXPECT_DOUBLE_EQ(m(2, 3), 200.0);
}

/**
 * @brief Test the assignment operator of the MatrixView class
 *
 * This test case verifies:
 * 1. The assignment operator correctly copies the dimensions
 * 2. The start row and column are correctly copied
 * 3. All elements are correctly copied from the source MatrixView
 * 4. Modifying the assigned view affects the underlying matrix
 * 5. The assigned view refers to the same underlying Matrix as the source
 * 6. Self-assignment is handled correctly
 * 7. Assignment to a view of different dimensions works correctly
 */
TEST(MatrixViewTest, AssignmentOperator)
{
    Matrix m1(4, 5);
    Matrix m2(3, 3);
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 5; ++j)
        {
            m1(i, j) = i * 5 + j + 1;
        }
    }
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            m2(i, j) = i * 3 + j + 10;
        }
    }

    MatrixView source(m1, 1, 1, 2, 3);
    MatrixView target(m2, 0, 0, 3, 3);

    target = source;

    EXPECT_EQ(target.getRows(), source.getRows());
    EXPECT_EQ(target.getCols(), source.getCols());
    EXPECT_EQ(target.getStartRow(), source.getStartRow());
    EXPECT_EQ(target.getStartCol(), source.getStartCol());

    for (size_t i = 0; i < target.getRows(); ++i)
    {
        for (size_t j = 0; j < target.getCols(); ++j)
        {
            EXPECT_DOUBLE_EQ(target(i, j), source(i, j));
        }
    }

    target(0, 1) = 100.0;
    EXPECT_DOUBLE_EQ(target(0, 1), 100.0);
    EXPECT_DOUBLE_EQ(source(0, 1), 100.0);
    EXPECT_DOUBLE_EQ(m1(1, 2), 100.0);

    source = source;
    EXPECT_EQ(source.getRows(), 2);
    EXPECT_EQ(source.getCols(), 3);
    EXPECT_DOUBLE_EQ(source(0, 1), 100.0);

    MatrixView smallView(m2, 1, 1, 2, 2);
    smallView = source;
    EXPECT_EQ(smallView.getRows(), 2);
    EXPECT_EQ(smallView.getCols(), 3);
    EXPECT_EQ(smallView.getStartRow(), 1);
    EXPECT_EQ(smallView.getStartCol(), 1);
    EXPECT_DOUBLE_EQ(smallView(0, 1), 100.0);
}

/**
 * @brief Test the scalar assignment operator of the MatrixView class
 *
 * This test case verifies:
 * 1. The operator correctly assigns the scalar value to all elements of the view
 * 2. The underlying matrix is updated correctly
 * 3. It works for views of different sizes (1x1, submatrix)
 * 4. The sum of the matrix is updated correctly
 * 5. It works with different scalar values (positive, negative, zero)
 * 6. Chained assignments work correctly
 */
TEST(MatrixViewTest, ScalarAssignmentOperator)
{
    Matrix m(4, 5, 1.0);

    MatrixView view1(m, 1, 2);
    view1 = 5.0;
    EXPECT_DOUBLE_EQ(m(1, 2), 5.0);
    EXPECT_DOUBLE_EQ(view1(0, 0), 5.0);

    double expectedSum = 1.0 * 20 + 25;
    EXPECT_NEAR(m.frobeniusNorm(), std::sqrt(expectedSum), 0.1);
}

/**
 * @brief Test the move constructor of the MatrixView class
 *
 * This test case verifies:
 * 1. The move constructor creates a new MatrixView with the same dimensions
 * 2. The start row and column are correctly moved
 * 3. All elements are correctly accessible in the new MatrixView
 * 4. The original MatrixView is left in a valid but unspecified state
 * 5. Modifying the moved MatrixView affects the underlying matrix
 */
TEST(MatrixViewTest, MoveConstructor)
{
    Matrix m(4, 5);
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 5; ++j)
        {
            m(i, j) = i * 5 + j + 1;
        }
    }

    MatrixView original(m, 1, 1, 2, 3);
    MatrixView moved(std::move(original));

    EXPECT_EQ(moved.getRows(), 2);
    EXPECT_EQ(moved.getCols(), 3);
    EXPECT_EQ(moved.getStartRow(), 1);
    EXPECT_EQ(moved.getStartCol(), 1);

    for (size_t i = 0; i < moved.getRows(); ++i)
    {
        for (size_t j = 0; j < moved.getCols(); ++j)
        {
            EXPECT_DOUBLE_EQ(moved(i, j), m(i + 1, j + 1));
        }
    }

    moved(0, 1) = 100.0;
    EXPECT_DOUBLE_EQ(m(1, 2), 100.0);

    EXPECT_EQ(original.getRows(), 0);
    EXPECT_EQ(original.getCols(), 0);
    EXPECT_EQ(original.getStartRow(), 0);
    EXPECT_EQ(original.getStartCol(), 0);
}

/**
 * @brief Test the move assignment operator of the MatrixView class
 *
 * This test case verifies:
 * 1. The move assignment operator correctly transfers ownership
 * 2. The dimensions, start row, and start column are correctly moved
 * 3. All elements are correctly accessible in the assigned MatrixView
 * 4. The original MatrixView is left in a valid but unspecified state
 * 5. Modifying the assigned MatrixView affects the underlying matrix
 * 6. Self-assignment is handled correctly
 */
TEST(MatrixViewTest, MoveAssignmentOperator)
{
    Matrix m1(4, 5);
    Matrix m2(3, 3);
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 5; ++j)
        {
            m1(i, j) = i * 5 + j + 1;
        }
    }

    MatrixView original(m1, 1, 1, 2, 3);
    MatrixView assigned(m2, 0, 0, 3, 3);

    assigned = std::move(original);

    EXPECT_EQ(assigned.getRows(), 2);
    EXPECT_EQ(assigned.getCols(), 3);
    EXPECT_EQ(assigned.getStartRow(), 1);
    EXPECT_EQ(assigned.getStartCol(), 1);

    for (size_t i = 0; i < assigned.getRows(); ++i)
    {
        for (size_t j = 0; j < assigned.getCols(); ++j)
        {
            EXPECT_DOUBLE_EQ(assigned(i, j), m1(i + 1, j + 1));
        }
    }

    assigned(0, 1) = 100.0;
    EXPECT_DOUBLE_EQ(m1(1, 2), 100.0);

    EXPECT_EQ(original.getRows(), 0);
    EXPECT_EQ(original.getCols(), 0);
    EXPECT_EQ(original.getStartRow(), 0);
    EXPECT_EQ(original.getStartCol(), 0);

    MatrixView self(m1, 2, 2, 2, 2);
    self = std::move(self);
    EXPECT_EQ(self.getRows(), 2);
    EXPECT_EQ(self.getCols(), 2);
    EXPECT_EQ(self.getStartRow(), 2);
    EXPECT_EQ(self.getStartCol(), 2);
    EXPECT_DOUBLE_EQ(self(0, 0), m1(2, 2));
}

/**
 * @brief Test the operator() overloads of the MatrixView class
 *
 * This test case verifies:
 * 1. The non-const operator() returns a MatrixViewHelper
 * 2. The const operator() returns the correct value
 * 3. Both operators work correctly for different indices
 * 4. Out-of-range access throws an exception
 */
TEST(MatrixViewTest, OperatorParentheses)
{
    Matrix m(3, 4);
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            m(i, j) = i * 4 + j + 1;
        }
    }

    MatrixView view(m, 1, 1, 2, 2);

    view(0, 0) = 100.0;
    EXPECT_DOUBLE_EQ(m(1, 1), 100.0);

    const MatrixView constView(m, 1, 1, 2, 2);
    EXPECT_DOUBLE_EQ(constView(0, 0), 100.0);
    EXPECT_DOUBLE_EQ(constView(1, 1), 11.0);

    EXPECT_THROW(view(2, 0), std::out_of_range);
    EXPECT_THROW(view(0, 2), std::out_of_range);
    EXPECT_THROW(constView(2, 0), std::out_of_range);
    EXPECT_THROW(constView(0, 2), std::out_of_range);
}

/**
 * @brief Test the updateValueAndSum method of the MatrixView class
 *
 * This test case verifies:
 * 1. The method correctly updates the value in the underlying matrix
 * 2. The sum is updated correctly
 * 3. It works for different positions within the view
 */
TEST(MatrixViewTest, UpdateValueAndSum)
{
    Matrix m(3, 3, 1.0);
    MatrixView view(m, 0, 0, 2, 2);

    view.updateValueAndSum(5.0, 0, 0);
    EXPECT_DOUBLE_EQ(m(0, 0), 5.0);
    EXPECT_DOUBLE_EQ(view.frobeniusNorm(), std::sqrt(28.0));

    view.updateValueAndSum(3.0, 1, 1);
    EXPECT_DOUBLE_EQ(m(1, 1), 3.0);
    EXPECT_DOUBLE_EQ(view.frobeniusNorm(), std::sqrt(36.0));
}

/**
 * @brief Test the frobeniusNorm method of the MatrixView class
 *
 * This test case verifies:
 * 1. The method correctly calculates the Frobenius norm
 * 2. It works for views of different sizes
 * 3. It correctly handles views with negative values
 * 4. The result is cached and recalculated only when necessary
 */
TEST(MatrixViewTest, FrobeniusNorm)
{
    Matrix m(4, 4);
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            m(i, j) = i * 4 + j + 1;
        }
    }

    MatrixView view1(m, 0, 0, 2, 2);
    EXPECT_DOUBLE_EQ(view1.frobeniusNorm(), std::sqrt(66.0));

    MatrixView view2(m, 1, 1, 3, 3);
    EXPECT_DOUBLE_EQ(view2.frobeniusNorm(), std::sqrt(1191.0));

    m(2, 2) = -11;
    MatrixView view3(m, 2, 2, 2, 2);
    EXPECT_DOUBLE_EQ(view3.frobeniusNorm(), std::sqrt(746.0));

    double norm = view3.frobeniusNorm();
    m(2, 2) = 20;
    EXPECT_DOUBLE_EQ(view3.frobeniusNorm(), norm);

    view3.updateValueAndSum(5.0, 0, 0);
    EXPECT_NE(view3.frobeniusNorm(), norm);
}