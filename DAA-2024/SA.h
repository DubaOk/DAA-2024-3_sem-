#pragma once
#include "IT.h"
#include "LT.h"
#include "In.h"
#include <vector>
#include "LA.h"
namespace SA {
	struct Flags {
		bool flagDecFunction = false;				// обнаруженно объ€вление функции
		bool flagDecProg = false;				// обнаруженно объ€вление функции
		bool flagCallFunction = false;				// обнаружен вызов функции
		int indF = -1;								// индекс функции в vector
		bool flagParametres = false;				// считывание параметров функции
		bool flagInFunction = false;				// вошли в блок функции
		bool flagInProg = false;				// вошли в блок функции
		bool flagReturn = false;					// встретили return
		bool flagExpression = false;				// наткнулись на выражение
		IT::IDDATATYPE ExpressionType = IT::NODEF;	// тип выражени€
		int ExpressionIndLT = -1;					// индекс выражени€ в таблице лексем
		bool flag—ondition = false;					// обнаружен условный оператор                           
	};
	struct Function {
		IT::Entry function;
		std::vector<IT::IDDATATYPE> parameters;
	};
	std::vector<SA::Function> SemAnalysis(LA::Tables tables);
	void GetFlags(char lexema, SA::Flags& flags);
	int CheckInFunctions(std::vector<SA::Function> functions, char* id);
}