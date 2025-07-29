/*******************************************************
 * Author: Kyle Bueche
 * File: main.cpp
 * 
 * A polynomial symmetrizer
 ******************************************************/
#include <algorithm>
#include <vector>
#include <iostream>

#include "polynomial.h"

long long factorial(int n)
{
    if (n < 0)
    {
        return -1;
    }

    long long result = 1;
    for (int i = 1; i <= n; ++i)
    {
        result *= i;
    }
    return result;
}

int main()
{
    int nVars = 3;
    std::vector<unsigned int> X = std::vector<unsigned int>(nVars);
    for (int i = 0; i < nVars; i++)
    {
        X[i] = i;
    }

    Polynomial<float> p(nVars);
    p.setRuleDegree2(0, 0, 4.0f);
    p.setRuleDegree2(0, 1, 100.0f);
    p.setRuleDegree2(1, 1, 7.2f);
    p.setRuleDegree1(0, 3.3f);
    p.setRuleDegree1(1, 10.0f);
    p.setRuleConstant(1.0f);
    std::sort(X.begin(), X.end());
    p.p(X);
    p.printFunction();
    p.printCoefficients();

    while (std::next_permutation(X.begin(), X.end()))
    {
        p.pAdd(X);
    }
    p.scale(1.0f / float(factorial(nVars)));
    
    std::cout << std::endl;
    p.printFunction();
    p.printCoefficients();

	return 0;
}
