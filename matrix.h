#ifndef MATRIX      // A header that contains matrix class
#define MATRIX      // and matrix-related functions

#include <vector>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>

template <typename T>
class Matrix
{
private:
    int m_row{};
    int m_col{};
    std::vector<T> m_vec{};
   
public:
    Matrix(int row, int col, std::initializer_list<T> list);

    Matrix(int row, int col, std::initializer_list<std::vector<T>> list);

    Matrix(int row, int col, std::vector<T>& vec);

    T& operator[](int i){ return m_vec[static_cast<std::size_t>(i)]; }
    const T& operator[](int i) const { return m_vec[static_cast<std::size_t>(i)]; }

    T& operator()(int i, int j){ return m_vec[static_cast<std::size_t>(i*getCol() + j)]; }
    const T& operator()(int i, int j) const { return m_vec[static_cast<std::size_t>(i*getCol() + j)]; }

    int getRow() const { return m_row; }
    int getCol() const { return m_col; }

    void print() const;  

    std::vector<T> row(int i) const;

    Matrix<T>& operator=(const Matrix<T>& copy);
};


////////////    Matrix class : Member definitions    /////////////////

template <typename T>
Matrix<T>::Matrix(int row, int col, std::initializer_list<T> list)
    : m_row{ row }, m_col{ col }, m_vec{ list }
{}

template <typename T>
Matrix<T>::Matrix(int row, int col, std::initializer_list<std::vector<T>> list)
    : m_row{ row }, m_col{ col }
{
    for (std::size_t i{ 0 }; i < list.size(); ++i)
        m_vec.insert(m_vec.end(), list.begin()[i].begin(), list.begin()[i].end());
}

template <typename T>
Matrix<T>::Matrix(int row, int col, std::vector<T>& vec)
    : m_row{ row }, m_col{ col }, m_vec{ vec }
{}

template <typename T>
void Matrix<T>::print() const
{
    for (int i{ 0 }; i < m_row; ++i)
    {
        for (int j{ 0 }; j < m_col; ++j)
            std::cout << std::setprecision(2) << std::setw(8) << m_vec[static_cast<std::size_t>(i * m_col + j)] << ' ';
        std::cout << '\n';
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& copy)
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

template <typename T> 
std::vector<T> Matrix<T>::row(int i) const
{
    std::vector<T> arr(static_cast<std::size_t>(m_col));

    for (int j{ 0 }; j < m_col; ++j)
        arr[static_cast<std::size_t>(j)] = m_vec[static_cast<std::size_t>((i-1) * m_col + j)];

    return arr;
}


///////////////    Matrix Operations    /////////////////////


template <typename T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
{
    Matrix<T> c{a};

    for(int i{0}; i < a.getRow(); ++i)
        for(int j{0}; j < a.getCol(); ++j)
            c(i, j) = a(i, j) + b(i, j);

    return c; 
}

template <typename T>
Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b)
{
    Matrix<T> c{a};

    for(int i{0}; i < a.getRow(); ++i)
        for(int j{0}; j < a.getCol(); ++j)
            c(i, j) = a(i, j) - b(i, j);

    return c; 
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b)
{
    std::vector<T> arr(static_cast<std::size_t>(a.getRow() * b.getCol()));

    for (int i{ 0 }; i < a.getRow(); ++i)
        for (int j{ 0 }; j < b.getCol(); ++j)
            for (int l{ 0 }; l < b.getRow(); ++l)
                arr[static_cast<std::size_t>(i * b.getCol() + j)] += a(i, l) * b(l, j);

    return { a.getRow() , b.getCol() , arr };
}

template <typename T>
Matrix<T> operator*(const T& s, const Matrix<T>& a)
{
    Matrix<T> c{ a };

    for (int i{ 0 }; i < a.getRow(); ++i)
        for (int j{ 0 }; j < a.getCol(); ++j)
            c(i,j) = s * a(i, j);

    return c;
}

template <typename T>
std::vector<T> operator*(const Matrix<T>& a, std::vector<T>& x)
{
    std::vector<T> y(static_cast<std::size_t>(a.getRow()));

    for (int i{ 0 }; i < a.getRow(); ++i)
        for (int j{ 0 }; j < a.getCol(); ++j)
            y [static_cast<std::size_t>(i)] += 
                x[static_cast<std::size_t>(j)] * a(i, j);

    return y;
}

template <typename T>
Matrix<T> transpose(const Matrix<T>& a)     //Return transpose of a matrix
{
    std::vector<T> arr(static_cast<std::size_t>(a.getRow() * a.getCol()));

    for (int i{ 0 }; i < a.getRow(); ++i)
        for (int j{ 0 }; j < a.getCol(); ++j)
            arr[static_cast<std::size_t>(j * a.getRow() + i)] = a(i, j);

    return { a.getCol() , a.getRow() , arr };
}

//////////  Miscellaneous functions  //////////////

template <typename T>
Matrix<T> id_matrix(int dimension)      //Return identity matrix of dimension n
{
    std::vector<T> id(static_cast<std::size_t>(dimension * dimension));

    for (std::size_t i{ 0 }; i < dimension; ++i)
        for (std::size_t j{ 0 }; j < dimension; ++j)
            if (i == j)
                id[i * dimension + i] = 1;

    return Matrix<T>{dimension, dimension, id};
}

template <typename T>                                   
Matrix<T> gauss_jordan_inverse(const Matrix<T>& a)      //Return inverse of a matrix
{
    Matrix<T> c{ a };
    Matrix<T> inv_matrix{ id_matrix<T>(a.getRow()) };
    T placeholder{ 0 };
    
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
                    c(i, j) -= placeholder * c(k,j) ;
                }
            }       

    for (int k{ c.getCol() - 1 }; k != -1; --k)
        for (int i{ k }; i != -1; --i)
            if(i != k)
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

#endif