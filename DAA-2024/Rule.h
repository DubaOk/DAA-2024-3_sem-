#pragma once
#include "GRB.h"
#define GRB_ERROR_SERIES 600
namespace GRB {
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
	Greibach greibach(NS('S'), TS('$'),
		8,
		Rule(NS('S'), GRB_ERROR_SERIES + 0,						// �������� ��������� ���������	
			5,
			Rule::Chain(5, TS('p'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('o'), NS('R'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('o'), NS('R'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('o'), NS('R'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), TS('o'), NS('R'), TS(';'), TS('}'), TS(';'), NS('S'))
		),

		Rule(NS('N'), GRB_ERROR_SERIES + 1,						// ��������� ��������
			13,
			Rule::Chain(4, TS('m'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('m'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(9, TS('m'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS('w'), TS('('), NS('R'), TS(')'), TS(';')),
			Rule::Chain(6, TS('w'), TS('('), NS('R'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(9, TS('c'), TS('('), NS('I'), TS(')'), TS('['), NS('N'), TS(']'), TS(';'), NS('N')),
			Rule::Chain(8, TS('c'), TS('('), NS('I'), TS(')'), TS('['), NS('N'), TS(']'), TS(';')),
			Rule::Chain(9, TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(8, TS('f'), TS('i'), TS('('), TS(')'), TS(';'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(3, TS('o'), NS('R'), TS(';'))
		),

		Rule(NS('E'), GRB_ERROR_SERIES + 2,						// ������ � ��������� 
			10,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(4, TS('i'), TS('('), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
		),

		Rule(NS('M'), GRB_ERROR_SERIES + 3,
			2,
			Rule::Chain(2, TS('x'), NS('E')),
			Rule::Chain(3, TS('x'), NS('E'), NS('M'))
		),

		Rule(NS('F'), GRB_ERROR_SERIES + 4,						// ������ � ����������
			2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),

		Rule(NS('W'), GRB_ERROR_SERIES + 5,						// ������ � ���������� ���������� �-���
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),

		Rule(NS('R'), GRB_ERROR_SERIES + 6,						// ������ ���������� ��� �������
			2,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l'))
		),

		Rule(NS('I'), GRB_ERROR_SERIES + 7,						// ������ � �������� ���������
			6,
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(3, TS('i'), TS('x'), TS('i')),
			Rule::Chain(3, TS('i'), TS('x'), TS('l')),
			Rule::Chain(3, TS('l'), TS('x'), TS('i')),
			Rule::Chain(3, TS('l'), TS('x'), TS('l'))
		)
	);
}