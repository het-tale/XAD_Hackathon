#include <gtest/gtest.h>
#include "Matrix.hpp"

/**
 * @brief Test the default constructor of the Matrix class
 *
 * This test case verifies:
 * 1. The constructor correctly sets the number of rows and columns
 * 2. It works for both small and large dimensions
 * 3. All elements are initialized to 0
 * 4. It handles the edge case of a 0x0 matrix
 */
TEST(MatrixTest, DefaultConstructor)
{

    Matrix m1(2, 3);
    EXPECT_EQ(m1.getRows(), 2);
    EXPECT_EQ(m1.getCols(), 3);

    Matrix m2(100, 200);
    EXPECT_EQ(m2.getRows(), 100);
    EXPECT_EQ(m2.getCols(), 200);

    for (size_t i = 0; i < m1.getRows(); ++i)
    {
        for (size_t j = 0; j < m1.getCols(); ++j)
        {
            EXPECT_EQ(m1(i, j), 0.0);
        }
    }

    Matrix m3(0, 0);
    EXPECT_EQ(m3.getRows(), 0);
    EXPECT_EQ(m3.getCols(), 0);
}

/**
 * @brief Test the constructor of the Matrix class with initial value
 *
 * This test case verifies:
 * 1. The constructor correctly sets the number of rows and columns
 * 2. It works for both small and large dimensions
 * 3. All elements are initialized to the specified value
 * 4. It handles the edge case of a 0x0 matrix
 * 5. It works with different initial values (positive, negative, zero)
 */
TEST(MatrixTest, ConstructorWithInitialValue)
{

    Matrix m1(2, 3, 5.5);
    EXPECT_EQ(m1.getRows(), 2);
    EXPECT_EQ(m1.getCols(), 3);
    for (size_t i = 0; i < m1.getRows(); ++i)
    {
        for (size_t j = 0; j < m1.getCols(); ++j)
        {
            EXPECT_DOUBLE_EQ(m1(i, j), 5.5);
        }
    }

    Matrix m2(100, 200, -1.5);
    EXPECT_EQ(m2.getRows(), 100);
    EXPECT_EQ(m2.getCols(), 200);
    EXPECT_DOUBLE_EQ(m2(50, 100), -1.5);

    Matrix m3(5, 5, 0.0);
    EXPECT_EQ(m3.getRows(), 5);
    EXPECT_EQ(m3.getCols(), 5);
    EXPECT_DOUBLE_EQ(m3(2, 2), 0.0);

    Matrix m4(0, 0, 10.0);
    EXPECT_EQ(m4.getRows(), 0);
    EXPECT_EQ(m4.getCols(), 0);
}

/**
 * @brief Test the copy constructor of the Matrix class
 *
 * This test case verifies:
 * 1. The copy constructor creates a new matrix with the same dimensions
 * 2. All elements are correctly copied from the original matrix
 * 3. Modifying the copy doesn't affect the original matrix
 * 4. It works with matrices of different sizes and values
 * 5. It correctly handles empty matrices (0x0)
 */
TEST(MatrixTest, CopyConstructor)
{

    Matrix original(3, 4, 2.5);
    Matrix copy(original);

    EXPECT_EQ(copy.getRows(), original.getRows());
    EXPECT_EQ(copy.getCols(), original.getCols());

    for (size_t i = 0; i < original.getRows(); ++i)
    {
        for (size_t j = 0; j < original.getCols(); ++j)
        {
            EXPECT_DOUBLE_EQ(copy(i, j), original(i, j));
        }
    }

    copy(1, 1) = 10.0;
    EXPECT_DOUBLE_EQ(copy(1, 1), 10.0);
    EXPECT_DOUBLE_EQ(original(1, 1), 2.5);

    Matrix original2(2, 2);
    original2(0, 0) = 1.0;
    original2(0, 1) = 2.0;
    original2(1, 0) = 3.0;
    original2(1, 1) = 4.0;
    Matrix copy2(original2);

    for (size_t i = 0; i < original2.getRows(); ++i)
    {
        for (size_t j = 0; j < original2.getCols(); ++j)
        {
            EXPECT_DOUBLE_EQ(copy2(i, j), original2(i, j));
        }
    }

    Matrix emptyOriginal(0, 0);
    Matrix emptyCopy(emptyOriginal);
    EXPECT_EQ(emptyCopy.getRows(), 0);
    EXPECT_EQ(emptyCopy.getCols(), 0);
}

/**
 * @brief Test the assignment operator of the Matrix class
 *
 * This test case verifies:
 * 1. The assignment operator creates a new matrix with the same dimensions
 * 2. All elements are correctly copied from the original matrix
 * 3. Modifying the assigned matrix doesn't affect the original matrix
 * 4. It works with matrices of different sizes and values
 * 5. It correctly handles self-assignment
 * 6. It correctly handles empty matrices (0x0)
 */
TEST(MatrixTest, AssignmentOperator)
{
    Matrix original(3, 4, 2.5);
    Matrix assigned = original;

    EXPECT_EQ(assigned.getRows(), original.getRows());
    EXPECT_EQ(assigned.getCols(), original.getCols());

    for (size_t i = 0; i < original.getRows(); ++i)
    {
        for (size_t j = 0; j < original.getCols(); ++j)
        {
            EXPECT_DOUBLE_EQ(assigned(i, j), original(i, j));
        }
    }

    assigned(1, 1) = 10.0;
    EXPECT_DOUBLE_EQ(assigned(1, 1), 10.0);
    EXPECT_DOUBLE_EQ(original(1, 1), 2.5);

    Matrix original2(2, 2);
    original2(0, 0) = 1.0;
    original2(0, 1) = 2.0;
    original2(1, 0) = 3.0;
    original2(1, 1) = 4.0;
    Matrix assigned2 = original2;

    for (size_t i = 0; i < original2.getRows(); ++i)
    {
        for (size_t j = 0; j < original2.getCols(); ++j)
        {
            EXPECT_DOUBLE_EQ(assigned2(i, j), original2(i, j));
        }
    }

    Matrix emptyOriginal(0, 0);
    Matrix emptyAssigned = emptyOriginal;
    EXPECT_EQ(emptyAssigned.getRows(), 0);
    EXPECT_EQ(emptyAssigned.getCols(), 0);

    Matrix selfAssign(2, 2, 1.0);
    selfAssign = selfAssign;
    EXPECT_EQ(selfAssign.getRows(), 2);
    EXPECT_EQ(selfAssign.getCols(), 2);
    EXPECT_DOUBLE_EQ(selfAssign(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(selfAssign(1, 1), 1.0);

    Matrix existing(5, 5, 3.0);
    existing = original2;
    EXPECT_EQ(existing.getRows(), 2);
    EXPECT_EQ(existing.getCols(), 2);
    EXPECT_DOUBLE_EQ(existing(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(existing(1, 1), 4.0);
}

/**
 * @brief Test the move constructor of the Matrix class
 *
 * This test case verifies:
 * 1. The move constructor creates a new matrix with the same dimensions
 * 2. All elements are correctly moved from the original matrix
 * 3. The original matrix is left in a valid but unspecified state
 * 4. It works with matrices of different sizes and values
 * 5. It correctly handles empty matrices (0x0)
 */
TEST(MatrixTest, MoveConstructor)
{
    Matrix original(3, 4, 2.5);
    size_t originalRows = original.getRows();
    size_t originalCols = original.getCols();

    Matrix moved(std::move(original));

    EXPECT_EQ(moved.getRows(), originalRows);
    EXPECT_EQ(moved.getCols(), originalCols);

    for (size_t i = 0; i < moved.getRows(); ++i)
    {
        for (size_t j = 0; j < moved.getCols(); ++j)
        {
            EXPECT_DOUBLE_EQ(moved(i, j), 2.5);
        }
    }

    EXPECT_EQ(original.getRows(), 0);
    EXPECT_EQ(original.getCols(), 0);

    Matrix original2(2, 2);
    original2(0, 0) = 1.0;
    original2(0, 1) = 2.0;
    original2(1, 0) = 3.0;
    original2(1, 1) = 4.0;

    Matrix moved2(std::move(original2));

    EXPECT_EQ(moved2.getRows(), 2);
    EXPECT_EQ(moved2.getCols(), 2);
    EXPECT_DOUBLE_EQ(moved2(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(moved2(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(moved2(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(moved2(1, 1), 4.0);

    Matrix emptyOriginal(0, 0);
    Matrix emptyMoved(std::move(emptyOriginal));
    EXPECT_EQ(emptyMoved.getRows(), 0);
    EXPECT_EQ(emptyMoved.getCols(), 0);
}