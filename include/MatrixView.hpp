#ifndef MATRIXVIEW_HPP
#define MATRIXVIEW_HPP

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cstddef> 



class Matrix;
class MatrixViewHelper;

class MatrixView {
	public:
		Matrix& matrix;
        double **matrix_ptr;
		size_t rows;
		size_t cols;
		size_t startRow;
		size_t startCol;
        mutable double sum;
        mutable bool sumComputed;
        size_t row;
        size_t col;

        

	public:
        // Constructors
        MatrixView(Matrix& matrix, size_t row, size_t col);
		MatrixView(Matrix& matrix, size_t rows, size_t cols, size_t startRow, size_t startCol);
        MatrixView(const MatrixView& other);
        MatrixView& operator=(const MatrixView& other);
        MatrixView& operator=(double value);
        MatrixView(MatrixView&& other);
        MatrixView& operator=(MatrixView&& other);

		~MatrixView();

        // getters
        size_t getRows() const;
        size_t getCols() const;
        size_t getStartRow() const;
        size_t getStartCol() const;
        double getValue(size_t row, size_t col) const;



        // Overload the () operator to access elements of the matrix
        // const double& operator()(size_t row, size_t col);
        MatrixViewHelper operator()(size_t row, size_t col);
        const double& operator()(size_t row, size_t col) const;
        
        void updateValueAndSum(double value, size_t row, size_t col);

        void setValue(size_t row, size_t col, double value);
        
        operator Matrix() const;
        operator double() const;


        double frobeniusNorm() const; 
		// MatrixView subMatrix(size_t rows, size_t cols, size_t startRow, size_t startCol) const;
};
#include "Matrix.hpp"
#include "MatrixViewHelper.hpp"




#endif
