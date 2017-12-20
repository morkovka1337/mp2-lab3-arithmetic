// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <iostream>
#include <string>
#include "stack.h"
#include <cctype>   // дл€ функции isdigit

using namespace std;
enum LexType {LBr, RBr, VAR, VAL, OPER, UNKOWN};

struct Lexem {
	string lexemstr;
	LexType type;
	double var;
	int priority;
	bool value_is_entered;

	Lexem() { lexemstr = "";  }
	Lexem(const Lexem & l)
	{
		lexemstr = l.lexemstr;
		type = l.type;
		var = l.var;
		priority = l.priority;
		value_is_entered = l.value_is_entered;
	}
	Lexem(const char c);
	Lexem(const string& s);
	Lexem& operator=(const Lexem & l) 
	{ 
		lexemstr = l.lexemstr; 
		type = l.type; 
		var = l.var; 
		priority = l.priority; 
		value_is_entered = l.value_is_entered;
		return *this; 
	}
//	Lexem& operator=(const string &s) { lexemstr = s; return *this; }
	void SetVar() { cout << "Enter value of " << (this)->lexemstr << " :" << endl; cin >> var; }
	bool operator == (const Lexem &l) 
	{ 
		int  temp = l.type;
		if (lexemstr != l.lexemstr)
			return false;
		else if (temp == OPER && (type == l.type || priority == l.priority))
			return true;
		else if (temp == VAL && var == l.var)
			return true;
		else return false;
	}
};



class Arithmetic {
	string str;
	Lexem* pLexem;
	int nLexems;

	Lexem* pLexemPolish;
	int nLexemsPolish;
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
	bool check();
	int GetnLexems() { return nLexems; };
	Arithmetic& operator +=(const Lexem& a);
	Arithmetic& operator =(const Arithmetic & a);
	void PolishEntry();
	Lexem GetPolishLex(int i);
	Lexem operator[] (int i);
	double Calc();
};
