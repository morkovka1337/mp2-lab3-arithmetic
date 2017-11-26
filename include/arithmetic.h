// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <iostream>
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
	Ariphmetic(char* s);
	int check();
	void PrintPolish();
	void SetVar();
	double calc();

};