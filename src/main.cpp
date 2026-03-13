/*******************************************************
 * Author: Kyle Bueche
 * File: main.cpp
 * 
 * A polynomial symmetrizer
 ******************************************************/
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <iostream>
#include <fstream>

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
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);


    std::ofstream outputFile("PermutationData2.csv");
    if (!outputFile.is_open())
    {
        std::cerr << "Can't open PermutationData.csv" << std::endl;
        return 1;
    }

    float c1 = 5.7;
    float c2 = 3.9;
    float c3 = 47.345;
    float c4 = -2.0;
    float c5 = -34.3;
    float c6 = -100.11111111111111;

    int nVars = 8;
    std::vector<unsigned int> X(nVars);
    for (int i = 0; i < nVars; i++)
    {
        X[i] = i;
    }

    Polynomial<float> p(nVars);
    std::cout << "here" << std::endl;
    p.setRuleDegree2(1 - 1, 2 - 1, c1);
    p.setRuleDegree2(3 - 1, 4 - 1, c2);
    p.setRuleDegree2(5 - 1, 6 - 1, c3);
    p.setRuleDegree2(7 - 1, 8 - 1, c4);
    //p.setRuleDegree2(9 - 1, 10 - 1, c5);
    //p.setRuleDegree2(11 - 1, 12 - 1, c6);
    std::cout << "here" << std::endl;


    Polynomial<float> pConverged = p;
    std::sort(X.begin(), X.end());
    while (std::next_permutation(X.begin(), X.end()))
    {
        pConverged.pAdd(X);
    }

    pConverged.scale(1.0f / float(factorial(nVars)));

    for (int i = 0; i < 1000000; i++)
    {
        std::shuffle(X.begin(), X.end(), rng);
        p.pAdd(X);
        Polynomial<float> p2 = p;
        p2.scale(1.0 / float(i));
            outputFile << distance(p2, pConverged) << '\n';
    }
    outputFile.close();
    std::cout << "done!" << std::endl;

    return 0;
}

void old_example() {
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
}
