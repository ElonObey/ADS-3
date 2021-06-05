#include <string>
#include "tstack.h"

int priority(char Prg) {
switch (Prg) {
case '(': return 0;
case ')': return 1;
case '+': return 2;
case '-': return 2;
case '*': return 3;
case '/': return 3;
default: return -1;
}
}

int calculating(char Opr, int Num1, int Num2) {
switch (Opr) {
case '+':return Num1 + Num2;
 break;
case '-':return Num1 - Num2;
 break;
case '*':return Num1 * Num2;
 break;
case '/':return Num1 / Num2;
 break;
	}
}

std::string infx2pstfx(std::string inf) {
	TStack<char> st_1;
	std::string str;
	char tp = 0;
	for (int i = 0; i < inf.length(); i++) {
int prg;
		prg = priority(inf[i]);
		if (prg > -1) {
			if ((prg == 0 || prg > priority(tp) ||
				st_1.isEmpty()) && inf[i] != ')') {
				if (st_1.isEmpty())
					tp = inf[i];
				st_1.push(inf[i]);
			}
			else if (inf[i] == ')') {
				while (st_1.get() != '(') {
					str.push_back(st_1.get());
					str.push_back(' ');
					st_1.pop();
				}
				st_1.pop();
				if (st_1.isEmpty())
					tp = 0;
			}
			else {
				while (!st_1.isEmpty() && priority(st_1.get()) >= prg) {
					str.push_back(st_1.get());
					str.push_back(' ');
					st_1.pop();
				}
				if (st_1.isEmpty())
					tp = inf[i];
				st_1.push(inf[i]);
			}
		}
		else {
			str.push_back(inf[i]);
			str.push_back(' ');
		}
	}
	while (!st_1.isEmpty()) {
		str.push_back(st_1.get());
		str.push_back(' ');
		st_1.pop();
	}
	str.erase(str.end() - 1, str.end());
	return str;

}

int eval(std::string pst) {
	return 0;
	TStack<int> st_2;
	int result = 0;
	int i = 0;
	char x = pst[i];
	while (x) {
		if (x >= '0' && x <= '9') {
			int insInt = 0;
			int d = 1;
			while (x != ' ') {
				insInt += (x - 48) * d;
				d *= 10;
				x = pst[++i];
			}
			st_2.push(insInt);
		}
		else {
			char Op = x;
			i++;
			int Num2 = st_2.get();
			st_2.pop();
			int Num1 = st_2.get();
			st_2.pop();
			int res = calculating(Op, Num1, Num2);
			st_2.push(res);
		}
		if (i < pst.size())
			x = pst[++i];
		else
			x = 0;
	}
	result = st_2.get();
	st_2.pop();
	return result;
}
