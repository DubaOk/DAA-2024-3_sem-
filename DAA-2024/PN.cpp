#include "PN.h"
#include "IT.h";
#include "LT.h";
#include <stack>;
#include <queue>;
#include <iostream>;
bool PN::PolishNotation(int n, LT::LexTable& lextable, IT::IdTable& idtable) {
	std::queue<LT::Entry> current;
	std::stack<LT::Entry> stack;
	int i = n;
	int priority;
	int parCount = 0;
	int indID = -1;
	while (lextable.table[i].lexema != ';') {
		priority = getP(lextable.table[i]);
		if (lextable.table[i].lexema == 'i' && lextable.table[i + 1].lexema == '(') { // попали на вызов функции
			indID = lextable.table[i].indID;
			i++;
			priority = getP(lextable.table[i]);
			while (priority < 2) {
				if (priority == 0) {
					current.push(lextable.table[i]);
					parCount++;
				}
				else if (priority == 1)
					stack.push(lextable.table[i]);
				else if (priority == -2);
				else if (priority == -1) {
					while (getP(stack.top()) != 1) {		// выталкиваем стек пока не встретим открывашку
						current.push(stack.top());
						stack.pop();
					}
					stack.pop();
					current.push({ '@', lextable.table[i].sn, lextable.table[i].idxLT, indID });
					if (parCount >= 0 && parCount <= 9) {
						current.push({ (char)(parCount + 48), lextable.table[i].sn, (int)LT_TI_NULLIDX });
					}
					if (parCount > 9) {
						current.push({ (char)((int)(parCount / 10) + 48), lextable.table[i].sn, (int)LT_TI_NULLIDX });
						current.push({ (char)(parCount % 10 + 48), lextable.table[i].sn, (int)LT_TI_NULLIDX });
					}
					i++;
					priority = getP(lextable.table[i]);
					break;
				}
				i++;
				priority = getP(lextable.table[i]);
			}
		}
		if (priority == 0)
			current.push(lextable.table[i]);
		else if (priority == 1)
			stack.push(lextable.table[i]);
		else if (priority == 2 || priority == 3 || priority == 4 || priority == 5 || priority == 6) {
			while (!stack.empty()) {
				if (getP(stack.top()) >= priority) {
					current.push(stack.top());
					stack.pop();
				}
				else
					break;
			}
			stack.push(lextable.table[i]);
		}
		else if (priority == -1) {
			while (getP(stack.top()) != 1) {			// выталкиваем стек пока не встретим открывашку		
				current.push(stack.top());
				stack.pop();
			}
			stack.pop();
		}
		else if (priority == -3)
			break;
		i++;
	}
	while (!stack.empty()) {
		current.push(stack.top());
		stack.pop();
	}
	current.push(lextable.table[i]);
	//обратная польская запись построена
	int posLast = i;	// позиция последнего символа выражения до польской записи
	i = n;
	for (i; i <= posLast; i++) {
		lextable.table[i] = { '#' , -1 , i , -1 };
		while (!current.empty()) {
			lextable.table[i] = current.front();
			lextable.table[i].idxLT = i;
			current.pop();
			i++;
		}
	}
	return true;
}
int PN::getP(LT::Entry table) {
	char token = table.lexema;
	if (token == 'x')
		token = table.operatorValue;
	if (token == '~')
		return 6;
	if (token == '*' || token == '/')
		return 5;
	else if (token == '+' || token == '-' || token == '%')
		return 4;
	else if (token == '&')
		return 3;
	else if (token == '|')
		return 2;
	else if (token == '(')
		return 1;
	else if (token == ')')
		return -1;
	else if (token == ',')
		return -2;
	else if (token == ';')
		return -3;
	else return 0;
}