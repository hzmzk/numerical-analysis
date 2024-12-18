#include "matrix.h"
#include <vector>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>


////////////    Matrix class : Member definitions    /////////////////

Matrix::Matrix(int row, int col, std::initializer_list<double> list)
    : m_row{ row }, m_col{ col }, m_vec{ list }
{}

Matrix::Matrix(int row, int col, std::initializer_list<std::vector<double>> list)
    : m_row{ row }, m_col{ col }
{
    for (std::size_t i{ 0 }; i < list.size(); ++i)
        m_vec.insert(m_vec.end(), list.begin()[i].begin(), list.begin()[i].end());
}

Matrix::Matrix(int row, int col, std::vector<double>& vec)
    : m_row{ row }, m_col{ col }, m_vec{ vec }
{}

void Matrix::print() const
{
    for (int i{ 0 }; i < m_row; ++i)
    {
        for (int j{ 0 }; j < m_col; ++j)
            std::cout << std::fixed << std::setprecision(4) <<std::setw(7) 
                << m_vec[static_cast<std::size_t>(i * m_col + j)] << ' ';
        std::cout << '\n';
    }
}


std::vector<double> Matrix::row(int i) const
{
    std::vector<double> row_i(static_cast<std::size_t>(m_col));

    for (int j{ 0 }; j < m_col; ++j)
        row_i[static_cast<std::size_t>(j)] = m_vec[static_cast<std::size_t>((i - 1) * m_col + j)];

    return row_i;
}

Matrix& Matrix::operator=(const Matrix& copy)
{
    if (this == &copy)
        return *this;
    else
    {
        m_row = copy.m_row;
        m_col = copy.m_col;
        m_vec = copy.m_vec;
        return *this;
    }
}


///////////////    Matrix Operations    /////////////////////

Matrix operator+(const Matrix& a, const Matrix& b)
{
    Matrix temp{ a };

    for (int i{ 0 }; i < a.getRow(); ++i)
        for (int j{ 0 }; j < a.getCol(); ++j)
            temp(i, j) = a(i, j) + b(i, j);

    return temp;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
    Matrix temp{ a };

    for (int i{ 0 }; i < a.getRow(); ++i)
        for (int j{ 0 }; j < a.getCol(); ++j)
            temp(i, j) = a(i, j) - b(i, j);

    return temp;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
    std::vector<double> temp(static_cast<std::size_t>(a.getRow() * b.getCol()));

    for (int i{ 0 }; i < a.getRow(); ++i)
        for (int j{ 0 }; j < b.getCol(); ++j)
            for (int l{ 0 }; l < b.getRow(); ++l)
                temp[static_cast<std::size_t>(i * b.getCol() + j)] += a(i, l) * b(l, j);

    return { a.getRow() , b.getCol() , temp };
}

Matrix operator*(const double s, const Matrix& a)
{
    Matrix temp{ a };

    for (int i{ 0 }; i < a.getRow(); ++i)
        for (int j{ 0 }; j < a.getCol(); ++j)
            temp(i, j) = s * a(i, j);

    return temp;
}

std::vector<double> operator*(const Matrix& a, std::vector<double>& x)
{
    std::vector<double> y(static_cast<std::size_t>(a.getRow()));

    for (int i{ 0 }; i < a.getRow(); ++i)
        for (int j{ 0 }; j < a.getCol(); ++j)
            y[static_cast<std::size_t>(i)] +=
            x[static_cast<std::size_t>(j)] * a(i, j);

    return y;
}

Matrix transpose(const Matrix& a)     //Return transpose of a matrix
{
    std::vector<double> temp(static_cast<std::size_t>(a.getRow() * a.getCol()));

    for (int i{ 0 }; i < a.getRow(); ++i)
        for (int j{ 0 }; j < a.getCol(); ++j)
            temp[static_cast<std::size_t>(j * a.getRow() + i)] = a(i, j);

    return { a.getCol() , a.getRow() , temp };
}



//////////  Miscellaneous functions  //////////////

Matrix id_matrix(int dimension)      //Return identity matrix of dimension n
{
    std::vector<double> id(static_cast<std::size_t>(dimension * dimension));

    for (std::size_t i{ 0 }; i < dimension; ++i)
        for (std::size_t j{ 0 }; j < dimension; ++j)
            if (i == j)
                id[i * dimension + i] = 1;

    return Matrix{ dimension, dimension, id };
}

Matrix gauss_jordan_inverse(const Matrix& a)      //Return inverse of a matrix
{
    Matrix c{ a };
    Matrix inv_matrix{ id_matrix(a.getRow()) };
    double placeholder{ 0 };

    for (int k{ 0 }; k < c.getRow(); ++k)
        for (int i{ k }; i < c.getRow(); ++i)
            if (i == k)
            {
                placeholder = c(i, i);
                for (int j{ 0 }; j < c.getRow(); ++j)
                {
                    inv_matrix(i, j) /= placeholder;
                    c(i, j) /= placeholder;
                }
            }
            else
            {
                placeholder = c(i, k);
                for (int j{ 0 }; j < c.getRow(); ++j)
                {
                    inv_matrix(i, j) -= placeholder * inv_matrix(k, j);
                    c(i, j) -= placeholder * c(k, j);
                }
            }

    for (int k{ c.getCol() - 1 }; k != -1; --k)
        for (int i{ k }; i != -1; --i)
            if (i != k)
            {
                placeholder = c(i, k);
                for (int j{ 0 }; j < c.getCol(); ++j)
                {
                    inv_matrix(i, j) -= placeholder * inv_matrix(k, j);
                    c(i, j) -= placeholder * c(k, j);
                }
            }

    return inv_matrix;
};

