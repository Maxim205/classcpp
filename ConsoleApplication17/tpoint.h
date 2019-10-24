#ifndef TPOINT_H
#define TPOINT_H

#include "tgeom.h"

enum TPointType {
	ptUnknown = 0
	, ptBank = 1
	, ptHouse = 2
	, ptCafe = 3
	, ptShop = 4
	, ptTank = 5
	,ptPen=6
};

class TPoint :public TGeom {
public:
	TPointType typ;
	int selected;
	TPoint();
	virtual void Print();
};

#endif
