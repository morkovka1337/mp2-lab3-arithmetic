// реализация пользовательского приложения

#include "arithmetic.h"
int main()
{
	string s = "22+3";
	double res;
	Arithmetic A(s);
	A.PolishEntry();
	res = A.Calc(); // возвращает последнюю лексему
	cout << s << " = " << res << endl;
}
