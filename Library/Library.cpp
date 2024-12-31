#include "pch.h" // Добавить эту строку
#include <iostream>
#include <Windows.h>
#include <string>
#include <cstring>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

extern "C" {

    void ConsNum(int a) {
        std::cout << a << std::endl;
    }

    void ConsStr(char* ptr) {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        if (ptr == nullptr) {
            std::cout << std::endl;
            return;
        }
        std::cout << ptr << std::endl;
    }

    void ConsBool(int a) {
        if (a == 1)
            std::cout << "true" << std::endl;
        else
            std::cout << "false" << std::endl;
    }

    bool comp(char* str1, char* str2) {
        int len1 = strlen(str1);
        int len2 = strlen(str2);

        // Сравниваем длины строк, если они разные, то строки разные
        if (len1 != len2)
            return false;

        // Сравниваем символы строк
        for (int i = 0; i < len1; i++) {
            if (str1[i] != str2[i])
                return false;
        }
        return true;
    }

    void consPause() {
        std::cout << "\n";
        system("pause");
    }

    char* copy(char* buffer, char* str1) {
        int i = 0;
        while (str1[i] != '\0' && i < 255) {
            buffer[i] = str1[i];
            i++;
        }
        buffer[i] = '\0'; // Завершаем строку
        return buffer;
    }

    char* concat(char* buffer, char* str1, char* str2) {
        int i = 0;

        // Копируем str1 в buffer
        while (str1[i] != '\0' && i < 255) {
            buffer[i] = str1[i];
            i++;
        }

        // Копируем str2 в buffer
        int j = 0;
        while (str2[j] != '\0' && i < 255) {
            buffer[i++] = str2[j++];
        }

        buffer[i] = '\0'; // Завершаем строку
        return buffer;
    }
}
