// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <iostream>
#include <string>
#include "stack.h"

using namespace std;
enum LexType {LBr, RBr, VAR, VAL, OPER};

struct Lexem {
	char name[10];
	LexType type;
	double var;
	int priority;

	Lexem () {};
	Lexem(char *s, LexType l) { strcpy(name, s), type = l; }
	Lexem operator=(const Lexem & l) { strcpy(name, l.name); type = l.type; var = l.var; priority = l.priority; }
	void SetVar() { cout << "Enter value:" << endl; cin >> var; }
	bool operator == (const Lexem &l) { if ((name != l.name) || (type != l.type) || (var != l.var) || (priority != l.priority)) return 0; else return 1; }

	Lexem(char* s, int k);
	
};

Lexem::Lexem(char* s, int k)
{
	strncpy(name, s, k);
	name[k] = '\0';

	if (k == 1)
	{
		if ('name' > 47 & 'name' < 58)
		{
			type = VAL;
			var = atof(name);
		}
		if (('name' > 64 & 'name' < 91) || ('name' > 96 & 'name' < 123))
		{
			type = VAR;
		}
		if ('name' == '(')
		{
			type = LBr;
			priority = 0;
		}
		if ('name' == ')')
		{
			type = RBr;
			priority = 0;
		}
		if ('name' == '+')
		{
			type = OPER;
			priority = 1;
		}
		if ('name' == '-')
		{
			type = OPER;
			priority = 1;
		}
		if ('name' == '*')
		{
			type = OPER;
			priority = 2;
		}
		if ('name' == '/')
		{
			type = OPER;
			priority = 2;
		}
		if (('name' < 40) || ('name' == 44) || ('name' == 46) || (('name' > 57) & ('name' < 65)) || (('name' > 90) & ('name' < 97)) || ('name' > 122))
		{
			throw "incorrect symbol";
		}
	}
	else if (k != 1)
	{
		type = VAL;
		var = atof(name);
	}
}

class Ariphmetic {
	Lexem* pLexem;
	int Size;
	int nLexems;
public:
	Ariphmetic() { Size = 0; nLexems = 0; };
	int check();
	void PrintPolish();
	void SetVar();
	double calc();
	Ariphmetic Str_To_Lexems(const string s);

};
Ariphmetic Ariphmetic::Str_To_Lexems(const string s)
{
	string opers = "+-*/";
	string str;
	int n = 0, i = 0;
	Ariphmetic temp;
	size_t OldPos, pos;
	n = 0; OldPos = 0;
	temp.Size = s.length();
	pos = s.find_first_of(opers);
	while (pos != s.npos)
	{
		if ((pos - OldPos) > 1)
		{
			str = s.substr(OldPos, pos - OldPos);
			temp.pLexem[i] = str;
			i++;
		}
		OldPos = pos + 1;
		pos = s.find_first_of(opers, OldPos);
	}
	if (OldPos < s.length)
	{
		temp.pLexem[i] = s.substr(OldPos);
	}
};