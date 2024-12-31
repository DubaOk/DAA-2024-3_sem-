#include "stdafx.h"
#include <iostream>
#include <cstdlib>  // Для system()

using namespace std;

int wmain(int argc, wchar_t* argv[]) {
    setlocale(LC_ALL, "rus");

    while (true) {
        // Выводим меню для пользователя
        wcout << L"Выберите опцию:" << endl;
        wcout << L"1. Начать программу" << endl;
        wcout << L"2. Выйти" << endl;
        wcout << L"Введите номер опции: ";

        int choice;
        wcin >> choice;
        bool askForAsm = true;

        if (choice == 1) {
            // Ваш текущий код программы
            Log::LOG log = Log::INTLOG;
            try {
                Parm::PARM parm = Parm::getparm(argc, argv);
                log = Log::getlog((parm.log));
                wcout << "-in:" << parm.in << ", -out:" << parm.outASM << ", -log: " << parm.log << endl;
                In::IN in = In::getin(parm.in);
                LA::Tables Tables = LA::Lex_analyz(in);
                std::cout << "Лексический анализ завершён успешно\n";
                LA::Inf inf;
                Log::WriteLine(log, " ТЕСТ:", " без ошибок\n", "");
                Log::WriteLog(log);
                Log::WriteParm(log, parm);
                Log::WriteIn(log, in);
                Log::WriteLine(log, "\n\n", "");
                IT::PrintTable(Tables.idTable);
                LT::PrintTable(Tables.LexTable);
                std::ofstream fout("MFST.txt");
                MFST_TRACE_START
                    MFST::Mfst mfst(Tables, GRB::getGreibach());
                mfst.start();
                mfst.printrules();
                std::cout << "Синтаксический анализ завершён успешно\n";
                std::vector<SA::Function> functions = SA::SemAnalysis(Tables);
                std::cout << "Семантический анализ завершён успешно\n";
                GenASM::Generation(parm.outASM, Tables, functions);
                std::cout << "Преобразование к польской записи завершено успешно\n";
                std::cout << "Генерация кода завершена успешно\n";
                LT::PrintTablePolish(Tables.LexTable);
                Log::WriteLine(log, "\n\n", "");
                Log::Close(log);
            }
            catch (Error::ERROR error) {
                cout << "Ошибка " << error.id << ": " << error.message << " (строка " << error.inext.line << ", позиция " << error.inext.col << ")" << std::endl;
                Log::WriteError(log, error);
                askForAsm = false;
            }

            if (askForAsm) {
                // Запрос на открытие сгенерированного файла
                wcout << L"Хотите открыть сгенерированный файл ASM? (y/n): ";
                char openChoice;
                cin >> openChoice;

                if (openChoice == 'y' || openChoice == 'Y') {
                    // Указываем полный путь к файлу
                    string command = "start D:\\Labs_BSTU_sem3\\DAA-2024\\ASM\\in.txt.asm"; // Путь к вашему файлу
                    system(command.c_str());  // Открываем файл

                }
            }

        }
        else if (choice == 2) {
            // Если выбрано "Выйти", выходим из программы
            wcout << L"Выход из программы..." << endl;
            break;
        }
        else {
            // Обработка неправильного ввода
            wcout << L"Неверный выбор. Пожалуйста, выберите 1 или 2." << endl;
        }
    }

    return 0;
}
