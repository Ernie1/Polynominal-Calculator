#include"Control.h"
#include<stdlib.h>
#include<conio.h>
#include<iostream>
using namespace std;
int main() {
	read();
	while (1) {
		system("cls");
		printMenu();
		int ch;
		ch = _getch();
		if (ch == '1')
			save();
		else if (ch == '2')
			operate('+');
		else if (ch == '3')
			operate('-');
		else if (ch == '4')
			operate('*');
		else if (ch == '5')
			dif();
		else if (ch == '6')
			evl();
		else if (ch == '7')
			operate('=');
		else if (ch == '8')
			dsp();
		else if (ch == '9')
			res();
		else if (ch == '0')
			break;
		else if (ch == 27) {
			cout << "\n\nMain Menu Already!";
			_getch();
		}
		else if (ch == 0x00 || ch == 0xE0) {
			cout << "\nError Dictate!";
			_getch();
			_getch();
		}
		else if (ch == 'a' || ch == 'A') {
			cout << "\n\n> About\n\nEmail: 870949712@qq.com\n\nCopyright 2017 Zhang Jiqi,SYSU\nAll rights reserved.";
			_getch();
		}
		else {
			cout << "\nError Dictate!";
			_getch();
		}
	}
	write();
	return 0;
}