#pragma once
#define LEXEMA_FIXSIZE	1
#define LT_MAXSIZE		4096
#define LT_TI_NULLIDX	0xffffffff
#define LEX_ARINTEGER	't'			// arinteger
#define LEX_STRING		't'			// string
#define LEX_BOOLEAN		't'			// boolean
#define LEX_ID			'i'			// идентификатор
#define LEX_LITERAL		'l'			// литерал
#define LEX_PROCESS		'f'			// process
#define LEX_SPAWN		'm'			// spawn
#define LEX_OUT	        'o'			// out
#define LEX_WRITE		'w'			// write
#define LEX_WRITELINE	'w'			// writeline
#define LEX_IF			'c'			// if
#define LEX_SEMICOLON	';'			// ;
#define LEX_COMMA		','			// ,
#define LEX_LEFTBRACE	'{'			// {
#define LEX_RIGHTBRACE	'}'			// }
#define LEX_BEGIN		'['			// begin  
#define LEX_END		    ']'			// end	
#define LEX_LEFTHESIS	'('			// (
#define LEX_RIGHTHESIS	')'			// )
#define LEX_PLUS		'x'			// +
#define LEX_MINUS		'x'			// -
#define LEX_STAR		'x'			// *
#define LEX_DIRSLASH	'x'			// /
#define LEX_EQUALITY    'x'			// =
#define LEX_EQUAL       '='			// :
#define LEX_PROGRAM		'p'			// Program
#define LEX_BOR 		'x'			// |
#define LEX_BAND     	'x'			// &
#define LEX_BNOT        'x'			// ~

namespace LT {
	struct Entry {
		char lexema;				// лексема
		int sn;						// номер строки
		int idxLT;					// индекс в таблице лексем
		int indID;					// индес в таблице индентификаторов
		char operatorValue;			// значение оператора для операторов.
		int posWord;				// позиция в строке
		char buf[LT_MAXSIZE * 2];	// буфер для связи с таблицей лексем
	};
	struct LexTable {
		int maxsize;				// макс размер таблицы лексем
		int size;					// текущий размер
		Entry* table; 				// массив строк таблицы лексем
	};
	LexTable Create();
	void Add(
		LexTable& lextable,			// экземпляр табл лексем
		Entry entry					// строка таблицы лексем
	);
	Entry GetEntry(					// получить строку в таблицу лексем
		LexTable& lextable,			// экземпляр табл лексем
		int n						// номер получаемой строки			
	);
	void Delete(LexTable& lextable);		// удалить таблицу лексем
	void PrintTable(LexTable& lextable);	// печать таблицы лексем
	void PrintTablePolish(LexTable& lextable);	// печать таблицы лексем
};