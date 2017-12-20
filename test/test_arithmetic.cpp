// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"
#include <string>
TEST(Lexem, can_define_type_of_lexem_1)
{
	string s = "11";
	Lexem L(s);
	EXPECT_EQ(L.var, 11);
	EXPECT_EQ(L.type, 3);
}
TEST(Lexem, can_define_type_of_lexem_2)
{
	string s = "1";
	Lexem L(s);
	EXPECT_EQ(L.var, 1);
	EXPECT_EQ(L.type, 3);
}
TEST(Lexem, can_define_type_of_lexem_3)
{
	string s = "+";
	Lexem L(s);
	EXPECT_EQ(L.type, 4);
	EXPECT_EQ(L.priority, 2);
}
TEST(Lexem, can_define_type_of_lexem_4)
{
	string s = "b";
	Lexem L(s);
	EXPECT_EQ(L.type, 2);
}
TEST(Lexem, can_define_type_of_lexem_5)
{
	string s = "$";
	Lexem L(s);
	EXPECT_EQ(L.type, 5);
}
TEST(Ariphmetic, can_divide_into_lexemes_1)
{
	string s = "11";
	ASSERT_NO_THROW(Arithmetic temp(s));
}
TEST(Arithmetic, can_calc_with_unary_minus)
{
	string s = "-3+5";
	Arithmetic temp(s);
	temp.PolishEntry();
	double exp = 2.0;
	double res = temp.Calc();
	EXPECT_EQ(exp, res);

}
TEST(Arithmetic, can_calc_with_unary_minus_3)
{
	string s = "-3+(-5)";
	Arithmetic temp(s);
	temp.PolishEntry();
	double exp = -8.0;
	double res = temp.Calc();
	EXPECT_EQ(exp, res);

}

TEST(Arithmetic, can_calc_with_unary_minus_2)
{
	string s = "-8*(9+1)*2+3*(2+7)/2";
		Arithmetic temp(s);
	temp.PolishEntry();
	double exp = -146.5;
	double res = temp.Calc();
	EXPECT_EQ(exp, res);

}
TEST(Arithmetic, can_calc_with_brackets_2)
{
	string s = "(1+1)";
	Arithmetic temp(s);
	temp.PolishEntry();
	double exp = 2.0;
	double res = temp.Calc();
	EXPECT_EQ(exp, res);

}

TEST(Arithmetic, can_divide_into_lexemes_2)
{
	string s = "11+5";
	Lexem l[5];
	l[0] = Lexem("11"); 
	l[1] = Lexem('+');
	l[2] = Lexem("5");
	Arithmetic a(s); 
	EXPECT_EQ(true, l[0]==a[0]);
	EXPECT_EQ(true, l[1]==a[1]); 
	EXPECT_EQ(true, l[2]==a[2]);
}

TEST(Arithmetic, can_transform_into_polish_1)
{
	string s = "-3+5";
	Lexem l[5];
	l[0] = Lexem("0");
	l[1] = Lexem('3');
	l[2] = Lexem("-");
	l[3] = Lexem("5");
	l[4] = Lexem("+");
	Arithmetic a(s);
	a.PolishEntry();
	EXPECT_EQ(true, l[0] == a.GetPolishLex(0));
	EXPECT_EQ(true, l[1] == a.GetPolishLex(1));
	EXPECT_EQ(true, l[2] == a.GetPolishLex(2));
	EXPECT_EQ(true, l[3] == a.GetPolishLex(3));
	EXPECT_EQ(true, l[4] == a.GetPolishLex(4));
}

TEST(Arithmetic, can_transform_into_polish_2)
{
	string s = "-3*5";
	Lexem l[6];
	l[0] = Lexem("0");
	l[1] = Lexem('3');
	l[2] = Lexem("5");
	l[3] = Lexem("*");
	l[4] = Lexem("-");
	Arithmetic a(s);
	a.PolishEntry();
	EXPECT_EQ(true, l[0] == a.GetPolishLex(0));
	EXPECT_EQ(true, l[1] == a.GetPolishLex(1));
	EXPECT_EQ(true, l[2] == a.GetPolishLex(2));
	EXPECT_EQ(true, l[3] == a.GetPolishLex(3));
	EXPECT_EQ(true, l[4] == a.GetPolishLex(4));
}

TEST(Arithmetic, can_transform_into_polish_3)
{
	string s = "1+3+4+5";
	Lexem l[7];
	l[0] = Lexem("1");
	l[1] = Lexem('3');
	l[2] = Lexem("+");
	l[3] = Lexem("4");
	l[4] = Lexem("+");
	l[5] = Lexem("5");
	l[6] = Lexem("+");
	Arithmetic a(s);
	a.PolishEntry();
	EXPECT_EQ(true, l[0] == a.GetPolishLex(0));
	EXPECT_EQ(true, l[1] == a.GetPolishLex(1));
	EXPECT_EQ(true, l[2] == a.GetPolishLex(2));
	EXPECT_EQ(true, l[3] == a.GetPolishLex(3));
	EXPECT_EQ(true, l[4] == a.GetPolishLex(4));
	EXPECT_EQ(true, l[5] == a.GetPolishLex(5));
	EXPECT_EQ(true, l[6] == a.GetPolishLex(6));
}
//тесты на перевод в польскую запись


TEST(Arithmetic, can_calc_without_brackets)
{
	string s = "22+3/5*2-4";
	//string s = "1+2+2*4";
	Arithmetic temp(s);
	temp.PolishEntry();
	double exp = 19.2; 
	double res = temp.Calc();
	EXPECT_EQ(exp, res);
}



TEST(Arithmetic, can_check_brackets_0)
{
	string s = "(1+2";
	Arithmetic temp(s);
	EXPECT_EQ(false, temp.check());
}

TEST(Arithmetic, can_check_brackets_1)
{
	string s = "(1+2))";
	Arithmetic temp(s);
	EXPECT_EQ(false, temp.check());
}

TEST(Arithmetic, can_check_brackets_2)
{
	string s = "1+2+(3-4)";
	Arithmetic temp(s);
	EXPECT_EQ(true, temp.check());
}


TEST(Arithmetic, can_check_operators)
{
	string s = "1+2++3";
	Arithmetic temp(s);
	EXPECT_EQ(false, temp.check());
}

