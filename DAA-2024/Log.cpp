#define _CRT_SECURE_NO_WARNINGS
#include "Log.h"
#include "Error.h"
#include <fstream>
#include <stdio.h>  
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
#include "Parm.h"
#include <iostream>
namespace Log {
	LOG getlog(wchar_t logfile[]) {
		LOG a;
		wcscpy_s(a.logfile, logfile);
		a.stream = new std::ofstream(logfile, std::ofstream::out);
		a.stream = new std::ofstream;
		a.stream->open(logfile);
		if (a.stream->fail()) {
			throw ERROR_THROW(112);
		}
		wcscpy_s(a.logfile, logfile);
		return a;
	}
	void WriteLine(LOG log, const char* c, ...) {
		const char** pc = &c;
		int len = 0;
		while (*pc != "") {
			len += strlen(*pc);
			pc++;
		}
		char* str = new char[len + 1];
		str[0] = 0;
		pc = &c;
		while (*pc != "") {
			strcat(str, *pc);
			pc++;
		}
		log.stream->write(str, len);
		delete[] str;
	}
	void WriteLine(LOG log, wchar_t* c, ...) {
		wchar_t** pc = &c;
		int len = 0;
		while (*pc != L"") {
			len += wcslen(*pc);
			pc++;
		}
		wchar_t* str = new wchar_t[len + 1];
		char* strl = new char[len + 1];
		str[0] = 0;
		pc = &c;
		while (*pc != L"") {
			wcscat(str, *pc);
			pc++;
		}
		wcstombs(strl, str, len + 2);
		log.stream->write(strl, len);
		delete[] str;
	}
	void WriteLog(LOG log) {
		time_t curTime;
		tm timeStruct;
		time(&curTime);
		char strTime[1024];
		localtime_s(&timeStruct, &curTime);
		strftime(strTime, 1024, "%d.%m.%Y %H:%M:%S", &timeStruct);
		*log.stream << "\n 覧覧覧覧 ﾏﾐﾎﾒﾎﾊﾎﾋ 覧覧覧覧\n" << " ﾄ瑣�: " << strTime << std::endl;
	}
	void WriteParm(LOG log, Parm::PARM parm) {
		*log.stream << "\n 覧覧覧覧 ﾏ瑩瑟褪�� 覧覧覧覧 " << std::endl;

		char temp[PARM_MAX_SIZE + 1];
		wcstombs(temp, PARM_LOG, wcslen(PARM_LOG) + 1);

		*log.stream << temp << " ";
		wcstombs(temp, parm.log, wcslen(parm.log) + 1);
		*log.stream << temp << std::endl;

		wcstombs(temp, PARM_OUT, wcslen(PARM_OUT) + 1);
		*log.stream << temp << " ";
		wcstombs(temp, parm.outASM, wcslen(parm.outASM) + 1);
		*log.stream << temp << ", ";
		*log.stream << temp << std::endl;

		wcstombs(temp, PARM_IN, wcslen(PARM_IN) + 1);
		*log.stream << temp << " ";
		wcstombs(temp, parm.in, wcslen(parm.in) + 1);
		*log.stream << temp << std::endl;
	}
	void WriteIn(LOG log, In::IN in) {
		*log.stream << "\n 覧覧覧覧 ﾈ���蓖�� 萵���� 覧覧� " << std::endl;
		*log.stream << "ﾊ��顆褥�粽 �韲粽���: " << in.size << std::endl;
		*log.stream << "ﾏ��鞳���頏�籵��    : " << in.ignor << std::endl;
		*log.stream << "ﾊ��顆褥�粽 �����   : " << in.lines + 1 << std::endl;
	}
	void WriteError(LOG log, Error::ERROR error) {
		*log.stream << "ﾎ�鞦�� " << error.id << ": " << error.message << ", ������ " << error.inext.line << ",��鉅��� " << error.inext.col << std::endl;
	}
	void Close(LOG log) {
		log.stream->close();
		delete log.stream;
		log.stream = NULL;
	}
}