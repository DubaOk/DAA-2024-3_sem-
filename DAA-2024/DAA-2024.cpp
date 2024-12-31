#include "stdafx.h"
#include <iostream>
#include <cstdlib>  // ��� system()

using namespace std;

int wmain(int argc, wchar_t* argv[]) {
    setlocale(LC_ALL, "rus");

    while (true) {
        // ������� ���� ��� ������������
        wcout << L"�������� �����:" << endl;
        wcout << L"1. ������ ���������" << endl;
        wcout << L"2. �����" << endl;
        wcout << L"������� ����� �����: ";

        int choice;
        wcin >> choice;
        bool askForAsm = true;

        if (choice == 1) {
            // ��� ������� ��� ���������
            Log::LOG log = Log::INTLOG;
            try {
                Parm::PARM parm = Parm::getparm(argc, argv);
                log = Log::getlog((parm.log));
                wcout << "-in:" << parm.in << ", -out:" << parm.outASM << ", -log: " << parm.log << endl;
                In::IN in = In::getin(parm.in);
                LA::Tables Tables = LA::Lex_analyz(in);
                std::cout << "����������� ������ �������� �������\n";
                LA::Inf inf;
                Log::WriteLine(log, " ����:", " ��� ������\n", "");
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
                std::cout << "�������������� ������ �������� �������\n";
                std::vector<SA::Function> functions = SA::SemAnalysis(Tables);
                std::cout << "������������� ������ �������� �������\n";
                GenASM::Generation(parm.outASM, Tables, functions);
                std::cout << "�������������� � �������� ������ ��������� �������\n";
                std::cout << "��������� ���� ��������� �������\n";
                LT::PrintTablePolish(Tables.LexTable);
                Log::WriteLine(log, "\n\n", "");
                Log::Close(log);
            }
            catch (Error::ERROR error) {
                cout << "������ " << error.id << ": " << error.message << " (������ " << error.inext.line << ", ������� " << error.inext.col << ")" << std::endl;
                Log::WriteError(log, error);
                askForAsm = false;
            }

            if (askForAsm) {
                // ������ �� �������� ���������������� �����
                wcout << L"������ ������� ��������������� ���� ASM? (y/n): ";
                char openChoice;
                cin >> openChoice;

                if (openChoice == 'y' || openChoice == 'Y') {
                    // ��������� ������ ���� � �����
                    string command = "start D:\\Labs_BSTU_sem3\\DAA-2024\\ASM\\in.txt.asm"; // ���� � ������ �����
                    system(command.c_str());  // ��������� ����

                }
            }

        }
        else if (choice == 2) {
            // ���� ������� "�����", ������� �� ���������
            wcout << L"����� �� ���������..." << endl;
            break;
        }
        else {
            // ��������� ������������� �����
            wcout << L"�������� �����. ����������, �������� 1 ��� 2." << endl;
        }
    }

    return 0;
}
