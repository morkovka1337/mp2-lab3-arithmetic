// ���������� ������� � ������� ��� ���������� �������������� ���������

#include <iostream>
#include <string>
#include "stack.h"
#include <cctype>   // ��� ������� isdigit

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
	Lexem operator=(const string s) { var = 's'; }
	void SetVar() { cout << "Enter value:" << endl; cin >> var; }
	bool operator == (const Lexem &l) { if ((name != l.name) || (type != l.type) || (var != l.var) || (priority != l.priority)) return 0; else return 1; }

	void deftype(string s, int k);
	
};

void Lexem::deftype(string s, int k)
{
	strncpy(name, s.c_str(), k);
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
	Ariphmetic(int s = 0, int NL = 0) { Size = s; nLexems = NL; };
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
	Ariphmetic temp (s.length());
	size_t OldPos, pos;
	n = 0; OldPos = 0, pos = 0;
	while (s[pos] != '\0')
	{
		while (isdigit(s[pos]) && isdigit(s[pos + 1]))
		{
			pos++;
		}
		str = s.substr(OldPos, (pos + 1 - OldPos)); 
		temp.pLexem[i] = str;
		temp.pLexem[i].deftype(str, pos-OldPos + 1);
		OldPos = pos;
		pos++;
		i++;
		temp.nLexems = i;
		str.empty();
	}
	return temp;
	// ���� �� ������, ����� ������ ������ �� �������; ���� ������� ������ + 1 = �����, �� �������� �� ������ ������� + ���������
	/*pos = s.find_first_of(opers);
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
	}*/
};