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
//�жϸ����������Ƿ�Ϸ�
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
//�ж϶���ʽ�����Ƿ�Ϸ�
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
//�ж����������Ƿ�Ϸ�
bool nameIsValid(const string input) {
	if (input.length() > 10)
		return false;
	for (size_t i = 0; i < input.length(); i++)
		if (!(input[i] >= 'a'&&input[i] <= 'z') && !(input[i] >= 'A'&&input[i] <= 'Z') && !(input[i] >= '0'&&input[i] <= '9'))
			return false;
	return true;
}
//�ж������Ƿ��Ѵ���
bool nameExist(const string input) {
	return(cal->nameExist(input));
}
//ʵ����ʱ���������ַ���
bool inputEsc(string & get) {
	int ch;
	while (1) {
		ch = _getch();
		if (ch == 0x00 || ch == 0XE0)	//if extended key
			_getch();	//gets scan code
		else if (ch == 27)
			return false;
		else if (ch == 8 && get.length() > 0) {
			cout << "\b \b";	// backspace, ������һ��
			get = get.substr(0, get.length() - 1);
		}
		else if (ch == '\r') {
			cout << "\n";
			if (get.length() == 0)
				continue;
			else
				break;
		}
		else if(ch >= 32 && ch <= 126) {	//�ɴ�ӡ�ַ�
			cout << static_cast<char> (ch);
			get += ch;
		}
	}
	return true;
}
//�˵�����
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
//ʶ���Ǿ������ʽ�������ƣ������кϷ����ж�
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
//���Ҷ���ʽ������
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
//����������ʽ
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
//�˵����� + - * == ����
void operate(const char ch) {
	while (1) {
		system("cls");
		//��ӡĿǰ����
		if (ch == '+')
			cout << "> Polynomial Calculator > Addition\n\n";
		else if (ch == '-')
			cout << "> Polynomial Calculator > Subtraction\n\n";
		else if (ch == '*')
			cout << "> Polynomial Calculator > Multiplication\n\n";
		else if (ch == '=')
			cout << "> Polynomial Calculator > Judgement\n\n";
		//��ʾ��¼
		if (!cal->empty()) {
			cout << ">Record:\n\n";
			cal->display();
			cout << endl;
		}
		//�������Ҷ���ʽ
		int flag = leftright();
		if (flag == 0)
			break;
		else if (flag == 1)
			continue;
		//�����Ҷ���ʽ������Ӧ����
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
		//������(�ж���ȳ���)
		if (ch != '=') {
			flag = saveResult();
			if (flag == 0)
				break;
			else if (flag == -1) {
				break;
			}
		}
		//�ж���ȵ�ѡ�񷵻ػ����
		else{
			cout << "\nPress Esc to return, other keys to continue";
			if (_getch() == 27)
				break;
		}
		continue;
	}
}
//�˵�����
void dif() {
	while (1) {
		system("cls");
		string left;
		//��ӡĿǰ����
		cout << "> Polynomial Calculator > Differentiation\n\n";
		//��ʾ��¼
		if (!cal->empty()) {
			cout << ">Record:\n\n";
			cal->display();
			cout << endl;
		}
		//�������ʽ
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
		//������
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
//�˵�����
void evl() {
	while (1) {
		system("cls");
		string left, right;
		//��ӡĿǰ����
		cout << "> Polynomial Calculator > Evaluation\n\n";
		//��ʾ��¼
		if (!cal->empty()) {
			cout << ">Record:\n\n";
			cal->display();
			cout << endl;
		}
		//�������ʽ
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
		//����x��ֵ
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
		//��ӡ���
		cout << endl << cal->left << " = " << cal->left.evaluate(assign) << " when x = "
			<< assign << endl;
		cout << "\nPress Esc to return, other keys to continue";
		if (_getch() == 27)
			break;
		continue;
	}
}
//�˵�����
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
		//��¼�ǿ�
		else {
			cal->display();
			//ѡ��ɾ��ĳ����¼�򷵻�
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
//�˵�����
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
//���ļ�
void read() {
	cal->read();
}
//д�ļ�
void write() {
	cal->write();
}