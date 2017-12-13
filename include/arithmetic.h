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
	Lexem(const string& s, LexType l) { lexemstr = s; type = l; }
	Lexem& operator=(const Lexem & l) 
	{ 
		lexemstr = l.lexemstr; 
		type = l.type; 
		var = l.var; 
		priority = l.priority; 
		return *this; 
	}
	Lexem& operator=(const string &s) { lexemstr = s; deftype(s); return *this; }
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
	}
	void deftype(const string s);
};



class Arithmetic {
	string str;
	Lexem* pLexem;
	int nLexems;

	void Str_To_Lexems(const string s);

public:
	Arithmetic()
	{
		str = "";
		pLexem = 0;
		nLexems = 0;
	};
	Arithmetic(const string& s) 
	{
		str = s;
		pLexem = new Lexem[s.size()];
		nLexems = 0;
		Str_To_Lexems(str);
		if (pLexem[0].lexemstr == "-" && ((pLexem[1].type == VAL) || pLexem[1].type == VAR))//унарный минус в начале строки
		{
			if (pLexem[1].type == VAR)
				pLexem[1].SetVar();
			pLexem[1].var = -pLexem[1].var;
			for (int j = 1; j < nLexems - 1; j++)
			{
				pLexem[j] = pLexem[j + 1];
			}
			nLexems--;
		}
		for (int i = 0; i < nLexems - 3; i++) // унарный минус в виде (-a)
		{
			if ((pLexem[i].type == LBr) && (pLexem[i + 1].lexemstr == "-") && ((pLexem[i + 2].type == VAL)|| pLexem[i+2].type == VAR))
			{
				if (pLexem[1].type == VAR)
					pLexem[1].SetVar();
				pLexem[i + 2].var = 0 - pLexem[i + 2].var;
				for (int j = i + 1; j < nLexems - 1; j++)
				{
					pLexem[j] = pLexem[j + 1];
				}
				nLexems--;
			}
		}
	};
	void check(const string s);
	int GetnLexems() { return nLexems; };
	Arithmetic& operator +=(const Lexem a);
	Arithmetic PolishEntry();
	Lexem operator[] (int i);
	double Calc();
};
