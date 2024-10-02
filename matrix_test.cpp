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
TEST(MatrixTest, DefaultConstructor) {
    // Test with small dimensions
    Matrix m1(2, 3);
    EXPECT_EQ(m1.getRows(), 2);
    EXPECT_EQ(m1.getCols(), 3);

    // Test with larger dimensions
    Matrix m2(100, 200);
    EXPECT_EQ(m2.getRows(), 100);
    EXPECT_EQ(m2.getCols(), 200);

    // Test that all elements are initialized to 0
    for (size_t i = 0; i < m1.getRows(); ++i) {
        for (size_t j = 0; j < m1.getCols(); ++j) {
            EXPECT_EQ(m1(i, j), 0.0);
        }
    }

    // Test constructor with 0x0 dimensions
    Matrix m3(0, 0);
    EXPECT_EQ(m3.getRows(), 0);
    EXPECT_EQ(m3.getCols(), 0);
}