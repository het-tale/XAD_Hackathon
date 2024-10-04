#include "../include/MatrixView.hpp"
#include <cmath>
#include "../include/Matrix.hpp"
#include <stdexcept>





MatrixView::MatrixView(Matrix& matrix, size_t row, size_t col)
    : matrix(matrix), row(row), col(col), matrix_ptr(matrix.getMatrix()), sumComputed(false), sum(0), cols(1), rows(1), startRow(row), startCol(col) {

        // Construct a view of a single element
        // std::cout << GREEN << "MatrixView(Matrix& matrix, size_t row, size_t col) called" << DEFAULT   << std::endl;
}

MatrixView::MatrixView(Matrix& matrix, size_t startRow, size_t startCol, size_t num_rows, size_t num_cols)
    : matrix(matrix), rows(num_rows), cols(num_cols), startRow(startRow), startCol(startCol) {

    matrix_ptr = matrix.getMatrix();
    
    if (startRow + rows > matrix.getRows() || startCol + cols > matrix.getCols()) {
        throw std::out_of_range("MatrixView dimensions exceed matrix bounds");
    }
    sumComputed = false;
    sum = 0;
    // std::cout << GREEN << "MatrixView(Matrix& matrix, size_t startRow, size_t startCol, size_t num_rows, size_t num_cols) called" << DEFAULT   << std::endl;
}

MatrixView::MatrixView(const MatrixView& other)
    : matrix(other.matrix), rows(other.rows), cols(other.cols), startRow(other.startRow), startCol(other.startCol) {
    // Copy constructor
    sumComputed = other.sumComputed;
    sum = other.sum;
    // std::cout << GREEN << "MatrixView(const MatrixView& other) called" << DEFAULT   << std::endl;
}





MatrixView& MatrixView::operator=(const MatrixView& other) {
    if (this != &other) {
        this->matrix = other.matrix;
        this->rows = other.rows;
        this->cols = other.cols;
        this->startRow = other.startRow;
        this->startCol = other.startCol;
    }
    // std::cout << GREEN << "MatrixView& MatrixView::operator=(const MatrixView& other) called" << DEFAULT   << std::endl;
    return (*this);
}

MatrixView& MatrixView::operator=(double value) {

		double d = matrix.get(row, col);
		matrix.setSum(matrix.getSum() - pow(d, 2) + pow(value, 2));
        sum = sum - pow(d, 2) + pow(value, 2);
        matrix.set(row, col, value);
        return *this;
}


MatrixView::MatrixView(MatrixView&& other)
    : matrix(other.matrix), rows(other.rows), cols(other.cols), startRow(other.startRow), startCol(other.startCol) {
    // Move constructor
    other.sumComputed = false;
    other.sum = 0;
    other.rows = 0;
    other.cols = 0;
    other.startRow = 0;
    other.startCol = 0;
    // std::cout << GREEN << "MatrixView(MatrixView&& other) called" << DEFAULT   << std::endl;
}

MatrixView& MatrixView::operator=(MatrixView&& other) {
    if (this != &other) {
        this->matrix = other.matrix;
        this->rows = other.rows;
        this->cols = other.cols;
        this->startRow = other.startRow;
        this->startCol = other.startCol;
    }
    // std::cout << GREEN << "MatrixView& MatrixView::operator=(MatrixView&& other) called" << DEFAULT   << std::endl;
    return *this;
}

MatrixView::~MatrixView() {
    // No dynamic allocation, so nothing to clean up
    // std::cout << RED << "MatrixView::~MatrixView() called" << DEFAULT   << std::endl;
}

size_t MatrixView::getRows() const {
    return rows;
}

size_t MatrixView::getCols() const {
    return cols;
}

size_t MatrixView::getStartRow() const {
    return startRow;
}

size_t MatrixView::getStartCol() const {
    return startCol;
}

double MatrixView::getValue(size_t row, size_t col) const
{
    return matrix_ptr[row + startRow][col + startCol];
}






/*
    Overload the () operator to access elements of the matrix

    THE MatrixViewHelper is a helper class to have controll on the assignment and have access to the assigned value  to update the sum
    const double& operator()(size_t row, size_t col) const; // for const object no need for helper class since we won't update the values
*/
MatrixViewHelper MatrixView::operator()(size_t row, size_t col) {
    
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Index out of range");
    }
    return MatrixViewHelper(*this, row, col);
}


const double& MatrixView::operator()(size_t row, size_t col) const {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Index out of range");
    }

    return matrix_ptr[startRow + row][startCol + col];
}



void MatrixView::updateValueAndSum(double value, size_t row, size_t col)
{
    double d = matrix_ptr[row + startRow][col + startCol];
    sum = sum - pow(d, 2) + pow(value, 2);
    matrix_ptr[row + startRow][col + startCol] = value;
}


void MatrixView::setValue(size_t row, size_t col, double value)
{
    matrix_ptr[row + startRow][col + startCol] = value;
}







MatrixView::operator Matrix() const {
        Matrix tmp(this->getRows(), this->getCols());
        for (size_t i = 0; i < this->getRows(); ++i) {
            for (size_t j = 0; j < this->getCols(); ++j) {
                tmp(i, j) = (*this)(i, j); // Copy elements from view
            }
        }
        return tmp;
}

MatrixView::operator double() const {
        return matrix.get(row, col);
}

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
