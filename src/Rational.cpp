#include <iostream>
#include "Rational.hpp"

void Rational::set(int n, int d){
	num = n;
	denom = d;
}

Rational::Rational(){set(0, 1);}

Rational::Rational(int num, int denom){set(num, denom);}

Rational::Rational(const Rational& r){set(r.num, r.denom);}

Rational::~Rational(){};

void Rational::read(){
	std::string in;
	std::cin>>in;
	int n, d;
	std::string first, second;
	size_t i = 0;
	while (i < in.length() && in.at(i) != '/'){
		first.push_back(in.at(i));
		i++;
	}
	if (i < in.length()){
		i++;
		while (i < in.length()){
			second.push_back(in.at(i));
			i++;
		}
	}
	
	n = stoi(first);
	if (second.empty())
		d = 1;
	else
		d = stoi(second);
	set(n, d);
	if (denom == 0){
		std::cout<<"Il denominatore non può essere nullo. Numero posto a 0.\n";
		set(0, 1);
	}
}

void Rational::print() const{
	if (num % denom == 0)
		std::cout<<num/denom;
	else
		std::cout<<num<<"/"<<denom;
}

void Rational::operator = (Rational r){
	this->num = r.num;
	this->denom = r.denom;
}

bool Rational::operator != (Rational r) const { return !(*this == r); }

bool Rational::operator == (Rational r) const{
	Rational first = *this, second = r;
	first.simplify();
	second.simplify();
	return first.num == second.num && first.denom == second.denom;
}

Rational Rational::operator * (Rational r) const{
	Rational first = *this, second = r;
	first.simplify();
	second.simplify();
	Rational prod;
	prod.num = first.num * second.num;
	prod.denom = first.denom * second.denom;
	prod.simplify();
	return prod;
}

Rational Rational::operator / (Rational r) const{
	Rational first = *this, second = r;
	first.simplify();
	second.simplify();
	second = second.invert();
	return first * second;
}

Rational Rational::operator + (Rational r) const{
	Rational sum;
	if (this->denom == r.denom){
		sum.denom = this->denom;
		sum.num = this->num + r.num;
	}
	else{
		Rational first = *this, second = r;
		int lowest = this->denom > r.denom ? r.denom : this->denom;
		int highest = lowest == this->denom ? r.denom : this->denom;
		bool this_higher = highest == this->denom;
		if (highest % lowest == 0){
			if (this_higher){
				second.denom *= (highest / lowest);
				second.num *= (highest / lowest);
			}
			else{
				first.denom *= (highest / lowest);
				first.num *= (highest / lowest);
			}
		}
		else{
			first.denom *= r.denom;
			first.num *= r.denom;
			second.denom *= this->denom;
			second.num *= this->denom;
		}
		sum.denom = first.denom;
		sum.num = first.num + second.num;
	}
	sum.simplify();
	return sum;
}

Rational Rational::operator - (Rational r) const{
	Rational diff;
	if (this->denom == r.denom){
		diff.denom = this->denom;
		diff.num = this->num - r.num;
	}
	else{
		Rational first = *this, second = r;
		int lowest = this->denom > r.denom ? r.denom : this->denom;
		int highest = lowest == this->denom ? r.denom : this->denom;
		bool this_higher = highest == this->denom;
		if (highest % lowest == 0){
			if (this_higher){
				second.denom *= (highest / lowest);
				second.num *= (highest / lowest);
			}
			else{
				first.denom *= (highest / lowest);
				first.num *= (highest / lowest);
			}
		}
		else{
			first.denom *= r.denom;
			first.num *= r.denom;
			second.denom *= this->denom;
			second.num *= this->denom;
		}
		diff.denom = first.denom;
		diff.num = first.num - second.num;
	}
	diff.simplify();
	return diff;
}

void Rational::operator += (Rational r) { *this = *this + r; }

void Rational::operator *= (Rational r) { *this = *this * r; }

void Rational::operator /= (Rational r) { *this = *this / r; }

void Rational::operator -= (Rational r) { *this = *this - r; }

Rational Rational::operator % (Rational r) const{
	Rational first = *this;
	first.simplify();
	r.simplify();
	if (first.denom == 1 && r.denom == 1){
		Rational modulo;
		modulo.num = first.num % r.num;
		modulo.denom = 1;
		return modulo;
	}
	else{
		std::cout<<"Impossibile eseguire l'operazione di modulo tra numeri non interi."<<std::endl;
		exit(0);
	}
}

bool Rational::operator < (Rational r) const{
	float first = this->num / this->denom;
	float second = r.num / r.denom;
	return first < second;
}

bool Rational::operator > (Rational r) const{
	float first = this->num / this->denom;
	float second = r.num / r.denom;
	return first > second;
}

bool Rational::operator <= (Rational r) const{
	return *this < r || *this == r;
}

bool Rational::operator >= (Rational r) const{
	return *this > r || *this == r;
}

Rational Rational::invert(){
	Rational invert = *this;
	if (num == 0){
		invert.num = 0;
		invert.denom = 1;
	}
	else{
		int temp = invert.num;
		invert.num = invert.denom;
		invert.denom = temp;
	}
	return invert;
}

void Rational::simplify(){
	int i = 2;
	int lowest = num < denom ? num : denom;
	while(i < lowest){
		while ((num % i == 0) && (denom % i == 0)){
			num /= i;
			denom /= i;
		}
		i++;
	}
	if (denom < 0){
		denom = -denom;
		num = -num;
	}
	return;
}

int Rational::rtoi() const{
	if (num % denom == 0)
		return num / denom;
	else
		return -1;
}

bool Rational::is_integer() const{
	Rational temp = *this;
	temp.simplify();
	if (temp.denom != 1)
		return false;
	return true;
}