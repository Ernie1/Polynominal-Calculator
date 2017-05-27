#include"Calculator.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

Calculator* Calculator::instance = NULL;
Calculator* Calculator::getInstance() {
	if (instance == NULL)
		instance = new Calculator;
	return instance;
}
void Calculator::deleteInstance() {
	if (instance != NULL)
		delete instance;
	instance = NULL;
}
void Calculator::addPoly(const string name, const Polynominal & poly) {
	Poly.insert(pair<string,Polynominal>(name, poly));
}
void Calculator::deletePoly(const string name) {
	Poly.erase(name);
}
void Calculator::printPoly(const string name) {
	cout << Poly.find(name)->second;
}
bool Calculator::nameExist(const string name) {
	if (Poly.find(name) != Poly.end())
		return true;
	return false;
}
void Calculator::display() {
	for (auto & x : Poly) {
		const char* out = x.first.c_str();
		cout << "  " << setw(10) << out << " = " << x.second << endl;
	}
}
bool Calculator::empty() {
	return Poly.empty();
}
Polynominal & Calculator::getPoly(const string name) {
	return Poly.find(name)->second;
}
void Calculator::clear() {
	Poly.clear();
}
void Calculator::read() {
	ifstream in("record", ios::binary | ios::in);
	if (in.is_open()) {
		while (in.peek() != EOF) {
			string name, poly;
			getline(in, name);
			getline(in, poly);
			current = poly;
			addPoly(name, current);
		}
		in.close();
	}
}
void Calculator::write() {
	ofstream out("record", ios::binary | ios::out);
	if (out.is_open()) {
		for (auto x : Poly) {
			const char* name = x.first.c_str();
			out << name << endl;
			for (auto y : x.second.Term)
				out << "(" << y.second << "," << y.first << ")";
			out << endl;
		}
		out.close();
	}
	else {
		cerr << "Unknown Error!";
		system("pause");
	}
}
Calculator::~Calculator() {
	Poly.clear();
}
Calculator::Calculator() {}