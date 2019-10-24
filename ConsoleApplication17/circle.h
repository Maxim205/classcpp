#ifndef CIRCLE_H
#define CIRCLE_H

#include "tgeom.h"

class Circle :public TGeom {
public:
	short r;
	Circle();
	virtual ~Circle();
	virtual void InitTest();
	virtual int Contains(const short X, const short Y);
	virtual void Print();
	virtual void Erase();
	virtual void SaveToFile(FILE *fileHandle);
	virtual int LoadFromStr(char *buffer);
};

#endif