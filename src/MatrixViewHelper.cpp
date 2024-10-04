#include "../include/MatrixViewHelper.hpp"
#include "../include/MatrixView.hpp"

MatrixViewHelper::MatrixViewHelper(MatrixView& matrixView, size_t row, size_t col)
    : matrixView(matrixView), row(row), col(col)
{
}

MatrixViewHelper& MatrixViewHelper::operator=(double value)
{
    matrixView.updateValueAndSum(value, row, col);
    return *this;
}

MatrixViewHelper::operator double() const
{
    return matrixView.getValue(row, col);
}
