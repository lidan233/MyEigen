//
// Created by 李源 on 2020-12-16.
//

#ifndef MYEIGEN_GAUSS_JORBAN_H
#define MYEIGEN_GAUSS_JORBAN_H

#include "EigenLidan.h"

template<class T>
std::ostream& operator<<(std::ostream &os, const Lmatrix<T>& obj)
{
    os<<"Matrix "<<obj.mrows()<<"x"<<obj.ncols()<<std::endl ;
    for(int i = 0 ; i < obj.mrows(); i++)
    {
        for(int j = 0;  j < obj.ncols(); j++)
        {
            os<<obj[i][j]<<" ";
        }
        os<<std::endl ;
    }
    return os ;
}

// 如果某一个变量消去，那么不需要再维护这一列的value了，因为都是0-0 或者1-0 浪费计算资源
// note: the matrix must be n*n
// https://www.mathsisfun.com/algebra/matrix-inverse-row-operations-gauss-jordan.html
// he just find some Redundant calculation. So he decides to delete them.
/*
 * MatDoub_IO a [m*m]
 * MatDoub_IO b [m*n]
 *
 * a*x = b
 *
 * begin:
 * a is the input matrix
 * b is the m num n*1 matrix
 *
 * end:
 * a is the inverse matrix
 * b is the solve result
 */

void gaussj(MatDoub_IO &a, MatDoub_IO &b)
{
    Int i, irow, icol, j, k, l, ll, m_a = a.mrows(), n_b = b.ncols() ;
    Doub big, dum, pivinv ;
    VecInt indxc(m_a), indxr(m_a) ,ipiv(m_a) ;

    for(j =0 ; j < m_a; j++) { ipiv[j] = 0 ; }

    // just count all
    for(i = 0 ; i< m_a; i++) {
        big = 0.0;

        // select the biggest value of all the matrix( just including no pivot rows)
        for (j = 0; j < m_a; j++)
            if (ipiv[j] != 1) {

                //note: just select biggest value of j row; we get the col order.
                // so the col order must be the real row, and the biggest will be col,col
                for (k = 0; k < m_a; k++) {
                    if (ipiv[k] == 0) {
                        if (abs(a[j][k]) >= big) {
                            big = abs(a[j][k]);
                            irow = j;
                            icol = k;
                        }
                    }
                }
            }

        // flag this row will be pivot
        ++(ipiv[icol]);

        // change the row of a and b
        if (irow != icol) {
                for (l = 0; l < m_a; l++) Swap(a[irow][l], a[icol][l]);
                for (l = 0; l < n_b; l++) Swap(b[irow][l], b[icol][l]);
        }

        indxr[i] = irow;
        indxc[i] = icol;
        if (a[icol][icol] == 0.0) throw("gaussj: Singular Matrix");

        // icol row just using 1
        pivinv = 1.0 / a[icol][icol];
        a[icol][icol] = 1.0;
        for (l = 0; l < m_a; l++) a[icol][l] *= pivinv;
        for (l = 0; l < n_b; l++) b[icol][l] *= pivinv;

        std::cout<<"begin"<<a<<b<<std::endl ;

        for (ll = 0; ll < m_a; ll++)
            if (ll != icol) {
                dum = a[ll][icol];
                std::cout<<dum<<std::endl ;
                a[ll][icol] = 0.0;
                for (l = 0; l < m_a ; l++) a[ll][l] -= a[icol][l] * dum;
                for (l = 0; l < n_b ; l++) b[ll][l] -= b[icol][l] * dum;
            }

        std::cout<<"end"<<a<<b<<std::endl ;
    }
    for (l = m_a - 1; l >= 0; l--) {
        if (indxr[l] != indxc[l])
            for (k = 0; k < m_a; k++)
                Swap(a[k][indxr[l]], a[k][indxc[l]]);
    }
    std::cout<<a<<b<<std::endl ;

}




void gaussj(MatDoub_IO &a)
{
    MatDoub b(a.mrows(),0);

    std::cout<<a<<std::endl ;
    std::cout<<b<<std::endl ;

    gaussj(a,b);

    std::cout<<a<<std::endl ;
    std::cout<<b<<std::endl ;
}

int testMain()
{
    Lmatrix<Doub> a = Lmatrix<Doub>(2,3)  ;
    a[0][0] = 1.0 ;
    a[1][0] = 2.0 ;
    a[0][1] = 2.0 ;
    a[1][1] = 3.0 ;
    gaussj(a) ;
}


#endif //MYEIGEN_GAUSS_JORBAN_H
