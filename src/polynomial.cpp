/****************************************************
 * Author: Kyle Bueche
 * File: polynomial.cpp
 *
 * Implementation of the Polynomial class
 *
 * In input lists, it starts counting values from 1
 ***************************************************/

#include "polynomial.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <vector>

template <typename Real>
Polynomial<Real>::Polynomial(unsigned int nVars)
{
    nVariables = nVars;
    template_D3 = std::vector<Real>(nVars * nVars * nVars, 0);
    // Create square matrices with n rows and cols, initialized to 0
    template_D2 = std::vector<std::vector<Real>>(nVars, std::vector<Real>(nVars, 0));
    template_D1 = std::vector<Real>(nVars, 0);
    template_C = 0.0;

    coefs_D3 = std::vector<Real>(nVars * nVars * nVars, 0);
    coefs_D2 = std::vector<std::vector<Real>>(nVars, std::vector<Real>(nVars, 0));
    coefs_D1 = std::vector<Real>(nVars, 0);
    coefs_C = 0.0;
}

template <typename Real>
void Polynomial<Real>::setRuleConstant(Real value)
{
    template_C = value;
}

template <typename Real>
void Polynomial<Real>::setRuleDegree1(unsigned int variable, Real value)
{
    template_D1[variable] = value;
}

template <typename Real>
void Polynomial<Real>::setRuleDegree2(unsigned int variable1, unsigned int variable2, Real value)
{
    unsigned int v1 = std::max(variable1, variable2);
    unsigned int v2 = std::min(variable1, variable2);
    template_D2[v1][v2] = value;
}

template <typename Real>
void Polynomial<Real>::setRuleDegree3(unsigned int variable1, unsigned int variable2, unsigned int variable3, Real value)
{
    template_D3[index(variable1, variable2, variable3)] = value;
}


template <typename Real>
void Polynomial<Real>::p(std::vector<unsigned int> X)
{
    // Total degree 3
    for (int i = 0; i < nVariables; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            for (int k = 0; k <= j; k++)
            {
                coefs_D3[index(X[i], X[j], X[k])] = template_D3[index(i, j, k)];
            }
        }
    }

    // Total degree 2
    for (int i = 0; i < nVariables; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            coefs_D2[X[i]][X[j]] = template_D2[i][j];
        }
    }

    // Total degree 1
    for (int i = 0; i < nVariables; i++)
    {
        coefs_D1[X[i]] = template_D1[i];
    }

    // Constant factor
    coefs_C = template_C;
}

template <typename Real>
void Polynomial<Real>::pAdd(std::vector<unsigned int> X)
{
    // Total degree 3
    for (int i = 0; i < nVariables; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            for (int k = 0; k <= j; k++)
            {
                coefs_D3[index(X[i], X[j], X[k])] += template_D3[index(i, j, k)];
            }
        }
    }

    // Total degree 2
    for (int i = 0; i < nVariables; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            int new_i = X[i];
            int new_j = X[j];
            if (new_i < new_j)
            {
                std::swap(new_i, new_j);
            }
            coefs_D2[new_i][new_j] += template_D2[i][j];
        }
    }

    // Total degree 1
    for (int i = 0; i < nVariables; i++)
    {
        coefs_D1[X[i]] += template_D1[i];
    }

    // Constant factor
    coefs_C += template_C;
}

template <typename Real>
Real Polynomial<Real>::evaluate(std::vector<Real> variableInstances)
{
    Real result;
    // Total degree 2
    for (int i = 0; i < nVariables; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            result += coefs_D2[i][j] * variableInstances[i] * variableInstances[j];
        }
    }

    // Total degree 1
    for (int i = 0; i < nVariables; i++)
    {
        result += coefs_D1[i] * variableInstances[i];
    }

    // Constant factor
    result += coefs_C;
    
    return result;
}

template <typename Real>
void Polynomial<Real>::scale(Real value)
{
    coefs_C = value * coefs_C;
    for (int i = 0; i < nVariables; i++)
    {
        coefs_D1[i] = value * coefs_D1[i];
        for (int j = 0; j <= i; j++)
        {
            coefs_D2[i][j] = value * coefs_D2[i][j];
            for (int k = 0; k <= j; k++)
            {
                coefs_D3[index(i, j, k)] *= value;
            }
        }
    }
}

template <typename Real>
void Polynomial<Real>::printCoefficients()
{
    std::cout << std::endl << std::endl;
    std::cout << "Degree 3 terms:" << std::endl << std::endl;
    std::cout << "i==j==k:" << std::endl << std::endl;
    for (int i = 0; i < nVariables; i++)
        std::cout << std::fixed << std::setprecision(3) << coefs_D3[index(i, i, i)] << " ";

    std::cout << std::endl << std::endl;
    std::cout << "i<j<k:" << std::endl << std::endl;

    for (int k = 0; k < nVariables; k++)
        for (int j = 0; j < k; j++)
            for (int i = 0; i < j; i++)
                std::cout << std::fixed << std::setprecision(3) << coefs_D3[index(i, j, k)] << " ";

    std::cout << std::endl << std::endl;
    std::cout << "i<j==k:" << std::endl << std::endl;

    for (int j = 0; j < nVariables; j++)
        for (int i = 0; i < j; i++)
            std::cout << std::fixed << std::setprecision(3) << coefs_D3[index(i, j, j)] << " ";

    std::cout << std::endl << std::endl;
    std::cout << "i==j<k:" << std::endl << std::endl;

    for (int k = 0; k < nVariables; k++)
        for (int i = 0; i < k; i++)
            std::cout << std::fixed << std::setprecision(3) << coefs_D3[index(i, i, k)] << " ";

    std::cout << std::endl << std::endl;

    
    std::cout << "Degree 2 terms:" << std::endl;
    std::cout << "     ";
    for (int i = 0; i < nVariables; i++)
    {
        std::cout << "x" << i << "    ";
    }
    std::cout << std::endl;
    std::cout << "   |-----";
    for (int i = 0; i < nVariables; i++)
    {
        std::cout << "-----";
    }
    std::cout << "|" << std::endl;
    for (int i = 0; i < nVariables; i++)
    {
        std::cout << "x" << i << " | ";
        for (int j = 0; j < nVariables; j++)
        {
            std::cout << std::fixed << std::setprecision(3) << coefs_D2[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "   |-----";
    for (int i = 0; i < nVariables; i++)
    {
        std::cout << "-----";
    }
    std::cout << "|" << std::endl << std::endl;

    std::cout << "Degree 1 terms:" << std::endl;
    std::cout << "   |------|" << std::endl;
    for (int i = 0; i < nVariables; i++)
    {
        std::cout << "x" << i << " | " << std::fixed << std::setprecision(2) << coefs_D1[i] << " |" << std::endl;
    }
    std::cout << "   |------|" << std::endl << std::endl;

    std::cout << "Constant:" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << coefs_C << std::endl;
}

template <typename Real>
void Polynomial<Real>::printFunction()
{
    // Total degree 2
    for (int i = 0; i < nVariables; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if(coefs_D2[i][j] != 0.0)
            {
                std::cout << std::fixed << std::setprecision(2) << coefs_D2[i][j];
                if (i == j)
                {
                    std::cout << "x" << i << "^2 + ";
                }
                else
                {
                    std::cout << "x" << i;
                    std::cout << "x" << j <<" + ";
                }
            }
        }
    }

    // Total degree 1
    for (int i = 0; i < nVariables; i++)
    {
        if (coefs_D1[i] != 0.0)
        {
            std::cout << std::setprecision(3) << coefs_D1[i];
            std::cout << "x" << i << " + ";
        }
    }

    // Constant factor
    if(coefs_C != 0.0)
    {
        std::cout << coefs_C;
    }
    std::cout << std::endl;
}

template <typename Real>
Polynomial<Real> operator+(Polynomial<Real> p1, const Polynomial<Real> p2)
{
    Polynomial<float> p(p1.nVariables);
    if (p1.nVariables == p2.nVariables)
    {
        p.coefs_C = p1.coefs_C + p2.coefs_C;
        for (int i = 0; i < p1.nVariables; i++)
        {
            p.coefs_D1[i] = p1.coefs_D1[i] + p2.coefs_D1[i];
            for (int j = 0; j <= i; j++)
            {
                p.coefs_D2[i][j] = p1.coefs_D2[i][j] + p2.coefs_D2[i][j];
            }
        }
    }
    return p;
}

template class Polynomial<float>;
template class Polynomial<double>;
        

/*****************************************************
 * Thinking I could do this with a matrix?
 * Needs to be user friendly, no idea how to
 * ensure that, maybe a string parser for variables?
 *
 * Maybe a polynomial builder that prints it as a string
 * as you toggle squares or add coefficients
 ****************************************************/
