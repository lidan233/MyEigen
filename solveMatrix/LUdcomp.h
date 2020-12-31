//
// Created by 李源 on 2021-01-01.
//

#ifndef MYEIGEN_LUDCOMP_H
#define MYEIGEN_LUDCOMP_H
#include "erf.h"
#include "EigenLidan.h"

class LUdcomp {
private:
    Int n;
    MatDoub lu;
    VecInt indx;
    Doub d;
    MatDoub_I &aref;

public:
    LUdcomp(MatDoub_I &a);
    void solve(VecDoub_I &b, VecDoub_O &x);
    void solve(MatDoub_I &b, MatDoub_O &x);
    void inverse(MatDoub_O &ainv);
    Doub det();
    void mprove(VecDoub_I &b, VecDoub_IO &x);
};




#endif //MYEIGEN_LUDCOMP_H
