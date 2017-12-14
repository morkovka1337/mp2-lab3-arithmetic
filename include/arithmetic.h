// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <iostream>
#include <string>
#include "stack.h"
#include <cctype>   // дл€ функции isdigit

using namespace std;
enum LexType {LBr, RBr, VAR, VAL, OPER};

struct Lexem {
	string lexemstr;
	LexType type;
	double var;
	int priority;

	Lexem() { lexemstr = "";  }
	Lexem(const Lexem & l)
	{
		lexemstr = l.lexemstr;
		type = l.type;
		var = l.var;
		priority = l.priority;
	}
	Lexem(const char c);
	Lexem(const string& s);
	Lexem& operator=(const Lexem & l) 
	{ 
		lexemstr = l.lexemstr; 
		type = l.type; 
		var = l.var; 
		priority = l.priority; 
		return *this; 
	}
	Lexem& operator=(const string &s) { lexemstr = s; return *this; }
	void SetVar() { cout << "Enter value:" << endl; cin >> var; }
	bool operator == (const Lexem &l) 
	{ 
		int  temp = l.type;
		if (lexemstr != l.lexemstr)
			return false;
		else if (temp = OPER && (type == l.type || priority == l.priority))
			return true;
		else if (temp = VAL && var == l.var)
			return true;
		else return false;
	}/*
	void deftype(const string s);*/
};



class Arithmetic {
	string str;
	Lexem* pLexem;
	int nLexems;

	Lexem* pLexemPolish;
	int nLexemsPolish;
/*
	void Str_To_Lexems(const string s);*/

public:
	Arithmetic(int k = 0)
	{
		str = "";
		if (k > 0)
			pLexem = new Lexem[k];
		nLexems = 0;
	};
	Arithmetic(const Arithmetic& a);
	Arithmetic(const string& s);
	void check(const string s);
	int GetnLexems() { return nLexems; };
	Arithmetic& operator +=(const Lexem& a);
	Arithmetic& operator =(const Arithmetic & a);
	void PolishEntry();
	Lexem operator[] (int i);
	double Calc();
};
