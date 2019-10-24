#ifndef TRECT_H
#define TRECT_H

#include "tgeom.h"

class TRect :public TGeom {
public:
	short height;
	short width;
	TRect();
	virtual ~TRect();
	virtual void InitTest();
	virtual int Contains(const short X, const short Y);
	virtual void Print();
	virtual void Erase();
	virtual void SaveToFile(FILE *fileHandle);
	virtual int LoadFromStr(char *buffer);
};

#endif