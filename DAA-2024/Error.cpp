#include "Error.h"
#include<iostream>
namespace Error {
	//    0 - 99 - системные ошибки 
	// 100 - 106 - ошибки параметров
	// 107 - 109 - доп. ошибки
	// 110 - 119 - ошибки файлов
	ERROR errors[ERROR_MAX_ENTRY] = { // таблица ошибок
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106),
		ERROR_ENTRY(107, "Семантическая ошибка. Деление на ноль"),
		ERROR_ENTRY(108, "Семантическая ошибка. Получено отрицательное значение переменной"),
		ERROR_ENTRY(109, "Лексическая ошибка. Превышена длина идентификатора"),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),

		ERROR_ENTRY(113, "Лексическая ошибка. Элемент не распознан"),
		ERROR_ENTRY(114, "Лексическая ошибка. Ошибка при создании файла IT"),
		ERROR_ENTRY(115, "Лексическая ошибка. Ошибка при создании файла LT"),
		ERROR_ENTRY(116, "Лексическая ошибка. Ошибка при создании лексической таблицы (превышен максимальный размер)"),
		ERROR_ENTRY(117, "Лексическая ошибка. Ошибка при создании таблицы идентификаторов (превышен максимальный размер)"),
		ERROR_ENTRY(118, "Лексическая ошибка. Ошибка при получении строки лексической таблицы (нет элемента)"),
		ERROR_ENTRY(119, "Лексическая ошибка. Ошибка при получении строки таблицы идентификаторов (нет элемента)"),

		ERROR_ENTRY(120, "Семантическая ошибка. Невозможно применить оператор к данному типу операнда"),
		ERROR_ENTRY(121, "Семантическая ошибка. Тип возвращаемого значения не соответствует типу функции"),
		ERROR_ENTRY(122, "Семантическая ошибка. Использована необъявленная переменная"),
		ERROR_ENTRY(123, "Семантическая ошибка. Повторное объявление имени"),
		ERROR_ENTRY(124, "Cемантическая ошибка. Функция должна возвращать значение"),
		ERROR_ENTRY(125, "Cемантическая ошибка. Ошибка в условии условного оператора"),
		ERROR_ENTRY(126, "Семантическая ошибка. Длина строкового литерала превышает допустимое значение"),
		ERROR_ENTRY(127, "Cемантическая ошибка. Несоответствие типов в выражении"),
		ERROR_ENTRY(128, "Семантическая ошибка. Несовпадение фактических и формальных параметров функции"),
		ERROR_ENTRY(129, "Семантическая ошибка. Обнаружено больше 1 точки входа в программу"),

		ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),

		ERROR_ENTRY(600, "Синтаксическая ошибка. Неверная структура программы"),
		ERROR_ENTRY(601, "Синтаксическая ошибка. Ошибочный оператор или функция не возвращает значения"),
		ERROR_ENTRY(602, "Синтаксическая ошибка. Ошибка в выражении"),
		ERROR_ENTRY(603, "Синтаксическая ошибка. Ошибка в операторах выражений"),
		ERROR_ENTRY(604, "Синтаксическая ошибка. Ошибка в параметрах функции"),
		ERROR_ENTRY(605, "Синтаксическая ошибка. Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(606, "Синтаксическая ошибка. Значением данного оператора может быть только переменная или литерал"),
		ERROR_ENTRY(607, "Синтаксическая ошибка. Ошибка в условии условного оператора"),
		ERROR_ENTRY(608, "Синтаксическая ошибка"),

		ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id) {
		ERROR e;
		if (0 < id && id < ERROR_MAX_ENTRY) {
			e = errors[id];
		}
		else {
			e = errors[0];
		}
		return e;
	}
	ERROR geterrorin(int id, int line, int col) {
		ERROR e;
		if (0 < id && id < ERROR_MAX_ENTRY) {
			e = errors[id];
			e.inext.line = line;
			e.inext.col = col;
		}
		else {
			e = errors[0];
			e.inext.line = line;
			e.inext.col = col;
		}
		return e;
	}
}