#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>

class Matrix {
	private:
		std::vector<std::vector<double>> matrix;
		size_t rows;
		size_t cols;

	public:
		Matrix(size_t rows, size_t cols);
		Matrix(size_t rows, size_t cols, double initValue);
		~Matrix();

		size_t	getRows() const;
		size_t	getCols() const;

		const double &operator()(size_t row, size_t col) const;
		double &operator()(size_t row, size_t col);

		friend std::ostream& operator<<(std::ostream &os, const Matrix &matrix);
};

#endif
