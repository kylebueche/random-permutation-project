/****************************************************
 * Author: Kyle Bueche
 * File: polynomial.cpp
 *
 * Implementation of the Polynomial class
 *
 * In input lists, it starts counting values from 1
 ***************************************************/

#include "polynomial.h"

private:
    std::vector<std::vector<Real>> coefficients;

/*****************************************************
 * Thinking I could do this with a matrix?
 * Needs to be user friendly, no idea how to
 * ensure that, maybe a string parser for variables?
 *
 * Maybe a polynomial builder that prints it as a string
 * as you toggle squares or add coefficients
 ****************************************************/
void Polynomial::setRule(/* ??? Inputs ??? */)
{
    // Somehow sets internal matrix rule
    //
    // A rule can be a matrix that is just straight
    // added or transformed onto the coefficient matrix,
    // but an easier way is to store it as a list of instructions
    // to do with indices in a build input.
}


void Polynomial::build(std::vector<Real> variableArray)
{
    // Verify that the inputs are a permutaion of 1, 2, ..., variableArray.size()
    coefficients[i][j] += 
}

Real Polynomial::evaluate(std::vector<Real> variableInstances)
{

}

void Polynomial::printCoefficients()
{

}
