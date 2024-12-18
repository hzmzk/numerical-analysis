#include "matrix.h"
#include <iostream>

int main()
{    
    Matrix a{ 3,3,
    {
        2,-1,0,
        -1,2,-1,
        0,-1,2
    }
    };

    a.print();
    std::cout << '\n';

    Matrix b = gauss_jordan_inverse(a);

    b.print();
    std::cout << '\n';

    Matrix c{ a * b };
    
    c.print();
    std::cout << '\n';

    return 0;
}

