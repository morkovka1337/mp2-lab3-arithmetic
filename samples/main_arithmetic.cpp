// реализация пользовательского приложения

#include "arithmetic.h"
int main()
{
	string s = "22-2";
	double res;
	Arithmetic A(s);
	A.PolishEntry();
	res = A.Calc();
	cout << s << " = " << res << endl;
}
