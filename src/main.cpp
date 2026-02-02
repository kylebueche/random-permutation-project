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
    int nVars = 8;
    std::vector<unsigned int> X = std::vector<unsigned int>(nVars);
    for (int i = 0; i < nVars; i++)
    {
        X[i] = i;
    }

    Polynomial<float> p(nVars);
    // i == j == k
    p.setRuleDegree3(4, 4, 4, 54620.0f);
    // i < j < k
    p.setRuleDegree3(1, 3, 5, -11111732.5f);
    // i < j == k
    p.setRuleDegree3(3, 4, 4, -91111123.456f);
    // i == j < k
    p.setRuleDegree3(4, 4, 5, 10000000.55593f);

    p.setRuleDegree2(4, 4, -9.0f);
    p.setRuleDegree2(3, 3, 8.0f);
    p.setRuleDegree2(2, 2, -1.0f);
    p.setRuleDegree2(1, 1, 3.0f);
    p.setRuleDegree2(0, 6, -9.0f);
    p.setRuleDegree2(1, 6, -1.0f);
    p.setRuleDegree2(0, 7, -1.0f);
    p.setRuleDegree2(1, 7, -1.0f);
    p.setRuleDegree2(2, 4, 1.0f);
    p.setRuleDegree2(3, 4, 1.0f);
    p.setRuleDegree2(2, 5, 1.0f);
    p.setRuleDegree2(3, 5, 1.0f);
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
