#include "../include/MatrixView.hpp"
#include <cmath>
#include "../include/Matrix.hpp"
#include <stdexcept>

/**
 * @brief Constructor for MatrixView with single element
 *
 * This constructor creates a view of a single element in the matrix.
 */
MatrixView::MatrixView(Matrix &matrix, size_t row, size_t col)
    : matrix(matrix), row(row), col(col), matrix_ptr(matrix.getMatrix()), sumComputed(false), sum(0), cols(1), rows(1), startRow(row), startCol(col)
{
}

/**
 * @brief Constructor for MatrixView with multiple elements
 *
 * This constructor creates a view of a submatrix within the original matrix.
 * It throws an out_of_range exception if the view dimensions exceed the matrix bounds.
 */
MatrixView::MatrixView(Matrix &matrix, size_t startRow, size_t startCol, size_t num_rows, size_t num_cols)
    : matrix(matrix), rows(num_rows), cols(num_cols), startRow(startRow), startCol(startCol)
{
    matrix_ptr = matrix.getMatrix();
    row = 0;
    col = 0;

    if (startRow + rows > matrix.getRows() || startCol + cols > matrix.getCols())
    {
        throw std::out_of_range("MatrixView dimensions exceed matrix bounds");
    }
    sumComputed = false;
    sum = 0;
}

/**
 * @brief Copy constructor for MatrixView
 *
 * This constructor creates a new MatrixView by copying an existing one.
 */
MatrixView::MatrixView(const MatrixView &other)
    : matrix(other.matrix), rows(other.rows), cols(other.cols), startRow(other.startRow), startCol(other.startCol)
{
    sumComputed = other.sumComputed;
    matrix_ptr = other.matrix_ptr;
    sum = other.sum;
}

/**
 * @brief Assignment operator for MatrixView
 *
 * This operator assigns the contents of one MatrixView to another.
 */
MatrixView &MatrixView::operator=(const MatrixView &other)
{
    if (this != &other)
    {
        this->matrix = other.matrix;
        this->rows = other.rows;
        this->cols = other.cols;
        this->startRow = other.startRow;
        this->startCol = other.startCol;
        this->matrix_ptr = other.matrix_ptr;
    }
    return (*this);
}

/**
 * @brief Assignment operator for assigning a scalar value to a MatrixView
 *
 * This operator assigns a scalar value to the MatrixView and updates the sum.
 */
MatrixView &MatrixView::operator=(double value)
{
    double d = matrix.getValue(row, col);
    matrix.setSum(matrix.getSum() - pow(d, 2) + pow(value, 2));
    sum = sum - pow(d, 2) + pow(value, 2);
    matrix.setValue(row, col, value);
    return *this;
}

/**
 * @brief Move constructor for MatrixView
 *
 * This constructor moves the contents of one MatrixView to a new one.
 */
MatrixView::MatrixView(MatrixView &&other)
    : matrix(other.matrix), rows(other.rows), cols(other.cols), startRow(other.startRow), startCol(other.startCol)
{
    matrix_ptr = other.matrix_ptr;
    other.sumComputed = false;
    other.matrix_ptr = nullptr;
    other.sum = 0;
    other.rows = 0;
    other.cols = 0;
    other.startRow = 0;
    other.startCol = 0;
    row = 0;
    col = 0;
}

/**
 * @brief Move assignment operator for MatrixView
 *
 * This operator moves the contents of one MatrixView to another.
 */
MatrixView &MatrixView::operator=(MatrixView &&other)
{
    if (this != &other)
    {
        this->matrix = other.matrix;
        this->rows = other.rows;
        this->matrix_ptr = std::move(other.matrix_ptr);
        this->cols = other.cols;
        this->startRow = other.startRow;
        this->startCol = other.startCol;

        other.rows = 0;
        other.cols = 0;
        other.startRow = 0;
        other.startCol = 0;
    }
    return *this;
}

/**
 * @brief Destructor for MatrixView
 *
 * This destructor cleans up the MatrixView object.
 */
MatrixView::~MatrixView()
{
}

size_t MatrixView::getRows() const
{
    return rows;
}

size_t MatrixView::getCols() const
{
    return cols;
}

size_t MatrixView::getStartRow() const
{
    return startRow;
}

size_t MatrixView::getStartCol() const
{
    return startCol;
}

double MatrixView::getValue(size_t row, size_t col) const
{
    return matrix_ptr[row + startRow][col + startCol];
}

/**
 * @brief Overloaded () operator for non-const MatrixView
 *
 * This operator returns a MatrixViewHelper object for element access and modification.
 * It throws an out_of_range exception for invalid indices.
 */
MatrixViewHelper MatrixView::operator()(size_t row, size_t col)
{
    if (row >= rows || col >= cols)
    {
        throw std::out_of_range("Index out of range");
    }
    return MatrixViewHelper(*this, row, col);
}

/**
 * @brief Overloaded () operator for const MatrixView
 *
 * This operator returns a const reference to the element at the specified position.
 * It throws an out_of_range exception for invalid indices.
 */
const double &MatrixView::operator()(size_t row, size_t col) const
{
    if (row >= rows || col >= cols)
    {
        throw std::out_of_range("Index out of range");
    }
    return matrix_ptr[startRow + row][startCol + col];
}

/**
 * @brief Update the value and sum of the MatrixView
 *
 * This method updates the value at the specified position and recalculates the sum.
 */
void MatrixView::updateValueAndSum(double value, size_t row, size_t col)
{
    double d = matrix_ptr[row + startRow][col + startCol];
    sum = sum - pow(d, 2) + pow(value, 2);
    matrix_ptr[row + startRow][col + startCol] = value;
}

/**
 * @brief Set the value at a specific position in the MatrixView
 *
 * This method sets the value at the specified position without updating the sum.
 */
void MatrixView::setValue(size_t row, size_t col, double value)
{
    matrix_ptr[row + startRow][col + startCol] = value;
}

/**
 * @brief Convert MatrixView to Matrix
 *
 * This operator creates a new Matrix object from the MatrixView.
 */
MatrixView::operator Matrix() const
{
    Matrix tmp(this->getRows(), this->getCols());
    for (size_t i = 0; i < this->getRows(); ++i)
    {
        for (size_t j = 0; j < this->getCols(); ++j)
        {
            tmp(i, j) = (*this)(i, j);
        }
    }
      // std::cout << tmp(2,3) << std::endl;
        tmp.setSum((this)->sum);
        tmp.setSumComputed(this->sumComputed);
    return tmp;
}

/**
 * @brief Convert MatrixView to double
 *
 * This operator returns the value of the single element in the MatrixView.
 */
MatrixView::operator double() const
{
    return matrix.getValue(row, col);
}

/**
 * @brief Calculate the Frobenius norm of the MatrixView
 *
 * This method calculates and returns the Frobenius norm of the MatrixView.
 */


// MatrixView::operator double() const {
//         return matrix.get(row, col);
// }

double MatrixView::frobeniusNorm() const {
    if (!sumComputed) {
        sum = 0;
        for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    sum += std::pow((*this)(i, j), 2);
                }
            }
        sumComputed = true;
    }
    return std::sqrt(sum);
}