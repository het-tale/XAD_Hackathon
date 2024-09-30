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
		Matrix(size_t rows, size_t cols, double initValue = 0.0, bool initMemory = false);
		~Matrix();

		size_t getRows() const;
		size_t getCols() const;

		double get(size_t rows, size_t cols) const;
		void set(size_t rows, size_t cols, double value);

		friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};

#endif
