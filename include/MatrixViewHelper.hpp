#ifndef MATRIXVIEWHELPER_HPP
#define MATRIXVIEWHELPER_HPP

#include <iostream>
#include <cstddef>

class MatrixView;

class MatrixViewHelper
{
private:
    MatrixView& matrixView;
    size_t row;
    size_t col;

public:
    MatrixViewHelper(MatrixView& matrixView, size_t row, size_t col);
    MatrixViewHelper& operator=(double value);
    operator double() const;
};

#include "MatrixView.hpp"

#endif