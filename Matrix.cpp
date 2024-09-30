#include "Matrix.hpp"

Matrix::Matrix(size_t rows, size_t cols, double initValue, bool initMemory)
	: rows(rows), cols(cols)
{
	std::cout << "Matrix default constructor called" << std::endl;
	if (initMemory) {
		this->matrix = std::vector<std::vector<double>>(rows, std::vector<double>(cols, initValue));
	} else {
		this->matrix = std::vector<std::vector<double>>(rows);
		for (size_t i = 0; i < rows; i++) {
			this->matrix[i].reserve(cols);
		}
	}
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

double Matrix::get(size_t row, size_t col) const {
	if (row >= this->rows || col >= this->cols || row < 0 || col < 0) {
		throw std::out_of_range("Index out of range");
	}
	return this->matrix[row][col];
}

void Matrix::set(size_t row, size_t col, double value) {
	if (row >= this->rows || col >= this->cols || row < 0 || col < 0) {
		throw std::out_of_range("Index out of range");
	}
	this->matrix[row][col] = value;
}
