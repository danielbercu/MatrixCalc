#pragma once

#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iostream>

struct rational_exception{
  enum err_type {invalid_format};
  err_type t;
  std::string msg;
};

class Rational {
  public:
  	Rational();
  	Rational(int num, int denom);
  	Rational(const Rational& r);
  	~Rational();
  	void read();
  	void print() const;
  	void operator = (Rational r);
  	bool operator == (Rational r) const;
  	bool operator != (Rational r) const;
  	Rational operator * (Rational r) const;
  	Rational operator / (Rational r) const;
  	Rational operator + (Rational r) const;
  	Rational operator - (Rational r) const;
  	void operator += (Rational r);
  	void operator *= (Rational r);
  	void operator /= (Rational r);
  	void operator -= (Rational r);
  	Rational operator % (Rational r) const;
  	bool operator < (Rational r) const;
  	bool operator > (Rational r) const;
  	bool operator <= (Rational r) const;
  	bool operator >= (Rational r) const;
  	Rational invert();
  	void simplify();
  	int rtoi() const;
  	bool is_integer() const;
  private:
  	void set(int n, int d);
  	int num;
  	int denom;
};

#endif
