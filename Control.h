#pragma once
#include"Calculator.h"
#include<iostream>
#include<conio.h>
#include<string>
#include<stdlib.h>
using namespace std;

Calculator *cal = Calculator::getInstance();
void printMenu() {
	system("cls");
	cout << "> Polynomial Calculator\n\n"
		<< " 1 --- Save Polynominal\n"
		<< " 2 ----------- Addition\n"
		<< " 3 -------- Subtraction\n"
		<< " 4 ----- Multiplication\n"
		<< " 5 ---- Differentiation\n"
		<< " 6 --------- Evaluation\n"
		<< " 7 ----------- Judgment\n"
		<< " 8 ----- Display Record\n"
		<< " 9 -------------- Reset\n"
		<< " 0 --------------- Exit\n\n"
		<< "Instruction:";
}
//判断浮点数输入是否合法
bool floatValid(const string Input) {
	string input = Input;
	int leftp = -1;
	if (input[leftp + 1] != '+'&&input[leftp + 1] != '-'&&input[leftp + 1] != '.' && (input[leftp + 1]>'9' || input[leftp + 1]<'0'))
		return false;
	if (input[leftp + 1] == '+' || input[leftp + 1] == '-' || input[leftp + 1] == '.')
		if (input[leftp + 2]>'9' || input[leftp + 2]<'0')
			return false;
	int point = 0;
	if (input[leftp + 1] == '.')
		point = 1;
	size_t i;
	for (i = leftp + 2; i<input.length(); i++) {
		if (input[i] == '.') {
			point++;
			if (point>1)
				return false;
			if (input[i + 1]>'9' || input[i + 1]<'0')
				return false;
		}
		else if (input[i]>'9' || input[i]<'0')
			return false;
	}
	return true;
}
//判断多项式输入是否合法
bool polyIsValid(const string input) {
	if (input[0] != '(')
		return false;
	int leftp = 0, flag = 0, count = 0;
	while (1) {
		// (~,
		if (input[leftp + 1] != '+'&&input[leftp + 1] != '-'&&input[leftp + 1] != '.' && (input[leftp + 1]>'9' || input[leftp + 1]<'0'))
			return false;
		if (input[leftp + 1] == '+' || input[leftp + 1] == '-' || input[leftp + 1] == '.')
			if (input[leftp + 2]>'9' || input[leftp + 2]<'0')
				return false;
		int point = 0;
		if (input[leftp + 1] == '.')
			point = 1;
		size_t i;
		for (i = leftp + 2; i<input.find(',', leftp + 1); i++) {
			if (input[i] == '.') {
				point++;
				if (point>1)
					return false;
				if (input[i + 1]>'9' || input[i + 1]<'0')
					return false;
			}
			else if (input[i]>'9' || input[i]<'0')
				return false;
		}
		// ,~)
		if (input[i + 1] != '+'&&input[i + 1] != '-' && (input[i + 1]>'9' || input[i + 1]<'0'))
			return false;
		if (input[i + 1] == '+' || input[i + 1] == '-')
			if (input[i + 2]>'9' || input[i + 2]<'0')
				return false;
		for (i = i + 2; i<input.find(')', leftp + 1); i++)
			if (input[i]>'9' || input[i]<'0')
				return false;
		if (i + 1 == input.length())
			return true;
		if (input[i + 1] != '(')
			return false;
		leftp = i + 1;
		count++;
		if (count > 100)
			return false;
	}
}
//判断名称输入是否合法
bool nameIsValid(const string input) {
	if (input.length() > 10)
		return false;
	for (size_t i = 0; i < input.length(); i++)
		if (!(input[i] >= 'a'&&input[i] <= 'z') && !(input[i] >= 'A'&&input[i] <= 'Z') && !(input[i] >= '0'&&input[i] <= '9'))
			return false;
	return true;
}
//判断名称是否已存在
bool nameExist(const string input) {
	return(cal->nameExist(input));
}
//实现随时返回输入字符串
bool inputEsc(string & get) {
	int ch;
	while (1) {
		ch = _getch();
		if (ch == 0x00 || ch == 0XE0)	//if extended key
			_getch();	//gets scan code
		else if (ch == 27)
			return false;
		else if (ch == 8 && get.length() > 0) {
			cout << "\b \b";	// backspace, 光标回退一格
			get = get.substr(0, get.length() - 1);
		}
		else if (ch == '\r') {
			cout << "\n";
			if (get.length() == 0)
				continue;
			else
				break;
		}
		else if(ch >= 32 && ch <= 126) {	//可打印字符
			cout << static_cast<char> (ch);
			get += ch;
		}
	}
	return true;
}
//菜单功能
void save() {
	while (1) {
		system("cls");
		cout << "> Polynomial Calculator > Save a polynominal\n\n"
			<< "e.g. p=(1,2)(1,0)\n\n";
		int flag = 0;
		string input;
		if (!inputEsc(input))
			break;
		if (input.find(' ') != -1)
			flag = 1;
		else {
			size_t count = 0;
			for (size_t i = 1; i < input.length(); i++)	//i begin with 1
				if (input[i] == '=')
					count++;
			if (count != 1)
				flag = 1;
		}
		string name, poly;
		if (!flag) {
			name = input.substr(0, input.find('='));
			poly = input.substr(input.find('=') + 1);
			if (!polyIsValid(poly) || !nameIsValid(name))
				flag = 1;
			else if (nameExist(name))
				flag = 2;
		}
		if (flag == 0) {
			cal->current = poly;
			cal->addPoly(name, cal->current);
			cout << endl << name << " = ";
			cal->printPoly(name);
			cout << " successfully saved!\n\n"
				<< "Press any key to return";
			_getch();
			break;
		}
		if (flag == 1)
			cout << "\nSyntax Error!\n";
		else if (flag == 2)
			cout << "\nExistent Name!\n";
		cout << "\nPress Esc to return, other keys to continue";
		if (_getch() == 27)
			break;
	}
}
//识别是具体多项式或是名称，并进行合法性判断
int judge(const string target) {
	int flag = 0;
	if (target.find(' ') != -1)
		flag = 1;
	else {
		if (target[0] == '(') {
			if (!polyIsValid(target))
				flag = 1;
			else
				flag = 2;
		}
		else {
			if (!nameIsValid(target))
				flag = 1;
			else
				flag = 3;
		}
		if (flag == 3 && !nameExist(target))
			flag = 4;
		if (flag == 1)
			cout << "\nSyntax Error!\n";
		else if (flag == 4)
			cout << "\nNon-Existent Name!\n";
	}
	return flag;
}
//左右多项式的输入
int leftright() {
	string left, right;
	cout << "Input a concrete polynominal or its name if only existed.\n\n";
	cout << "Lvalue:\n";
	if (!inputEsc(left))
		return 0;
	int flag = judge(left);
	if (flag == 1 || flag == 4) {
		cout << "\nPress Esc to return, other keys to continue";
		if (_getch() == 27)
			return 0;
		return 1;
	}
	else if (flag == 2)
		cal->left = left;
	else if (flag == 3)
		cal->left = cal->getPoly(left);
	cout << "\nRvalue:\n";
	if (!inputEsc(right))
		return 0;
	flag = judge(right);
	if (flag == 1 || flag == 4) {
		cout << "\nPress Esc to return, other keys to continue";
		if (_getch() == 27)
			return 0;
		return 1;
	}
	else if (flag == 2)
		cal->right = right;
	else if (flag == 3)
		cal->right = cal->getPoly(right);
	return 2;
}
//保存结果多项式
int saveResult() {
	cout << "\nInput 1 to return, 2 to save the result, other to continue\n";
	string ch;
	if (!inputEsc(ch))
		return 0;
	if (ch == "1")
		return 0;
	if (ch == "2") {
		while (1) {
			string name;
			cout << "\nName:\n";
			if(!inputEsc(name))
				return 0;
			if (!nameIsValid(name)) {
				cout << "\nSyntax Error!\n";
				continue;
			}
			if (nameExist(name)) {
				cout << "\nExistent Name!\n";
				continue;
			}
			cal->addPoly(name, cal->current);
			cout << endl << name << " = ";
			cal->printPoly(name);
			cout << " successfully saved!\n\n"
				<< "Press any key to return";
			_getch();
			return -1;
		}
	}
	return 1;
}
//菜单功能 + - * == 操作
void operate(const char ch) {
	while (1) {
		system("cls");
		//打印目前功能
		if (ch == '+')
			cout << "> Polynomial Calculator > Addition\n\n";
		else if (ch == '-')
			cout << "> Polynomial Calculator > Subtraction\n\n";
		else if (ch == '*')
			cout << "> Polynomial Calculator > Multiplication\n\n";
		else if (ch == '=')
			cout << "> Polynomial Calculator > Judgement\n\n";
		//显示记录
		if (!cal->empty()) {
			cout << ">Record:\n\n";
			cal->display();
			cout << endl;
		}
		//输入左右多项式
		int flag = leftright();
		if (flag == 0)
			break;
		else if (flag == 1)
			continue;
		//对左右多项式进行相应操作
		if (ch == '+') {
			cal->current = cal->left + cal->right;
			cout << endl << "(" << cal->left << ")+(" << cal->right << ") = "
				<< cal->current << endl;
		}
		else if (ch == '-') {
			cal->current = cal->left - cal->right;
			cout << endl << "(" << cal->left << ")-(" << cal->right << ") = "
				<< cal->current << endl;
		}
		else if (ch == '*') {
			cal->current = cal->left * cal->right;
			cout << endl << "(" << cal->left << ")*(" << cal->right << ") = "
				<< cal->current << endl;
		}
		else if (ch == '=') {
			if (cal->left == cal->right)
				cout << endl << cal->left << " = " << cal->right << endl;
			else
				cout << endl << cal->left << " != " << cal->right << endl;
		}
		//保存结果(判断相等除外)
		if (ch != '=') {
			flag = saveResult();
			if (flag == 0)
				break;
			else if (flag == -1) {
				break;
			}
		}
		//判断相等的选择返回或继续
		else{
			cout << "\nPress Esc to return, other keys to continue";
			if (_getch() == 27)
				break;
		}
		continue;
	}
}
//菜单功能
void dif() {
	while (1) {
		system("cls");
		string left;
		//打印目前功能
		cout << "> Polynomial Calculator > Differentiation\n\n";
		//显示记录
		if (!cal->empty()) {
			cout << ">Record:\n\n";
			cal->display();
			cout << endl;
		}
		//输入多项式
		cout << "Input a concrete polynominal or its name if only existed.\n\n";
		cout << "Object:\n";
		if (!inputEsc(left))
			break;
		int flag = judge(left);
		if (flag == 1 || flag == 4) {
			cout << "\nPress Esc to return, other keys to continue";
			if (_getch() == 27)
				break;
			continue;
		}
		else if (flag == 2)
			cal->left = left;
		else if (flag == 3)
			cal->left = cal->getPoly(left);
		cal->current = cal->left.differentiate();
		cout << endl << "(" << cal->left << ")' = " << cal->current << endl;
		//保存结果
		flag = saveResult();
		if (flag == 0)
			break;
		else if (flag == -1) {
			cin.ignore();
			break;
		}
		continue;
	}
}
//菜单功能
void evl() {
	while (1) {
		system("cls");
		string left, right;
		//打印目前功能
		cout << "> Polynomial Calculator > Evaluation\n\n";
		//显示记录
		if (!cal->empty()) {
			cout << ">Record:\n\n";
			cal->display();
			cout << endl;
		}
		//输入多项式
		cout << "Input a concrete polynominal or its name if only existed.\n\n";
		cout << "Object:\n";
		if (!inputEsc(left))
			break;
		int flag = judge(left);
		if (flag == 1 || flag == 4) {
			cout << "\nPress Esc to return, other keys to continue";
			if (_getch() == 27)
				break;
			continue;
		}
		else if (flag == 2)
			cal->left = left;
		else if (flag == 3)
			cal->left = cal->getPoly(left);
		//输入x的值
		float assign;
		bool tem = false;
		while (1) {
			cout << "\nx = ";
			if (!inputEsc(right)) {
				tem = true;
				break;
			}
			if (floatValid(right)) {
				const char* input = right.c_str();
				assign = (float)atof(input);
				break;
			}
			else
				cout << "\nSyntax Error!\n"; 
		}
		if (tem)
			break;
		//打印结果
		cout << endl << cal->left << " = " << cal->left.evaluate(assign) << " when x = "
			<< assign << endl;
		cout << "\nPress Esc to return, other keys to continue";
		if (_getch() == 27)
			break;
		continue;
	}
}
//菜单功能
void dsp() {
	while (1) {
		system("cls");
		string left, right;
		cout << "> Polynomial Calculator > Display Record\n\n";
		if (cal->empty()) {
			cout << "Empty!\n\nPress any key to return";
			_getch();
			break;
		}
		//记录非空
		else {
			cal->display();
			//选择删除某条记录或返回
			cout << "\nPress D to delete a polynominal, Esc to return";
			char ch = _getch();
			if (ch == 'D' || ch == 'd') {
				while (1) {
					system("cls");
					cout << "> Polynomial Calculator > Display Record > Delete A Record\n\n";
					cal->display();
					string name;
					cout << "\nName:\n";
					if (!inputEsc(name)) {
						ch = 27;
						break;
					}
					if (!nameExist(name)) {
						cout << "\nNon-Existent Name!\nPress Esc to return the menu, others to return\n";
						ch = _getch();
						break;
					}
					cout << "\nDelete " << name << " = ";
					cal->printPoly(name);
					cout << " ?\n\nPress Y to delete, Esc to return the menu, others to return.\n";
					ch = _getch();
					if (ch == 'y'||ch=='Y') {
						cal->deletePoly(name);
						cout << endl << name << " successfully deleted!";
						cout << "\nPress Esc to return the menu, others to return";
						ch = _getch();
					}
					break;
				}
			}
			if (ch == 27)
				break;
		}
	}
}
//菜单功能
void res() {
	system("cls");
	cout << "> Polynomial Calculator > Reset\n\n";
	cout << "Press Y to reset, other keys to return";
	char ch = _getch();
	if (ch == 'Y' || ch == 'y') {
		cal->clear();
		cout << "\n\nReset successfully! Press any key to return";
		_getch();
	}
}
//读文件
void read() {
	cal->read();
}
//写文件
void write() {
	cal->write();
}