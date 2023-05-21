/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * Number.cpp
 */

#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

#include "Number.hpp"

Number factorial( unsigned int i ){
    Number num{i};
    if(i > 1){
        Number num = factorial(i-1);
        num.multiply(i);
        return num;
    }
    else{
        return 1;
    }
}

std::istream & operator>>( std::istream & in, Number & n )
{
    n.read(in);
    return in;
}

Number & operator+=( Number &n_1  , unsigned int n_2 ){
    n_1.add(n_2);
    return n_1;
}
Number & operator*=( Number &n_1  , unsigned int n_2  ){
    n_1.multiply(n_2);
    return n_1;
}
Number operator+( Number n_1  , unsigned int n_2 ){
    n_1.add(n_2);
    return n_1;
}
Number operator*( Number n_1  , unsigned int n_2  ){
    n_1.multiply(n_2);
    return n_1;
}
