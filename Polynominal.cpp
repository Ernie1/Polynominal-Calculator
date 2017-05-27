#include"Polynominal.h"
#include<string>
#include<cmath>
#include<sstream>
using namespace std;
Polynominal::Polynominal(){}
Polynominal::Polynominal(const Polynominal & source) {
	for (auto & x : source.Term)
		Term.insert(pair<int, float>(x.first, x.second));
}
Polynominal::Polynominal(const string input) {
	int count = 0;
	for (size_t i = 0; i < input.length(); i++)
		if (input[i] == '(')
			count++;
	stringstream in(input);
	for (int i = 0; i < count; i++) {
		int exp;
		float coef;
		char ch;
		in >> ch >> coef >> ch >> exp >> ch;
		addTerm(exp, coef);
	}
}
Polynominal::~Polynominal() {
	Term.clear();
}
Polynominal Polynominal::operator+(const Polynominal & right) {
	Polynominal des(*this);
	for (auto & x : right.Term)
		des.addTerm(x.first, x.second);
	return des;
}
Polynominal Polynominal::operator-(const Polynominal & right) {
	Polynominal des(*this);
	for (auto & x : right.Term)
		des.addTerm(x.first, x.second*(-1));
	return des;
}
Polynominal Polynominal::operator*(const Polynominal & right) {
	Polynominal result;
	for (auto & i : Term)
		for (auto & j : right.Term)
			result.addTerm(i.first + j.first, i.second*j.second);
	return result;
}
Polynominal & Polynominal::operator=(const Polynominal & source) {
	Term.clear();
	for (auto & x : source.Term)
		Term.insert(pair<int, float>(x.first, x.second));
	return *this;
}
Polynominal & Polynominal::operator=(const string Input) {
	Term.clear();
	string input = Input;
	while (1) {
		stringstream in(input);
		int exp;
		float coef;
		char ch;
		in >> ch >> coef >> ch >> exp >> ch;
		addTerm(exp, coef);
		size_t pos = input.find(')') + 1;
		if (pos >= input.length())
			break;
		input = input.substr(pos);
	}
	return *this;
}
float Polynominal::evaluate(float num) {
	float value = 0;
	for (auto & x : Term)
		value += x.second*pow(num, x.first);
	return value;
}
Polynominal Polynominal::differentiate() {
	Polynominal result;
	for (auto & x : Term)
		if (x.first != 0)
			result.addTerm(x.first - 1, x.second*x.first);
	return result;
}
bool Polynominal::operator==(const Polynominal & other) {
	auto iter = other.Term.begin();
	for (auto & x : Term) {
		if (iter == other.Term.end())
			return false;
		if (x.first != iter->first || fabs(x.second - iter->second) >= 1e-6)
			return false;
		iter++;
	}
	return true;
}
bool Polynominal::invalid_0() {
	auto iter = Term.begin();
	if (iter->first < 0)
		return true;
	return false;
}
bool Polynominal::empty() {
	return Term.empty();
}
ostream & operator<<(ostream & out, const Polynominal & Poly) {
	if (Poly.Term.empty())
		out << "0";
	else {
		for (auto iter = Poly.Term.rbegin(); iter != Poly.Term.rend(); iter++) {
			if (iter->first == 0)
				out << iter->second;
			else {
				if (fabs(iter->second + 1) < 1e-6)
					out << "-";
				else if (fabs(iter->second - 1) >= 1e-6)
					out << iter->second;
				out << "x";
				if (iter->first != 1) {
					if (iter->first > 0)
						out << "^" << iter->first;
					else
						out << "^" << "(" << iter->first << ")";
				}
			}
			auto itor = iter;
			if (++itor != Poly.Term.rend() && itor->second > 0)
				out << "+";
		}
	}
	return out;
}
void Polynominal::addTerm(int exp, float coef) {
	if (fabs(coef) < 1e-6)
		return;
	auto iter = Term.find(exp);
	if (iter == Term.end())
		Term.insert(pair<int, float>(exp, coef));
	else {
		iter->second += coef;
		if (fabs(iter->second) < 1e-6)
			Term.erase(iter);
	}
}