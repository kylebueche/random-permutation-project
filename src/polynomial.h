/********************************************
 * Author: Kyle Bueche
 * File: polynomial.h
 *
 * A class for defining polynomials
 *******************************************/

#include <vector>

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

template <typename Real>
class polynomial
{
    private:
        std::vector<std::vector<Real>> coefficients;
    public:
        void build(std::vector<Real> variableArray);
        Real evaluate(std::vector<Real> variableInstances);
        void printCoefficients();
};

#endif

/****************************************************************
 * The task provided:
 *
 * Find the smallest number of steps to symmetrize a polynomial
 * OR find the rate of convergence for random symmetrization
 *
 * f(x1, ..., xn) is any function that returns a polynomial
 * of the variable inputs.
 *
 * Need a polynomial function class that can evaluate f() at
 * real inputs, or any set of n inputs in the set R
 *
 * Also need a function that can add *generic variables* to f()
 * in order to build f() depending on the current base rule.
 *
 * For example, define the rule f(r1, r2, r3) = r1 * r2 + r3
 * Then, f(x1, x2, x3) builds x1 * x2 + x3,
 * And,  f(x2, x3, x1) builds x2 * x3 + x1
 *
 * For a polynomial p = 0, with a rule attached like above,
 * building is additive. Building f(x1, x2, x3) will add
 * to p's value, resulting in p = x1 * x2 + x3. Further
 * building f(x2, x3, x1) results in p = x1 * x2 + x3 + x2 * x3 + x1.
 *
 * p is initially stored as a triangular matrix of coefficients
 * the value is associated with the row variable times the col variable
 * 
 *    1 x1 x2 x3
 *  1 0  0  0  0
 * x1 0  0  0  0
 * x2 0  0  0  0
 * x3 0  0  0  0
 *
 * build f(x1, x2, x3):
 *
 *    1 x1 x2 x3
 *  1 0  0  0  1
 * x1 0  0  1  0
 * x2 0  0  0  0
 * x3 0  0  0  0
 *
 * build f(x2, x3, x1):
 *
 *    1 x1 x2 x3
 *  1 0  1  0  1
 * x1 0  0  1  0
 * x2 0  0  0  1
 * x3 0  0  0  0
 *
 * Now we can track our entire polynomial of size n
 * in O(n^2) space
 *
 * Also define scalar operations so that c * p scales every entry
 * in the table by c
 *
 * for any rule, building f(x1, x2, ..., xn) is always the
 * polynomial that we are trying to symmetrize. Thus it is the
 * base input polynomial
 *
 * Prerequesites:
 *  - require a customizeable internal rule for build to follow
 *  - require the function void build(std::vector) that takes
 *    a vector of integers which are a permutation of the set
 *    { 1, 2, ..., vector.size() } and treats the input as if it
 *    were building f(xi, ..., xi), where i are the input numbers
 *  - require the function Real evaluate(x1, ..., xn) which
 *    calculates the value when each xi is set to a real number
 *
 * Step 1:
 *  - Require an infinite sequence of permutations
 *******************************************************************
