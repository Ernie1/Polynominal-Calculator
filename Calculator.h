#pragma once
#include"Polynominal.h"
using namespace std;
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)
class Calculator {
public:
	static Calculator* getInstance();
	static void deleteInstance();
	void addPoly(const string name, const Polynominal & poly);
	void Calculator::deletePoly(const string name);
	void printPoly(const string name);
	bool nameExist(const string name);
	void display();
	bool empty();
	Polynominal & getPoly(const string name);
	Polynominal left;
	Polynominal right;
	Polynominal current;
	void clear();
	void read();
	void write();
private:
	map<string, Polynominal> Poly;
	Calculator();
	~Calculator();
	static Calculator* instance;
	DISALLOW_COPY_AND_ASSIGN(Calculator);
};