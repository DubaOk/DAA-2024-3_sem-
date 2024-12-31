#include "IT.h";
#include "LA.h";
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Error.h"
using namespace std;
using namespace IT;
using namespace LA;
IdTable IT::Create() {
	IdTable IdTable = {};
	IdTable.maxsize = TI_MAXSIZE;
	IdTable.size = 0;
	IdTable.table = new Entry[IdTable.maxsize];
	if (IdTable.size > TI_MAXSIZE)
		throw ERROR_THROW(117);
	return IdTable;
}
void IT::Add(IdTable& idtable, Entry entry) {
	idtable.table[idtable.size] = entry;
	idtable.size++;
}
void IT::Delete(IdTable& idtable) {
	IdTable temp = {};
	idtable = temp;
}
Entry IT::GetEntry(IdTable& idtable, int n) {
	return idtable.table[n];
	if (n > idtable.size)
		throw ERROR_THROW(119);
}
int IT::IsId(IdTable& idtable, char* id) {
	for (int i = idtable.size - 1; i >= 0; i--) {
		if (strcmp(id, idtable.table[i].id) == 0) {
			return i;
		}
		if (strlen(idtable.table[i].id) > ID_MAXSIZE) {
			throw ERROR_THROW(109);
		}
	}
	return TI_NULLIDX;
}
void IT::PrintTable(IdTable& idtable) {
	ofstream fout("IT.txt");
	if (!fout.is_open()) {
		throw ERROR_THROW(114);
	}
	Entry e;
	fout << endl << "\t\t\t\t\t\t\t\t*** ÒÀÁËÈÖÀ ÈÄÅÍÒÈÔÈÊÀÒÎÐÎÂ ***" << endl;
	fout << endl;
	fout << "" << setw(98) << setfill('—') << "—" << endl;
	fout << "\tÒÈÏ:\t\t\t|" << "ÈÄÅÍÒÈÔÈÊÀÒÎÐ:" << "\t\t" << "|ÒÈÏ ÄÀÍÍÛÕ:" << "\t " << "|¹ Â ÒË" << "\t\t" << "|ÇÍÀ×ÅÍÈÅ:" << endl;
	fout << "" << setw(98) << setfill('—') << "—" << endl;
	for (int i = 0; i < idtable.size; i++) {
		e = idtable.table[i];
		switch (e.idtype) {
		case IT::L:
			switch (e.iddatatype) {
			case IT::INT:
				fout << "\tLITERAL\t\t\t|L" << e.idxfirstLE << "\t\t\t\t|" << "ARINTEGER" << "\t\t |" << e.idxfirstLE << "\t\t\t|" << e.value.vint << endl;
				break;
			case IT::STR:
				fout << "\tLITERAL\t\t\t|L" << e.idxfirstLE << "\t\t\t\t|" << "STRING" << "\t\t\t |" << e.idxfirstLE << "\t\t\t|" << e.value.vstr.str << endl;
				break;
			case IT::BOOL:
				fout << "\tLITERAL\t\t\t|L" << e.idxfirstLE << " \t\t\t\t|" << "BOOLEAN" << "\t\t |" << e.idxfirstLE << "\t\t\t|" << e.value.vbool << endl;
				break;
			}
			break;
		case IT::V:
			switch (e.iddatatype) {
			case IT::INT:
				fout << "\tVARIABLE\t\t|" << e.id << "\t\t\t|" << "INTEGER" << "\t\t |" << e.idxfirstLE << "\t\t\t|" << e.value.vint << endl;
				break;
			case IT::STR:
				fout << "\tVARIABLE\t\t|" << e.id << "\t\t|" << "STRING" << "\t\t\t |" << e.idxfirstLE << "\t\t\t|" << e.value.vstr.str << endl;
				break;
			case IT::BOOL:
				fout << "\tVARIABLE\t\t|" << e.id << "\t\t\t|" << "BOOLEAN" << "\t\t |" << e.idxfirstLE << "\t\t\t|" << e.value.vbool << endl;
				break;
			}
			break;
		case IT::F:
			switch (e.iddatatype) {
			case IT::INT:
				fout << "\tFUNCTION\t\t|" << e.id << "\t\t\t\t|" << "ARINTEGER" << "\t\t |" << e.idxfirstLE << endl;
				break;
			case IT::STR:
				fout << "\tFUNCTION\t\t|" << e.id << "\t\t\t\t|" << "STRING" << "\t\t\t |" << e.idxfirstLE << endl;
				break;
			case IT::BOOL:
				fout << "\tFUNCTION\t\t|" << e.id << "\t\t\t\t|" << "BOOLEAN" << "\t\t |" << e.idxfirstLE << endl;
				break;
			}
			break;
		case IT::P:
			switch (e.iddatatype) {
			case IT::INT:
				fout << "\tPARAMETER\t\t|" << e.id << "\t\t\t|" << "ARINTEGER" << "\t\t |" << e.idxfirstLE << "\t\t\t\t|" << e.value.vint << endl;
				break;
			case IT::STR:
				fout << "\tPARAMETER\t\t|" << e.id << "\t\t\t|" << "STRING" << "\t\t\t |" << e.idxfirstLE << "\t\t\t|" << e.value.vstr.str << endl;
				break;
			case IT::BOOL:
				fout << "\tPARAMETER\t\t|" << e.id << "\t\t\t|" << "BOOLEAN" << "\t\t |" << e.idxfirstLE << "\t\t\t|" << e.value.vbool << endl;
				break;
			}
			break;
		}
	}
	fout << "" << setw(98) << setfill('—') << "—";
	fout.close();
}