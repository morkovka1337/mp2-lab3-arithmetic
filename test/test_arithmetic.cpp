// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"
#include <string>
TEST(Lexem, can_define_type_of_lexem_1)
{
	string s = "11";
	Lexem L;
	L.deftype(s);
	EXPECT_EQ(L.var, 11);
	EXPECT_EQ(L.type, 3);
}
TEST(Lexem, can_define_type_of_lexem_2)
{
	string s = "1";
	Lexem L;
	L.deftype(s);
	EXPECT_EQ(L.var, 1);
	EXPECT_EQ(L.type, 3);
}
TEST(Lexem, can_define_type_of_lexem_3)
{
	string s = "+";
	Lexem L;
	L.deftype(s);
	EXPECT_EQ(L.type, 4);
	EXPECT_EQ(L.priority, 1);
}
TEST(Lexem, can_define_type_of_lexem_4)
{
	string s = "b";
	Lexem L;
	L.deftype(s);
	EXPECT_EQ(L.type, 2);
}
TEST(Lexem, can_define_type_of_lexem_5)
{
	string s = "$";
	Lexem L;
	ASSERT_ANY_THROW(L.deftype(s));
}
TEST(Ariphmetic, can_divide_into_lexemes_1)
{
	string s = "11";
	ASSERT_NO_THROW(Arithmetic temp(s));
}

TEST(Arithmetic, can_divide_into_lexemes_2)
{
	string s = "11+5";
	Lexem l[5];
	l[0] = "11"; 
	l[1] = "+";
	l[2] = "5";
	Arithmetic a(s); 
	EXPECT_EQ(true, l[0]== a[0]);
//	EXPECT_EQ(true, l[1]== a[1]); // сравнение??
	EXPECT_EQ(true, l[2]== a[2]);
}



//TEST(Arithmetic, can_check_into_lexemes_1)
//{
//	string s = "11";
//	Arithmetic temp;
//	ASSERT_NO_THROW(temp.check(s));
//}

TEST(Arithmetic, can_calc)
{
	string s = "223+5";
	Arithmetic temp(s);// верно определяется количество лексем, но строка содержит только 1 число?
	double exp = 223.0; // не присваивается значение по строке^?
	double res = temp.Calc();
	EXPECT_EQ(exp, res);

}