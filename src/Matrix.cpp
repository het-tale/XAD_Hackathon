#include "../include/Matrix.hpp"

Matrix::Matrix(size_t rows, size_t cols)
	: rows(rows), cols(cols), sum(0)
{
	this->matrix = std::vector<std::vector<double>>(rows);
	for (size_t i = 0; i < rows; i++) {
		this->matrix[i].reserve(cols);
	}
	std::cout << "Matrix parameterized constructor called" << std::endl;
}

Matrix::Matrix(size_t rows, size_t cols, double initValue)
	: rows(rows), cols(cols), matrix(rows, std::vector<double>(cols, initValue))
{
	this->sum = pow(initValue, 2) * rows * cols;
	std::cout << "Matrix parameterized constructor called" << std::endl;
}

Matrix::Matrix(const Matrix &other) {
	(*this) = other;
	std::cout << "Matrix copy constructor called" << std::endl;
}

Matrix &Matrix::operator=(const Matrix &other) {
	if (this != &other) {
		this->rows = other.rows;
		this->cols = other.cols;
		this->matrix.resize(this->rows);
		for (size_t i = 0; i < this->rows; i++) {
			this->matrix[i].resize(this->cols);
			for (size_t j = 0; j < this->cols; j++)
				this->matrix[i][j] = other.matrix[i][j];
		}
	}
	std::cout << "Matrix copy assignment operator called" << std::endl;
	return (*this);
}

Matrix::Matrix(Matrix&& other)
	: rows(other.rows), cols(other.cols), matrix(std::move(other.matrix))
{
	other.rows = 0;
	other.cols = 0;
	std::cout << "Matrix move constructor called" << std::endl;
}

Matrix &Matrix::operator=(Matrix&& other) {
    if (this != &other) {
		this->rows = other.rows;
		this->cols = other.cols;
		this->matrix = std::move(other.matrix);

		other.rows = 0;
		other.cols = 0;
	}
	std::cout << "Matrix move assignment operator called" << std::endl;
	return *this;
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


double Matrix::frobeniusNorm() const {
	return sqrt(sum);
}