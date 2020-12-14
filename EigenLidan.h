//
// Created by 李源 on 2020-12-14.
//

#ifndef MYEIGEN_EIGENLIDAN_H
#define MYEIGEN_EIGENLIDAN_H

#include <fstream>
#include <vector>
#include <cmath>
#include <complex>
#include <iostream>
#include <iomanip> // io manipulator
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>


using namespace std ;

template<class T>
inline T Square(const T &a) { return a*a ; }

// note: double and float, pick float
template<class T>
inline const T& Max(const T& a, const T& b)
{ return b > a ? (b) : (a); }

inline float Max(const double &a, const float &b)
{return b > a ? (b) : float(a);}

inline float Max(const float &a, const double &b)
{return b > a ? float(b) : (a);}

// note: double and float, pick float
template<class T>
inline const T& Min(const T& a, const T& b)
{ return b > a ? (a) : (b); }

inline float Min(const double& a, const float& b)
{ return b > a ? float(a) : (b) ; }

inline float Min(const float& a , const double& b)
{ return b > a ? (a) : float(b) ; }

// note: double and float, pick float
// note: to make a has the same flag with b

template<class T>
inline T Sign(const T& a, const T& b)
{ return b >= 0 ? (a >= 0? (a) : (-a)) :(a >= 0? (-a) : (a)) ;}

inline float Sign(const double& a, const float& b)
{ return float(b >= 0 ? (a >= 0? (a) : (-a)) :(a >= 0? (-a) : (a))) ;}

inline float Sign(const float& a, const double& b)
{ return b >= 0 ? (a >= 0? (a) : (-a)) :(a >= 0? (-a) : (a)) ; }


template<class T>
inline void Swap(T& a, T& b)
{ T t = a ; a = b ; b = t ; }


// note: error Handler

#ifndef _USER_ERROR_CLASS_
#define throw(message) \
{ printf(" ERROR: %s/n   in file %s at line %d.\n", message, __FILE__, __LINE__); throw(1); }
#else

struct Lerror{
    char *message;
    char *file;
    int line;
    Lerror(char *m, char *f, int l) : message(m), file(f), line(l) {}
};

#define throw(message) throw(Lerror(message, __FILE__, __LINE__)) ;
void Lcatch(Lerror err)
{
    printf("ERROR: %s\n    in file %s at line %d\n", err.message, err.file, err.line) ;
    exit(1) ;
}

#endif

#ifdef _USESTDVECTOR_
#define NRvector vector
#else
template<class T>
class Lvector{
private:
    int size_vector ;
    T* data ;

public:
    Lvector() ;
    explicit Lvector(int size) ;
    Lvector(int size, const T& a) ;
    Lvector(int size, const T* a) ;
    Lvector(const Lvector& rhs) ;
    Lvector & operator=(const Lvector& rhs) ;
    typedef T value_type ;
    inline T& operator[](const int i) ; // why is it inline?
    inline const T& operator[](const int i) const ;
    inline int size() ;
    void resize(int newsize) ;
    void assign(int newsize, const T& a) ;
    ~Lvector() ;
};


template <class T>
Lvector<T>::Lvector() : size_vector(0), data(NULL) {}

// note : if Lvector size less than zero. You will get a nullptr data.
template <class T>
Lvector<T>::Lvector(int size) : size_vector(size), data( size > 0? new T[size]: nullptr) {}


template <class T>
Lvector<T>::Lvector(int size,const T& a) : size_vector(size), data( size > 0? new T[size]: nullptr)
{
    for(int i = 0  ; i < size ; i++)  data[i] = a  ;
}

// note : if put in the stack a pointer, the pointer must be a array pointer.
template <class T>
Lvector<T>::Lvector(int size, const T* a) : size_vector(size), data( size > 0? new T[size]: nullptr)
{
    for(int i = 0 ; i < size ; i++) data[i] = *a++ ;
}

// note : the : init list is also ordered.
template <class T>
Lvector<T>::Lvector(const Lvector& rhs) : size_vector(rhs.size_vector), data( size_vector > 0? new T[size]: nullptr)
{
    for(int i = 0 ; i< size_vector ;i++)  data[i] = rhs.data[i] ;
}

//note: resize vector and copy data
template <class T>
Lvector<T>& Lvector<T>::operator=(const Lvector<T> &rhs) {
    if(this != &rhs)
    {
        if(size_vector!=rhs.size_vector)
        {
            if(data!=nullptr)
            {
                delete[] (data) ;
            }

            size_vector = rhs.size_vector ;
            data = size_vector>0 ? new T[size_vector] : NULL ;
        }

        for(int i = 0;  i < size_vector ;i++)
        {
            data[i] = rhs[i] ;
        }
    }

    return *this ;
}


// if you use []， you must has two version. one for [], another for const [].
template <class T>
inline T& Lvector<T>::operator[](const int i)
{
#ifdef _CHECKBOUNDS_
    if(i<0 || i >= size_vector) throw("Lvector subscript out of bounds.")
#endif
    return data[i] ;
}


template <class T>
inline const T & Lvector<T>::operator[](const int i) const	//subscripting
{
#ifdef _CHECKBOUNDS_
    if (i<0 || i>=nn) {
	throw("Lvector subscript out of bounds");
}
#endif
    return data[i];
}

// note: resize would remove all data
template <class T>
void Lvector<T>::resize(int newsize)
{
    f (newsize != size_vector) {
        if (data != NULL) delete[] (data);
        size_vector  = newsize;
        data = size_vector > 0 ? new T[size_vector] : NULL;
    }
}

template <class T>
void Lvector<T>::assign(int newsize, const T& a)
{
    if(newsize != size_vector)
    {
        if(data != nullptr) delete[] v ;
        size_vector = newsize ;
        data = size_vector > 0? new T[size_vector] : nullptr ;
    }
    for( int i = 0; i< size_vector ;i++)  data[i] = a ;
}


template <class T>
Lvector<T>::~Lvector()
{
    if (data != nullptr) delete[] (data);
}

#endif


// define datatype
typedef int Int; // 32 bit integer
typedef unsigned int Uint;


// MSVC provide int 64  other provide long long
#ifdef _MSC_VER
typedef __int64 Llong; // 64 bit integer
typedef unsigned __int64 Ullong;
#else
// other compiler provide all
typedef long long int Llong; // 64 bit integer
typedef unsigned long long int Ullong;
#endif

typedef char Char; // 8 bit integer
typedef unsigned char Uchar;

typedef double Doub; // default floating type
typedef long double Ldoub;

typedef complex<double> Complex; // default complex type

typedef bool Bool;





#endif //MYEIGEN_EIGENLIDAN_H
