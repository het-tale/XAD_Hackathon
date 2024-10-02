#include "MatrixView.hpp"
#include <stdexcept>

MatrixView::MatrixView(Matrix& matrix, size_t startRow, size_t startCol, size_t num_rows, size_t num_cols)
    : matrix(matrix), rows(num_rows), cols(num_cols), startRow(startRow), startCol(startCol) {
    if (startRow + rows > matrix.getRows() || startCol + cols > matrix.getCols()) {
        std::cout << "num_rows  " << rows  << " matrix.getRows(): " << matrix.getRows() << std::endl;
        std::cout << "num_cols  " << cols  << " matrix.getCols(): " << matrix.getCols() << std::endl;
        std::cout << "startRow  " << startRow  << " matrix.getRows(): " << matrix.getRows() << std::endl;
        std::cout << "startCol  " << startCol  << " matrix.getCols(): " << matrix.getCols() << std::endl;
        std::cout << "startCol + num_cols: " << startCol + num_cols << std::endl;
        std::cout << "startRow + num_rows: " << startRow + num_rows << std::endl;
        std::cout << "MatrixView dimensions exceed matrix bounds" << std::endl;
        throw std::out_of_range("MatrixView dimensions exceed matrix bounds");
    }
    sumComputed = false;
    sum = 0;
}

MatrixView::MatrixView(const MatrixView& other)
    : matrix(other.matrix), rows(other.rows), cols(other.cols), startRow(other.startRow), startCol(other.startCol) {
    // Copy constructor
    sumComputed = other.sumComputed;
    sum = other.sum;
}

MatrixView& MatrixView::operator=(const MatrixView& other) {
    if (this != &other) {
        this->matrix = other.matrix;
        this->rows = other.rows;
        this->cols = other.cols;
        this->startRow = other.startRow;
        this->startCol = other.startCol;
    }
}

MatrixView::MatrixView(MatrixView&& other)
    : matrix(other.matrix), rows(other.rows), cols(other.cols), startRow(other.startRow), startCol(other.startCol) {
    // Move constructor
    // other.matrix = nullptr;
    other.rows = 0;
    other.cols = 0;
    other.startRow = 0;
    other.startCol = 0;
}

MatrixView& MatrixView::operator=(MatrixView&& other) {
    if (this != &other) {
        this->matrix = other.matrix;
        this->rows = other.rows;
        this->cols = other.cols;
        this->startRow = other.startRow;
        this->startCol = other.startCol;
    }
    return *this;
}

MatrixView::~MatrixView() {
    // No dynamic allocation, so nothing to clean up
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

double& MatrixView::operator()(size_t row, size_t col) {
     std::cout << "const "<< rows << " " << cols <<  std::endl;
     std::cout << "const "<< row << " " << col <<  std::endl;
     std::cout << "row >= rows: " << matrix.getRows() << std::endl;
     std::cout << "col >= cols: " <<  matrix.getCols() << std::endl;
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Index out of range");
    }
    return *(&matrix(startRow + row, startCol + col));
}

const double MatrixView::operator()(size_t row, size_t col) const {
    std::cout << "const "<< row << " " << col <<  std::endl;
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Index out of range");
    }
    return matrix(startRow + row, startCol + col);
}



MatrixView MatrixView::subMatrix(size_t subRows, size_t subCols, size_t subStartRow, size_t subStartCol) const {
    if (subStartRow + subRows > rows || subStartCol + subCols > cols) {
        throw std::out_of_range("SubMatrix dimensions exceed MatrixView bounds");
    }
    return MatrixView(matrix, subRows, subCols, startRow + subStartRow, startCol + subStartCol);
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

MatrixView::operator Matrix() const {
        Matrix tmp(this->getRows(), this->getCols());
        for (size_t i = 0; i < this->getRows(); ++i) {
            for (size_t j = 0; j < this->getCols(); ++j) {
                tmp(i, j) = (*this)(i, j); // Copy elements from view
            }
        }
        return tmp;
    }