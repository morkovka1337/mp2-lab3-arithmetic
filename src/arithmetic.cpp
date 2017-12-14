// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"
Lexem::Lexem(const string& s)
{
	lexemstr = s;
	int k = s.length();
	if (k == 1)
	{
		if (isdigit(lexemstr[0]))
		{
			type = VAL;
			var = stod(lexemstr);
		}
		else if (isalpha(lexemstr[0]))
		{
			type = VAR;
		}
		else if (lexemstr == "(")
		{
			type = LBr;
			priority = 0;
		}
		else if (lexemstr == ")")
		{
			type = RBr;
			priority = 0;
		}
		else if (lexemstr == "+")
		{
			type = OPER;
			priority = 1;
		}
		else if (lexemstr == "-")
		{
			type = OPER;
			priority = 1;
		}
		else  if (lexemstr == "*")
		{
			type = OPER;
			priority = 2;
		}
		else if (lexemstr == "/")
		{
			type = OPER;
			priority = 2;
		}
		else
		{
			throw "incorrect symbol";
		}
	}
	else if (k > 1)
	{
		type = VAL;
		var = stod(lexemstr);
	}
}


Lexem::Lexem(const char c)
{
	string opers = "(+-*/)";
	char value = opers.find(c);
	switch (c)
	{
	case '(':
	{
		type = LBr;
		value = 0;
		break;
	}
	case ')':
	{
		type = RBr;
		value = 0;
		break;
	}
	}
	if (value > 0)
		type = OPER;
	lexemstr = c;

	if (lexemstr == "(")
	{
		priority = 0;
	}
	else if (lexemstr == "+")
	{
		priority = 1;
	}
	else if (lexemstr == "-")
	{
		priority = 1;
	}
	else  if (lexemstr == "*")
	{
		priority = 2;
	}
	else if (lexemstr == "/")
	{
		priority = 2;
	}

};

Arithmetic& Arithmetic::operator +=(const Lexem& a)
{
	int size = nLexems;
	pLexem[size] = a;
	nLexems += 1;
	return *this;
}

Arithmetic& Arithmetic::operator =(const Arithmetic & a)
{
	str = a.str;
	nLexems = a.nLexems;

	pLexem = new Lexem[nLexems];
	for (int i = 0; i < nLexems; i++)
		pLexem[i] = a.pLexem[i];

	return (*this);
}

void Arithmetic::check(const string s)
{
	Arithmetic lex(s);
	int k, p;
	for (int i = 0; i < lex.nLexems; i++)
	{
		if (lex.pLexem[i].type == LBr) k++;
		if (lex.pLexem[i].type == RBr) p++;
	}
	if (((lex.pLexem[0].type == VAL) || (lex.pLexem[0].type == LBr)) && ((lex.pLexem[nLexems - 1].type == VAL) || (lex.pLexem[nLexems - 1].type == RBr)) && (p = k))
	{
		for (int i = 0; i < (nLexems - 1); i++)
			switch (lex.pLexem[i].type)
			{
			case VAL:
				if ((lex.pLexem[i + 1].type != RBr) || (lex.pLexem[i + 1].type != OPER))
					throw "StringError";
			case OPER:
				if ((lex.pLexem[i + 1].type != VAL) || (lex.pLexem[i + 1].type != RBr))
					throw "StringError";
			case LBr:
				if ((lex.pLexem[i + 1].type != VAL) || (lex.pLexem[i + 1].type != RBr))
					throw "StringError";
			case RBr:
				if ((lex.pLexem[i + 1].type != RBr) || (lex.pLexem[i + 1].type != OPER))
					throw "StringError";
			}
	}
	else
		throw "StringError";
}

Lexem Arithmetic::operator[] (int i)
{
	return pLexem[i];
}
Arithmetic::Arithmetic(const string& s)
{
	str = s;
	pLexem = new Lexem[s.size()];
	pLexemPolish = new Lexem[s.size()];
	nLexemsPolish = 0;

	nLexems = 0;
	int k = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (isdigit(s[i]))
		{
			int j = i; // конец числа
			string v;
			while (isdigit(s[j]) || (s[j] == '.'))
			{
				if (s[j] != '/0')
					j++;
			}
			v = s.substr(i, j - i);
			pLexem[k] = Lexem(v);
			k++;
			i = j - 1;
		}
		else
		{
			pLexem[k] = Lexem(s[i]);
			k++;
		}
	}
	nLexems = k;
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
		if ((pLexem[i].type == LBr) && (pLexem[i + 1].lexemstr == "-") && ((pLexem[i + 2].type == VAL) || pLexem[i + 2].type == VAR))
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


Arithmetic::Arithmetic(const Arithmetic& a)
{
	str = a.str;
	nLexems = a.nLexems;
	nLexemsPolish = a.nLexemsPolish;
	pLexem = new Lexem[nLexems];
	for (int i = 0; i < nLexems; i++)
		pLexem[i] = a.pLexem[i];
	pLexemPolish = new Lexem[nLexemsPolish];
	for (int i = 0; i < nLexemsPolish; i++)
		pLexemPolish[i] = a.pLexemPolish[i];
}

void  Arithmetic::PolishEntry()
{
	for (int i = 0; i < nLexems; i++)
		cout << "[pLexem[" << i + 1 << "]" << pLexem[i].lexemstr << "] " << "[type[" << i + 1 << "]" << pLexem[i].type << "] " << "[var[" << i + 1 << "]" << pLexem[i].var << "] " << "[priority[" << i + 1 << "]" << pLexem[i].priority << "] " << endl;
	// сделать void?
	Stack<Lexem> s1;
	for (int i = 0; i < nLexems; i++)
	{
		if ((pLexem[i].type == VAL) || (pLexem[i].type == VAR))
			pLexemPolish[nLexemsPolish++] = pLexem[i];
		if (pLexem[i].type == LBr)
		{
			s1.Push(pLexemPolish[i]);
		}
		if (pLexem[i].type == OPER)
		{
			if (s1.IsEmpty())
				s1.Push(pLexem[i]);
			else
			{
				Lexem x;
				while (!s1.IsEmpty() && (s1.Top().priority > pLexem[i].priority))
				{
					x = s1.Eject();
					pLexemPolish[nLexemsPolish++] = x; 
				}
				s1.Push(pLexem[i]);
			}
		}

		if (pLexem[i].type == RBr)
		{
			Lexem x = s1.Eject();
			while (x.type != LBr)
			{
				pLexemPolish[nLexemsPolish++] = x;
				x = s1.Eject();
			}
		}
	}

	while (!s1.IsEmpty())
	{
		Lexem x = s1.Eject();
		pLexemPolish[nLexemsPolish++] = x;
	} 
	for (int i = 0; i < nLexemsPolish; i++)
		cout << "[pLexem[" << i + 1 << "]" << pLexemPolish[i].lexemstr << "] " << "[type[" << i + 1 << "]" << pLexemPolish[i].type << "] " << "[var[" << i + 1 << "]" << pLexemPolish[i].var << "] " << "[priority[" << i + 1 << "]" << pLexemPolish[i].priority << "] " << endl;
}



double Arithmetic::Calc()
{
	for (int i = 0; i < nLexemsPolish; i++)
	{
		if (pLexemPolish[i].type == VAR)
		{
			pLexemPolish[i].SetVar();
			pLexemPolish[i].type = VAL;
		}
	}

	Stack<double> s1;
	double res = 0.0;

	for (int i = 0; i < nLexemsPolish; i++)
	{
		if (pLexemPolish[i].type == VAL)
		{
			s1.Push(pLexemPolish[i].var);
		}
		if (pLexemPolish[i].type == OPER)
		{
			double A = s1.Eject();
			double B = s1.Eject();
			string ls = pLexemPolish[i].lexemstr;
			if (ls == "+")
			{
				res = A + B;
			}
			else if (ls == "-")
			{
				res = B - A;
			}
			else if (ls == "*")
			{
				res = A * B;
			}
			else if (ls == "/")
			{
				res = B / A;
			}
			cout << res << endl;
			s1.Push(res);
		}
	}
	return s1.Eject();
}
