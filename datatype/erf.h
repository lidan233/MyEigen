//
// Created by 李源 on 2020-12-14.
//

#ifndef MYEIGEN_ERF_H
#define MYEIGEN_ERF_H

#include "EigenLidan.h"


struct Erf {
    static const Int ncof = 28 ;
    static const Doub cof[28] ;

    inline Doub erf(Doub x)
    {
        if( x >= 0. ) return 1.0 - erfccheb(x) ;
        else return erfccheb(-x) - 1.0;
    }

    Doub erfccheb(Doub z){
        Int j;
        Doub t,ty,tmp,d=0.,dd=0.;
        if (z < 0.) throw("erfccheb requires nonnegative argument");
        t = 2./(2.+z);
        ty = 4.*t - 2.;
        for (j=ncof-1;j>0;j--) {
            tmp = d;
            d = ty*d - dd + cof[j];
            dd = tmp;
        }
        return t*exp(-z*z + 0.5*(cof[0] + ty*d) - dd);
    }

    Doub inverfc(Doub p) {
        Doub x,err,t,pp;
        if (p >= 2.0) return -100.;
        if (p <= 0.0) return 100.;
        pp = (p < 1.0)? p : 2. - p;
        t = sqrt(-2.*log(pp/2.));
        x = -0.70711*((2.30753+t*0.27061)/(1.+t*(0.99229+t*0.04481)) - t);
        for (Int j=0;j<2;j++) {
            err = erfc(x) - pp;
            x += err/(1.12837916709551257*exp(-Square(x))-x*err);
        }
        return (p < 1.0? x : -x);
    }

    inline Doub inverf(Doub p) {return inverfc(1.-p);}


};
#endif //MYEIGEN_ERF_H
