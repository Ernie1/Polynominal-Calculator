#pragma once
#include<map>
//#include"Term.h"
using namespace std;
class Polynominal {
public:
	Polynominal();
	Polynominal(const Polynominal & source);
	Polynominal(const string input);
	~Polynominal();
	Polynominal operator+(const Polynominal & right);
	Polynominal operator-(const Polynominal & right);
	Polynominal operator*(const Polynominal & right);
	Polynominal & operator=(const Polynominal & source);
	Polynominal & operator=(const string Input);
	Polynominal differentiate();
	float evaluate(float num);
	bool operator==(const Polynominal & other);
	bool invalid_0();
	bool empty();
	friend ostream & operator<<(ostream & out, const Polynominal & Poly);

	map<int, float> Term;
	void addTerm(int exp, float coef);
};