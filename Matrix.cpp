#include "Matrix.hpp"

Matrix::Matrix(size_t rows, size_t cols)
	: rows(rows), cols(cols)
{
	std::cout << "Matrix default constructor called" << std::endl;
	this->matrix = std::vector<std::vector<double>>(rows);
	for (size_t i = 0; i < rows; i++) {
		this->matrix[i].reserve(cols);
	}
}

Matrix::Matrix(size_t rows, size_t cols, double initValue)
	: rows(rows), cols(cols), matrix(rows, std::vector<double>(cols, initValue))
{
	std::cout << "Matrix default constructor called" << std::endl;
}

Matrix::~Matrix() {
	std::cout << "Matrix destructor called" << std::endl;
}

size_t Matrix::getRows() const {
	return this->rows;
}

size_t Matrix::getCols() const {
	return this->cols;
}

const double &Matrix::operator()(size_t row, size_t col) const {
	if (row >= this->rows || col >= this->cols || row < 0 || col < 0)
		throw std::out_of_range("Matrix indices are out of range");
	return this->matrix[row][col];
}

double &Matrix::operator()(size_t row, size_t col) {
	if (row >= this->rows || col >= this->cols || row < 0 || col < 0)
		throw std::out_of_range("Matrix indices are out of range");
	return this->matrix[row][col];
}

std::ostream& operator<<(std::ostream &os, const Matrix &matrixObj) {
	for (size_t i = 0; i < matrixObj.rows; i++) {
		for (size_t j = 0; j < matrixObj.cols; j++){
			os << matrixObj.matrix[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}
