#pragma once

#ifndef SQUAREMAT_HPP
#define SQUAREMAT_HPP

#include <iostream>
#include <vector>
#include "Rational.hpp"

class SquareMat {
  public:
  	SquareMat();
    SquareMat(int dim);						//Constructor
    SquareMat(const SquareMat& s);			//Copy constructor
    ~SquareMat();							//Destructor
    void read();							//Fill the matrix
    Rational& at(int r, int c);				//Return the element in position (r,c)
    const Rational& at(int r, int c) const;	//Return the element in position (r,c)
    void print() const;						//Print the matrix
    SquareMat reduce(int r, int c) const;	//Create a new matrix without row r and column c
    Rational determinant() const;			//Calculate the matrix's determinant
    int size() const;						//Return matrix's side's size
    bool allprimes() const;					//Check if every number in the matrix is prime

    SquareMat transpose() const;			//Calculate the matrix's transpose
    SquareMat inverse() const;				//Calculate the matrix's inverse
    bool operator == (SquareMat a) const;	//Check if two matrix have the same elements
    void operator = (SquareMat a);			//Copy assignment
    bool orthogonal() const;				//Checks if the matrix is orthogonal
    SquareMat operator * (SquareMat a) const;	// *
    SquareMat operator + (SquareMat a) const;	// +
    SquareMat create();
    int rank() const;
    SquareMat MEG() const;
    bool empty() const;
  private:
    std::vector<std::vector<Rational>> mat;		//A matrix is based on a two-dimensional vector of integers
    Rational dummy;								//Dummy variable
};

#endif
