#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "FST.h"
#include "LT.h"
#include "LA.h"
#include "In.h"
#include "Log.h"
#include <vector>
using namespace LT;
int enter = 0;
int conv(char* s) {
	int res = 0;
	int power = 0;
	int dec = 0;
	for (int i = strlen(s) - 1; i >= 0; --i) {
		res *= 8;
		res = s[i] - '0';
		dec += res * pow(8, power);
		power++;
	}
	return dec;
}
bool LA::CheckInVector(std::vector<const char*> vector, const char* word) {
	for (int i = 0; i < vector.size(); i++) {
		if (strcmp(word, vector[i]) == 0)
			return true;
	}
	return false;
}
void LA::InTables(LA::Tables& tables, int posword, int line, char* word, LA::Inf& inf) {
	LA::Machines machines[N_GRAPHS] = {
		{ LEX_ARINTEGER , FST::FST GRAPH_arinteger			}, // 1
		{ LEX_STRING    , FST::FST GRAPH_string				}, // 2
		{ LEX_BOOLEAN   , FST::FST GRAPH_boolean			}, // 3
		{ LEX_WRITE     , FST::FST GRAPH_write				}, // 4
		{ LEX_WRITE     , FST::FST GRAPH_writeline			}, // 5
		{ LEX_PROCESS   , FST::FST GRAPH_process			}, // 6
		{ LEX_SPAWN	    , FST::FST GRAPH_spawn				}, // 7
		{ LEX_PROGRAM   , FST::FST GRAPH_program			}, // 8
		{ LEX_OUT	    , FST::FST GRAPH_out				}, // 9
		{ LEX_IF        , FST::FST GRAPH_if					}, // 10
		{ LEX_COMMA     , FST::FST GRAPH_COMMA				}, // 11
		{ LEX_BEGIN	    , FST::FST GRAPH_BEGIN				}, // 12
		{ LEX_END	    , FST::FST GRAPH_END				}, // 13
		{ LEX_LEFTHESIS , FST::FST GRAPH_LEFTHESIS			}, // 14
		{ LEX_RIGHTHESIS, FST::FST GRAPH_RIGHTHESIS			}, // 15
		{ LEX_LEFTBRACE , FST::FST GRAPH_LEFTBRCE			}, // 16
		{ LEX_RIGHTBRACE, FST::FST GRAPH_BRACELET			}, // 17
		{ LEX_BOR       , FST::FST GRAPH_BOR                }, // 18
		{ LEX_MINUS     , FST::FST GRAPH_MINUS				}, // 19
		{ LEX_PLUS      , FST::FST GRAPH_PLUS				}, // 20
		{ LEX_BAND      , FST::FST GRAPH_BAND               }, // 21
		{ LEX_SEMICOLON , FST::FST GRAPH_SEMICOLON			}, // 22
		{ LEX_BNOT      , FST::FST GRAPH_BNOT               }, // 23
		{ LEX_EQUALITY  , FST::FST GRAPH_equality			}, // 24
		{ LEX_EQUAL     , FST::FST GRAPH_EQUAL				}, // 25
		{ LEX_LITERAL   , FST::FST GRAPH_true				}, // 26
		{ LEX_LITERAL   , FST::FST GRAPH_false				}, // 27
		{ LEX_LITERAL   , FST::FST GRAPH_integerx8_literal	}, // 28
		{ LEX_LITERAL   , FST::FST GRAPH_integer_literal	}, // 29
		{ LEX_LITERAL   , FST::FST GRAPH_string_literal		}, // 30
		{ LEX_ID		, FST::FST GRAPH_id					}, // 31
		{ LEX_STAR	    , FST::FST GRAPH_MUL				}, // 32
		{ LEX_DIRSLASH  , FST::FST GRAPH_DIV				}, // 33

	};
	const char* LiteralPrefix = "L";
	char lexema = (char)"";
	int indexIT = -1;
	bool executeFlag = 0;
	bool IdFlag = 0;
	union Value {
		unsigned int vint;					// значение integer
		struct {
			int len;						// количество символов в string
			char* str;						// cимволы string
		} vstr;								// значение string
		bool vbool;							// значение bool
	} value{};
	value.vint = 0;
	value.vstr.str = (char*)" ";
	value.vbool = false;
	for (int i = 0; i < N_GRAPHS; i++) {
		if (FST::execute(machines[i].machine, word)) {
			if (machines[i].lexema == 'i' || machines[i].lexema == 'l') { // обработка литералов
				if (i == 25) {
					inf.iddatatype = IT::IDDATATYPE::BOOL;
					inf.idtype = IT::IDTYPE::L;
					value.vbool = true;
				}
				else if (i == 26) {
					inf.iddatatype = IT::IDDATATYPE::BOOL;
					inf.idtype = IT::IDTYPE::L;
					value.vbool = false;
				}
				else if (i == 27) {
					inf.iddatatype = IT::IDDATATYPE::INT;
					inf.idtype = IT::IDTYPE::L;
					int length = strlen(word);
					char* newStart;
					if (length <= 2) {
						word[0] = '\0';
					}
					else {
						newStart = word + 2;
						strcpy(word, newStart);
					}
					value.vint = conv(word);
				}
				else if (i == 28) {
					inf.iddatatype = IT::IDDATATYPE::INT;
					inf.idtype = IT::IDTYPE::L;
					value.vint = atoi(word);
				}
				else if (i == 29) {
					inf.iddatatype = IT::IDDATATYPE::STR;
					inf.idtype = IT::IDTYPE::L;
					value.vstr = { (int)strlen(word), word };
					tables.idTable.table[i].id = (char*)8;
					if (value.vstr.len > 255)
						throw Error::geterrorin(126, line, posword);
				}
				IdFlag = true;
			}
			executeFlag = true;
			lexema = machines[i].lexema;
			break;
		}
	}
	if (executeFlag) {
		if (IdFlag) {
			if (CheckInVector(inf.functions, (const char*)word) || lexema == 'l');
			else if (inf.flagInFunc) {
				strcat(word, "_");
				strcat(word, inf.prefix);
			}
			indexIT = IT::IsId(tables.idTable, word);
			if (indexIT != TI_NULLIDX && inf.iddatatype != IT::IDDATATYPE::NODEF && inf.idtype != IT::IDTYPE::L && inf.idtype != IT::IDTYPE::P)
				throw Error::geterrorin(123, line, posword); // повторна€ инициализаци€
			else if (indexIT == TI_NULLIDX) { // добавл€ем в таблицу индентификаторов
				if (inf.iddatatype == IT::IDDATATYPE::NODEF)
					throw Error::geterrorin(122, line, posword); // использование без объ€влени€
				indexIT = tables.idTable.size;
				IT::Entry IdTableEntry = { tables.LexTable.size, word, inf.iddatatype, inf.idtype , 0 };
				memcpy(&IdTableEntry.value, &value, sizeof(Value));
				IT::Add(tables.idTable, IdTableEntry);
				inf.iddatatype = IT::IDDATATYPE::NODEF;
				inf.idtype = IT::IDTYPE::V;
			}
			else {
				inf.iddatatype = IT::IDDATATYPE::NODEF;
				inf.idtype = IT::IDTYPE::V;
			}
		}
		LT::Add(tables.LexTable, { lexema, line, tables.LexTable.size, indexIT, word[0], posword });
	}
	else
		throw Error::geterrorin(113, line, posword);
}
void LA::GetInf(LA::Inf& inf, char* word) {
	if (strcmp(word, "arinteger") == 0)
		inf.iddatatype = IT::IDDATATYPE::INT;
	else if (strcmp(word, "string") == 0)
		inf.iddatatype = IT::IDDATATYPE::STR;
	else if (strcmp(word, "boolean") == 0)
		inf.iddatatype = IT::IDDATATYPE::BOOL;
	else if (strcmp(word, "process") == 0) {
		inf.idtype = IT::IDTYPE::F;
		inf.flagFunc = true;
	}
	else if (strcmp(word, "(") == 0 && inf.flagFunc) {
		inf.flagParam = true;
		inf.flagInFunc = true;
	}
	else if (strcmp(word, ")") == 0 && inf.flagFunc) {
		inf.flagParam = false;
		inf.flagFunc = false;
	}
	else if (inf.idtype == IT::IDTYPE::F || strcmp(word, "Program") == 0) {
		for (int i = 0; i <= strlen(word); i++)
			inf.prefix[i] = word[i];
		if (strcmp(word, "Program") != 0)
			inf.functions.push_back((const char*)word);
		if (strcmp(word, "Program") == 0) {
			enter++;
			if (enter > 1)
				throw Error::geterrorin(129, 0, 0);
		}
	}
	else if (inf.flagParam)
		inf.idtype = IT::IDTYPE::P;
	else if (strcmp(word, "{") == 0)
		inf.flagInFunc = true;
	else if (strcmp(word, "}") == 0) {
		inf.prefix = NULL;
		inf.prefix = new char(256);
		inf.flagInFunc = false;
	}
}
LA::Tables LA::Lex_analyz(In::IN in) {
	LA::Tables tables;
	tables.LexTable = LT::Create();
	tables.idTable = IT::Create();
	LA::Inf inf;
	inf.functions.push_back("comp");
	inf.functions.push_back("copy");
	inf.functions.push_back("concat");
	IT::Entry IdTableEntry;
	IdTableEntry = { tables.LexTable.size, (char*)"comp", IT::IDDATATYPE::BOOL, IT::IDTYPE::F , true, 0, 0 };
	IT::Add(tables.idTable, IdTableEntry);
	IdTableEntry = { tables.LexTable.size, (char*)"copy", IT::IDDATATYPE::STR, IT::IDTYPE::F , true, 0, 1 };
	IT::Add(tables.idTable, IdTableEntry);
	IdTableEntry = { tables.LexTable.size, (char*)"concat", IT::IDDATATYPE::STR, IT::IDTYPE::F , true, 0, 2 };
	IT::Add(tables.idTable, IdTableEntry);
	int i = 0; // индекс по in.text
	int wordIndex = 0;
	int posWord = 0; // позици€ слова в строке
	int line = 1; // текуща€ строка
	char* word = new char[256];
	if (in.text == (unsigned char*)' ')
		i++;
	while (i < in.size) {
		if (in.text[i] == '#') {
			while (in.text[i] != '\n')
				i++;
		}
		else if (in.text[i] == '\'') {
			while (true) {
				word[wordIndex++] = in.text[i++];
				posWord++;
				if (in.text[i] == '\n') {
					line++;
					posWord = 0;
				}
				if (in.text[i] == '\'' || in.text[i] == '\0')
					break;
			}
			word[wordIndex++] = in.text[i++];
			word[wordIndex] = '\0';
			GetInf(inf, word);
			InTables(tables, posWord, line, word, inf);
			word = NULL;
			word = new char[256];
			wordIndex = 0;
		}
		else if (in.code[in.text[i]] == in.T) {
			while (in.code[in.text[i]] == in.T) {
				word[wordIndex++] = in.text[i++];
				posWord++;
			}
			if (in.code[in.text[i]] == in.S || in.code[in.text[i]] == in.P || in.code[in.text[i]] == in.Q) {
				word[wordIndex] = '\0';
				wordIndex = 0;
				GetInf(inf, word);
				InTables(tables, posWord, line, word, inf);
				word = NULL;
				word = new char[256];
			}
		}
		else if (in.code[in.text[i]] == in.S) {
			word[wordIndex++] = in.text[i++];
			word[wordIndex] = '\0';
			GetInf(inf, word);
			InTables(tables, posWord, line, word, inf);
			posWord++;
			wordIndex = 0;
			word = NULL;
			word = new char[256];
		}
		else if (in.code[in.text[i]] == in.P) {
			if (in.text[i] == IN_CODE_ENDL) {
				line++;
				posWord = 0;
			}
			wordIndex = 0;
			i++;
		}
	}
	return tables;
}