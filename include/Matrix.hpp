#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <cstddef> 

# define 	GREEN 		"\e[1;32m"
# define 	RED 		"\e[1;31m"
# define 	WHITE 		"\e[1;37m"
# define 	YELLOW 	"\e[1;33m"
# define 	BLUE 		"\e[1;34m"
# define 	PURPLE 	"\033[1;35m"
# define 	DEFAULT	"\e[0;37m"



// class ElementProxy;
class MatrixView;

class Matrix {
	private:
		// std::vector<std::vector<double>> matrix;
		double **matrix;
		size_t rows;
		size_t cols;
		mutable double sum;
		mutable bool sumComputed;
	public:
		Matrix(size_t rows, size_t cols);
		Matrix(size_t rows, size_t cols, double initValue);
		Matrix(const Matrix &other);
		Matrix &operator=(const Matrix &other);
		Matrix(Matrix&& other);
		
		Matrix &operator=(Matrix&& other);
		~Matrix();

		size_t	getRows() const;
		size_t	getCols() const;
		double getSum() const;
		double **getMatrix() const;
		double get(size_t row, size_t col) const;

	
		void  setSum(double value) const;
		void set(size_t row, size_t col, double value);

		MatrixView operator()(size_t row, size_t col);
		const double &operator()(size_t row, size_t col) const;
		// double &operator()(size_t row, size_t col);


		double frobeniusNorm() const;

		friend std::ostream& operator<<(std::ostream &os, const Matrix &matrix);
};

#include "MatrixView.hpp"

#endif
