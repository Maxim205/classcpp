#include "pch.h"
#include <iostream>
#include "consts.h"
#include "tgeom.h"
#include "tpoint.h"
#include "consoleroutine.h"

TPoint::TPoint() {
	TGeom::TGeom();
	char s=symb;
	switch (typ) {
	case 0: typ = ptBank;    break;
	case 1: typ = ptHouse;   break;
	case 2: typ = ptCafe;    break;
	case 3: typ = ptShop;    break;
	case 4: typ = ptTank; break;
	case 5:typ = ptPen; break;
	}
	selected = 0;
	strcpy_s(name, defaultNameLength, "TPoint");
}

void TPoint::Print() {
	char s = symb;
	switch (typ) {
	case ptBank:s = 'B'; break;
	case ptHouse:s = 'H'; break;
	case ptCafe:s = 'C'; break;
	case ptShop:s = 'S'; break;
	case ptTank:s = 'T'; break;
	}
	consoleSetColors(color, bgcolor);
	consoleGotoXY(x, y);
	printf("%c", s);
}