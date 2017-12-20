// реализация пользовательского приложения
#include <cstdio>

#include "arithmetic.h"
int main()
{
	string expression;
	cout << "enter expression" << endl;
	cin >> expression;
	//string s = "1+2*(3-2)-4";
	double res;
	Arithmetic A(expression);
	if (A.check())
	{
		A.PolishEntry();
		Arithmetic B(A);
		int menu = 1;
		res = B.Calc();
		cout << expression << " = " << res << endl;
		cout << "Do you want to calculate again with another variables?" << endl;
		cout << " 0 - exit; other - calc again" << endl;
		cin >> menu;
		while (menu != 0)
		{
			res = A.Calc();
			cout << expression << " = " << res << endl;
			cout << "Do you want to calculate again with another variables?" << endl;
			cout << " 0 - exit; other - calc again" << endl;
			cin >> menu;
		}
	}
	else cout << "wrong expression!" << endl;
}
