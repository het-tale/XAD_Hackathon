#include "../include/Matrix.hpp"
#include "../include/MatrixView.hpp"
#include <cmath>
#include <iostream>



/*

 Constructors

*/

Matrix::Matrix(size_t rows, size_t cols)
	: rows(rows), cols(cols), sum(0)
{
	this->matrix = new double*[rows];
	for (size_t i = 0; i < rows; i++) {
		this->matrix[i] = new double[cols];
	}
	// std::cout << GREEN << "Matrix default constructor called" << DEFAULT << std::endl;
}


Matrix::Matrix(size_t rows, size_t cols, double initValue)
	: rows(rows), cols(cols)
{
	this->sum = pow(initValue, 2) * rows * cols;
	this->matrix = new double*[rows];
	for (size_t i = 0; i < rows; i++) {
		this->matrix[i] = new double[cols];
		for (size_t j = 0; j < cols; j++)
			this->matrix[i][j] = initValue;
	}
	// std::cout << GREEN << "Matrix parameterized constructor called" << DEFAULT << std::endl;
}

Matrix::Matrix(const Matrix &other) {
	(*this) = other;
	// std::cout << GREEN << "Matrix copy constructor called" << DEFAULT << std::endl;
}



/*

	Asignment Operator

*/

Matrix &Matrix::operator=(const Matrix &other) {
	if (this != &other) {
		this->rows = other.rows;
		this->cols = other.cols;
		this->matrix = new double*[other.rows];
		for (size_t i = 0; i < other.rows; i++) {
			this->matrix[i] = new double[other.cols];
			for (size_t j = 0; j < other.cols; j++)
				this->matrix[i][j] = other.matrix[i][j];
		}

	}
	// std::cout << GREEN << "Matrix copy assignment operator called" << DEFAULT << std::endl;
	return (*this);
}



Matrix::Matrix(Matrix&& other)
	: rows(other.rows), cols(other.cols), matrix(std::move(other.matrix))
{
	other.rows = 0;
	other.cols = 0;
	// std::cout << GREEN << "Matrix move constructor called" << DEFAULT << std::endl;
}

Matrix &Matrix::operator=(Matrix&& other) {
    if (this != &other) {
		this->rows = other.rows;
		this->cols = other.cols;
		this->matrix = std::move(other.matrix);

		other.rows = 0;
		other.cols = 0;
	}
	// std::cout << GREEN << "Matrix move assignment operator called" << DEFAULT << std::endl;
	return *this;
}

Matrix::~Matrix() {
	if (this->matrix != NULL) {
	for (size_t i = 0; i < this->rows; i++) {
		if (this->matrix[i] != NULL) {	
			delete[] this->matrix[i];
		}
		}
		// delete[] this->matrix;
	}
	// std::cout << RED << "Matrix destructor called" << DEFAULT << std::endl;
}


/*
	GETTERS
*/
size_t Matrix::getRows() const {
	return this->rows;
}

size_t Matrix::getCols() const {
	return this->cols;
}

double Matrix::getSum() const {
	return this->sum;
}
double **Matrix::getMatrix() const {
	return this->matrix;

}
double Matrix::get(size_t row, size_t col) const {
	return this->matrix[row][col];
}
bool Matrix::getSumComputed() const  {
	return this->sumComputed;
}


/*

 Old code of operator overloading changed to can have access to value assigned
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

*/


/*
		Setters to the value of the matrix 
*/


void Matrix::setSumComputed(bool value)  {
	this->sumComputed = value;
}

void Matrix::set(size_t row, size_t col, double value) {
	this->matrix[row][col] = value;
}

void Matrix::setSum(double value)  {
	this->sum = value;
}



/*

	Operator Overloading

	The operator return MatrixView  in order to have controll on the assignment operator and access the assigned value and edit the Sum

*/

MatrixView Matrix::operator()(size_t row, size_t col) {

        if (row >= rows || col >= cols) {
            throw std::out_of_range("Index out of range");
        }
        return MatrixView(*this, row, col);
    }


/*

	Const operator

	No need to edit the sum because the operator is const

*/

    const double &Matrix::operator()(size_t row, size_t col) const {
		// std::cout << "const ElementProxy operator called" << std::endl;
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Index out of range");
        }
        return matrix[row][col];
    }




/*

	Frobenius Norm
	
	Compute the sum of the square of the matrix and return the square root of the sum
	Complexity O(n^2) for the first call
	Then O(1) after.
	The sum is update in each modifaction of the matrix so the Complexity stay O(1)
    
*/

double Matrix::frobeniusNorm() const {
	if (!sumComputed) {
		sum = 0;
		for (size_t i = 0; i < this->rows; i++) {
			for (size_t j = 0; j < this->cols; j++) {
				sum += pow(this->matrix[i][j], 2);
			}
		}
		sumComputed = true;
	}
	return sqrt(sum);
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
