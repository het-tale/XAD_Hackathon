#ifndef MATRIXVIEW_HPP
#define MATRIXVIEW_HPP

#include "Matrix.hpp"

class MatrixView {
	private:
		Matrix& matrix;
		size_t rows;
		size_t cols;
		size_t startRow;
		size_t startCol;
       mutable double sum;
        mutable bool sumComputed;

        

	public:
        // Constructors
		MatrixView(Matrix& matrix, size_t rows, size_t cols, size_t startRow, size_t startCol);
        MatrixView(const MatrixView& other);
        MatrixView& operator=(const MatrixView& other);
        MatrixView(MatrixView&& other);
        MatrixView& operator=(MatrixView&& other);

		~MatrixView();

        // getters
        size_t getRows() const;
        size_t getCols() const;
        size_t getStartRow() const;
        size_t getStartCol() const;

        double frobeniusNorm() const; 

        operator Matrix() const;

        // Overload the () operator to access elements of the matrix
        double& operator()(size_t row, size_t col);
        const double operator()(size_t row, size_t col) const;


		MatrixView subMatrix(size_t rows, size_t cols, size_t startRow, size_t startCol) const;
};

#endif
