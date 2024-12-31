#ifndef MATRIX      // A header that contains matrix class
#define MATRIX      // and matrix-related functions

#include <vector>
#include <initializer_list>

class Matrix
{
private:
    int m_row{};
    int m_col{};
    std::vector<double> m_vec{};
   
public:
    Matrix(int row, int col, std::initializer_list<double> list);
    Matrix(int row, int col, std::initializer_list<std::vector<double>> list);
    Matrix(int row, int col, std::vector<double>& vec);

    double& operator[](int i){ return m_vec[static_cast<std::size_t>(i)]; }
    double operator[](int i) const { return m_vec[static_cast<std::size_t>(i)]; }

    double& operator()(int i, int j){ return m_vec[static_cast<std::size_t>(i*getCol() + j)]; }
    double operator()(int i, int j) const { return m_vec[static_cast<std::size_t>(i*getCol() + j)]; }

    int getRow() const { return m_row; }
    int getCol() const { return m_col; }

    void print() const;  

    std::vector<double> row(int i) const;

    Matrix& operator=(const Matrix& copy);
};


///////////////    Matrix Operators Overload    /////////////////////

Matrix operator+(const Matrix& a, const Matrix& b);

Matrix operator-(const Matrix& a, const Matrix& b);

Matrix operator*(const Matrix& a, const Matrix& b);

Matrix operator*(const double s, const Matrix& a);

std::vector<double> operator*(const Matrix& a, std::vector<double>& x);

Matrix transpose(const Matrix& a);     


//////////  Matrix-related functions  //////////////

Matrix id_matrix(int dimension);      //Return identity matrix of dimension n
                                   
Matrix gauss_jordan_inverse(const Matrix& a);      //Return inverse of a matrix

#endif