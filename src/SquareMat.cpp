#include <iostream>
#include <vector>
#include "SquareMat.hpp"
#include "Rational.hpp" 

SquareMat::SquareMat(){
	this->mat.resize(0);
};

// predefinita
void SquareMat::read() {
    for (int i = 0; i < size(); ++i)
        for (int j = 0; j < size(); ++j)
            at(i, j).read();
    std::cout << '\n';
}

// predefinita
void SquareMat::print() const {
    for (int i = 0; i < size(); ++i) {
        for (int j = 0; j < size(); ++j){
        	at(i, j).print();
        	std::cout<<"     ";
        	if (at(i, j).is_integer())
        		std::cout<<" ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

SquareMat::SquareMat(int dim){
	mat.resize(dim);
	for (int i = 0; i < size(); i++){
		mat.at(i).resize(dim);
	}
	dummy = {0, 1};
}

SquareMat::SquareMat(const SquareMat& s){
	this->mat = s.mat;
}

SquareMat::~SquareMat(){}	//fa niente pk tanto i vector sono già cosati

Rational& SquareMat::at(int r, int c){
	if (r < 0 || c < 0 || (size_t) r > mat.size() || (size_t) c > mat.size())
		return dummy;
	return mat.at(r).at(c);
}

const Rational& SquareMat::at(int r, int c) const{
	if (r < 0 || c < 0 || (size_t) r > mat.size() || (size_t) c > mat.size())
		return dummy;
	return mat.at(r).at(c);
}

int SquareMat::size() const{
	return mat.size();
}

SquareMat SquareMat::reduce(int r, int c) const{
	if (r < 0 || c < 0 || (size_t) r > mat.size() || (size_t) c > mat.size())
		exit(0);

	SquareMat red{size() - 1};

	for (int i = 0; i < size(); i++)
		for (int j = 0; j < size(); j++)
			if (i != r && j != c){
				if (i <= r && j <= c)	red.mat.at(i).at(j) = mat.at(i).at(j);
				if (i > r && j <= c)	red.mat.at(i - 1).at(j) = mat.at(i).at(j);
				if (i <= r && j > c)	red.mat.at(i).at(j - 1) = mat.at(i).at(j);
				if (i > r && j > c)		red.mat.at(i - 1).at(j - 1) = mat.at(i).at(j);
			}

	return red;

}

Rational SquareMat::determinant() const{
	if (size() == 2)
		return mat.at(0).at(0) * mat.at(1).at(1) - mat.at(0).at(1) * mat.at(1).at(0);

	Rational ZERO{0, 1};
	Rational ONE{1, 1};
	Rational MONE{-1, 1};

	std::vector<Rational> first_row = mat.at(0);
	Rational det = ZERO, coeff = ONE;
	for (size_t i = 0; i < first_row.size(); i++){
		coeff = i % 2 == 0 ? ONE : MONE;
		det += coeff * first_row.at(i) * this->reduce(0, i).determinant();
	}
	return det;
}

bool SquareMat::allprimes() const{

	Rational ONE{1, 1};
	Rational TWO{2, 1};

	bool all_primes = true;
	for (int i = 0; i < size(); i++){
		for (int j = 0; j < size(); j++){
			for (int k = 2; k < mat.at(i).at(j).rtoi(); k++){
				if (mat.at(i).at(j).is_integer() == true){
					int n = (int) mat.at(i).at(j).rtoi();
					if (n % k == 0)
						all_primes = false;
				}
				else all_primes = false;
			}
		}
	}
	return all_primes;
}

SquareMat SquareMat::transpose() const{
	SquareMat tr {size()};

	for (int i = 0; i < size(); i++){
		for (int j = 0; j < size(); j++){
			tr.mat.at(i).at(j) = mat.at(j).at(i);
		}
	}

	return tr;
}

SquareMat SquareMat::inverse() const{

	Rational ZERO{0, 1};
	Rational MZERO{-0, 1};
	Rational ONE{1, 1};
	Rational MONE{-1, 1};

	if (this->determinant() == ZERO){
		std::cout<<"Impossibile calcolare l'inversa.\n";
		exit(0);
	}

	SquareMat temp {size()};

	if (size() == 2){
		temp.at(0, 0) = this->at(1, 1) / this->determinant();
		temp.at(0, 1) = MONE * this->at(0, 1) / this->determinant();
		temp.at(1, 0) = MONE * this->at(1, 0) / this->determinant();
		temp.at(1, 1) = this->at(0, 0) / this->determinant();
		for (int i = 0; i < size(); i++)
			for (int j = 0; j < size(); j++){
				temp.at(i, j).simplify();
				if (temp.at(i, j) == MZERO) temp.at(i, j) = ZERO;
			}
	}
	else{
		Rational coeff = {1, 1};
		for (int i = 0; i < size(); i++){
			for (int j = 0; j < size(); j++){
				coeff = (i + j) % 2 == 0 ? ONE : MONE;
				temp.at(i, j) = coeff * this->reduce(j, i).determinant() / this->determinant();
				if (temp.at(i, j) == MZERO) temp.at(i, j) = ZERO;
				temp.at(i, j).simplify();
			}
		}
	}
	
	return temp;
}

void SquareMat::operator = (SquareMat a){
	this->mat = a.mat;
}

bool SquareMat::operator == (SquareMat a) const{
	if (size() != a.size())
		return false;
	bool same = true;
	for (int i = 0; i < size(); i++){
		for (int j = 0; j < size(); j++){
			if (this->at(i, j) != a.at(i, j))
				same = false;
		}
	}
	return same;
}

bool SquareMat::orthogonal() const{
	Rational ZERO{0, 1};
	return this->determinant() != ZERO ? this->transpose() == this->inverse() : false;
}

SquareMat SquareMat::operator* (SquareMat a) const{
	if (size() != a.size()){
		std::cout<<"Impossibile eseguire la moltiplicazione. Dimensioni delle matrici diverse.\n";
		exit(0);
	}
	
	SquareMat prod {size()};

	for (int i = 0; i < size(); i++){
		for (int j = 0; j < size(); j++){
			for (int k = 0; k < size(); k++){
				prod.at(i, j) += this->at(i, k) * a.at(k, j);
			}
		}
	}

	return prod;
}

SquareMat SquareMat::operator+ (SquareMat a) const{
	if (size() != a.size()){
		std::cout<<"Impossibile eseguire la somma. Dimensioni delle matrici diverse.\n";
		exit(0);
	}

	SquareMat sum {size()};

	for (int i = 0; i < size(); i++){
		for (int j = 0; j < size(); j++){
			sum.at(i, j) = this->at(i, j) + a.at(i, j);
		}
	}

	return sum;
}

void SquareMat::create(){
	int dim = -1;
	std::string in;
	std::cout<<"Inserisci la lunghezza della riga/colonna della matrice: ";
    std::cin>>in;
    size_t i = 0;
    while(i < in.length() && in.at(i) >= '0' && in.at(i) <= '9'){
    	int temp = in.at(i) - 48;
    	if (dim == -1)
    		dim = temp;
    	else
    		dim += temp;
    	i++;
    }
    if (i != in.length()){
    	throw matrix_exception{matrix_exception::invalid_format, "Formato non valido.\n"};
    }
    if (dim == 0){
		throw matrix_exception{matrix_exception::null_matrix, "Matrice nulla."};
	}

    this->mat.resize(dim);
    for (size_t i = 0; i < mat.size(); i++){
    	this->mat.at(i).resize(dim);
    }
    std::cout<<"Inserisci gli elementi della matrice:\n";
    this->read();
    this->print();
}

int SquareMat::rank() const{
	
	if (empty()){
		std::cout<<"Matrice nulla. ";
		return 0;
	}

	Rational ZERO{0, 1};

	SquareMat temp = this->MEG();
	int rk = 0;
	for (int i = 0; i < size(); i++){
		if (temp.at(i, i) != ZERO)
			rk++;
	}

	return rk;
}

SquareMat SquareMat::MEG() const{
	if (empty()){
		std::cout<<"Matrice nulla.\n";
		exit(0);
	}

	SquareMat temp {*this};
	Rational ZERO{0, 1};

	for (int i = 0; i < size(); i++){
		if (temp.mat.at(i).at(i) == ZERO){
			int t = i + 1;
			bool modified = false;
			while(t < size() && !modified){
				if (!modified && temp.mat.at(t).at(0) != ZERO){
					std::vector<Rational> curr_row = temp.mat.at(i);
					temp.mat.at(i) = temp.mat.at(t);
					temp.mat.at(t) = curr_row;
					modified = true;
				}
				t++;
			}
		}

		for (int j = i + 1; j < size(); j++){			
			Rational coeff = temp.at(j, i) * temp.at(i, i).invert();
			for (int k = 0; k < size(); k++){
				temp.mat.at(j).at(k) = temp.mat.at(j).at(k) - coeff * temp.mat.at(i).at(k);
			}

		}
	}

	return temp;
}

bool SquareMat::empty() const{
	Rational ZERO{0, 1};
	bool allzero = true;
	for (int i = 0; i < size(); i++){
		for (int j = 0; j < size(); j++){
			if (mat.at(i).at(j) != ZERO)
				allzero = false;
		}
	}
	return allzero;
}
