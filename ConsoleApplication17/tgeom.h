#ifndef TGEOM_H
#define TGEOM_H

#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include "consoleroutine.h"

class TGeom {
private:
public:
	int    id;
	short  x;
	short  y;
	char   symb;
	char   *name;
	ConsoleColors color;
	ConsoleColors bgcolor;
	TGeom();
	virtual ~TGeom();
	virtual int Contains(const short X, const short Y);
	virtual void InitTest();
	virtual void Print();
	virtual void Erase();
	virtual void SaveToFile(FILE *fileHandle);
	virtual int LoadFromStr(char *buffer);
protected:
};

#endif
