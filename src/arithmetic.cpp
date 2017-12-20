// реализаци€ функций и классов дл€ вычислени€ арифметических выражений
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
			priority = 1;
		}
		else if (lexemstr == "+")
		{
			type = OPER;
			priority = 2;
		}
		else if (lexemstr == "-")
		{
			type = OPER;
			priority = 2;
		}
		else  if (lexemstr == "*")
		{
			type = OPER;
			priority = 3;
		}
		else if (lexemstr == "/")
		{
			type = OPER;
			priority = 3;
		}
		else
		{
			type = UNKOWN;
		}
	}
	else if (k > 1)
	{
		type = VAL;
		var = (double)stod(lexemstr);
	}
}


Lexem::Lexem(const char c)
{
	switch (c)
	{
	case '(':
	{
		type = LBr;
		priority = 0;
		break;
	}
	case ')':
	{
		type = RBr;
		priority = 1;
		break;
	}
	case '+':
	{
		type = OPER;
		priority = 2;
		break;
	}
	case '-':
	{
		type = OPER;
		priority = 2;
		break;
	}
	case '*':
	{
		type = OPER;
		priority = 3;
		break;
	}
	case '/':
	{
		type = OPER;
		priority = 3;
		break;
	}
	}
	lexemstr = c;
	if (isdigit(c))
	{
		type = VAL;
		var = stod(lexemstr);
	}
	else if (isalpha(c))
	{
		type = VAR;
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
	nLexemsPolish = a.nLexemsPolish;
	pLexem = new Lexem[nLexems];
	for (int i = 0; i < nLexems; i++)
		pLexem[i] = a.pLexem[i];
	pLexemPolish = new Lexem[nLexemsPolish];
	for (int i = 0; i < nLexemsPolish; i++)
		pLexemPolish[i] = a.pLexemPolish[i];

	return (*this);
}

bool Arithmetic::check()
{
	int k = 0, p = 0;
	for (int i = 0; i < nLexems; i++)
	{
		if (pLexem[i].type == LBr) k++;
		if (pLexem[i].type == RBr) p++;
	}
	if (k != p) return false;
	if ((!((pLexem[0].type == VAL)||(pLexem[0].type == VAR) || (pLexem[0].type == LBr))) || (!((pLexem[nLexems-1].type == VAL) || (pLexem[nLexems-1].type == VAR) || (pLexem[nLexems-1].type == RBr))))
		return false;
	for (int i = 0; i < (nLexems - 1); i++)
		switch (pLexem[i].type)
		{
		case VAL:
			if (!((pLexem[i + 1].type == RBr) || (pLexem[i + 1].type == OPER)))
				return false; // после числа только закрывающа€ скобка или оператор
			break;
		case VAR:
			if (!((pLexem[i + 1].type == RBr) || (pLexem[i + 1].type == OPER)))
				return false; // после переменной только закрывающа€ скобка или оператор
			break;
		case OPER:
			if (!((pLexem[i + 1].type == VAL) || (pLexem[i + 1].type == VAR) || (pLexem[i + 1].type == LBr)))
				return false; // после оператора только число, переменна€ или открывающа€ скобка
			break;
		case LBr:
			if (!((pLexem[i + 1].type == VAL) || (pLexem[i + 1].type == VAR) || (pLexem[i + 1].type == LBr)))
				return false; // после открывающей скобки только число, переменна€ или открывающа€ скобка
			break;
		case RBr:
			if (!((pLexem[i + 1].type == RBr) || (pLexem[i + 1].type == OPER)))
				return false; // после закрывающей скобки только закрывающа€ или оператор
			break;
		case UNKOWN:
			return false;
			break;
		}
	return true;
}

Lexem Arithmetic::operator[] (int i)
{
	return pLexem[i];
}
Arithmetic::Arithmetic(const string& s)
{
	str = s;
	pLexem = new Lexem[s.size()];
	//pLexemPolish = new Lexem[s.size()];
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
				if (s[j] != '\0')
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

	if ((pLexem[0].lexemstr == "-") && ((pLexem[1].type == VAL) || pLexem[1].type == VAR))//унарный минус в начале строки
	{
		nLexems++;
		Lexem* pLexemTemp;
		pLexemTemp = new Lexem[nLexems];
		pLexemTemp[0].type = VAL;
		pLexemTemp[0].var = 0.0;
		pLexemTemp[0].lexemstr = "0";
		for (int i = 1; i < nLexems; i++)
			pLexemTemp[i] = pLexem[i - 1];
		delete[] pLexem;
		pLexem = new Lexem[nLexems];
		for (int i = 0; i < nLexems; i++)
			pLexem[i] = pLexemTemp[i];
	}
	for (int i = 0; i < nLexems - 3; i++) // унарный минус в виде (-a
	{
		if ((pLexem[i].type == LBr) && (pLexem[i + 1].lexemstr == "-") && ((pLexem[i + 2].type == VAL) || pLexem[i + 2].type == VAR))
		{
			nLexems++;
			Lexem* pLexemTemp;
			pLexemTemp = new Lexem[nLexems];
			for (int j = 0; j < i+1; j++)
				pLexemTemp[j] = pLexem[j];

			pLexemTemp[i + 1].type = VAL;
			pLexemTemp[i + 1].var = 0.0;
			pLexemTemp[i + 1].lexemstr = "0";

			for (int j = i+1; j < nLexems - 1; j++)
				pLexemTemp[j+1] = pLexem[j];
			delete[] pLexem;
			pLexem = pLexemTemp;
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

void Arithmetic::PolishEntry()
{
	for (int i = 0; i < nLexems; i++)
		cout << "pLexem[" << i + 1 << "]" << pLexem[i].lexemstr << endl;
	pLexemPolish = new Lexem[nLexems];
	Stack<Lexem> s1;
	for (int i = 0; i < nLexems; i++)
	{
		if ((pLexem[i].type == VAL) || (pLexem[i].type == VAR))
		{
			pLexemPolish[nLexemsPolish] = pLexem[i];
			nLexemsPolish++;
		}
		if (pLexem[i].type == LBr)
		{
			s1.Push(pLexem[i]);
		}
		if (pLexem[i].type == RBr)
		{
			//Lexem x = s1.Eject();
			while ((s1.Top().type != LBr) && (!s1.IsEmpty())) // после первого оператора помещает пустую лексему, остальные смещаютс€ на 1;
			{
				pLexemPolish[nLexemsPolish] = s1.Eject();
				//cout << "nLexemsPolish " << nLexemsPolish << endl;
				nLexemsPolish++;
				//x = s1.Eject();
			}
			s1.Eject();
		}
		if (pLexem[i].type == OPER)
		{
			if ((s1.IsEmpty()) || (pLexem[i].priority > s1.Top().priority))
				s1.Push(pLexem[i]);
			else
			{
				while ((!s1.IsEmpty()) && (s1.Top().priority >= pLexem[i].priority))
				{
					pLexemPolish[nLexemsPolish] = s1.Eject(); 
					nLexemsPolish++;
				}
				s1.Push(pLexem[i]);
			}
		}

		
	}
	while (!s1.IsEmpty())
	{
		pLexemPolish[nLexemsPolish] = s1.Eject();
		nLexemsPolish++;
	} 
	for (int i = 0; i < nLexemsPolish; i++)
		cout << "[pLexemPolish[" << i + 1 << "]" << pLexemPolish[i].lexemstr << "] " << "[type[" << i + 1 << "]" << pLexemPolish[i].type << "] " << "[var[" << i + 1 << "]" << pLexemPolish[i].var << "] " << "[priority[" << i + 1 << "]" << pLexemPolish[i].priority << "] " << endl;
}

Lexem Arithmetic::GetPolishLex(int i)
{
	return pLexemPolish[i];
}



double Arithmetic::Calc()
{
	for (int i = 0; i < nLexemsPolish; i++)
	{
		if (pLexemPolish[i].type == VAR)
		{
			pLexemPolish[i].SetVar();
			pLexemPolish[i].type = VAL;
			pLexemPolish[i].value_is_entered = true;
			for (int j = i; j < nLexemsPolish; j++)
				if ((pLexemPolish[j].type == VAR) && (pLexemPolish[j].lexemstr == pLexemPolish[i].lexemstr))
				{
					pLexemPolish[j].var = pLexemPolish[i].var;
					pLexemPolish[j].value_is_entered = true;
					pLexemPolish[j].type = VAL;
				}
		}
	}

	Stack<double> s1;
	double res = 0.0;
	//cout << nLexemsPolish << endl;
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
			//cout << res << endl;
			s1.Push(res);
		}
	}
	return s1.Eject();
}
