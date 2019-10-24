#include "pch.h"
#include <iostream>
#include <conio.h>
#include "consoleroutine.h"
#include "consts.h"
#include "tgeom.h"
#include "tpoint.h"
#include "trect.h"
#include "circle.h"
#include "list2link.h"
#include<ctime>

void printState(list2 *points) {
	consoleSetColors(clBlack, clLightGreen);
	consoleGotoXY(0, 0);
	printf("count = %d         ", list2_count(points));
}

void clearBoomPoints(list2 *points, list2 *boom) {
	list2 *p = NULL;
	list2 *b = list2_gotofirst(boom);
	while (NULL != b) {
		Circle *c = (Circle*)b->geom;
		p = list2_gotofirst(points);
		while (NULL != p) {
			TPoint *t = (TPoint *)p->geom;
			if (0 != c->Contains(t->x, t->y)) {
				list2 *nxt = p->next;
				list2_del(p);
				p = nxt;
			}
			else {
				p = p->next;
			}
		}
		b = b->next;
	}
}

int main(int argc, char*argv[]) {
	
	srand(time(NULL));
		list2 *list = NULL;
		list2 *list1 = NULL;

		for (int i = 0; i < 1000; i++) {
			list = list2_ins(list);
			switch (rand() % 3 ) {
			  case 0: list->geom = new TPoint ; break;
			  case 1: list->geom = new TRect  ; break;
			  case 2: list->geom = new Circle; break;
			}
			list->geom->id = i;
			list->geom->InitTest();
		}
		int key = 0;
		int flag = 0;
		do
		{
			key = _getch();
			switch (key)
			{
			case KEY_ESCAPE:
				flag = 1;
				break;
			case KEY_F1:
				list2_print(list);
				list2_savetofile(list, "d:\\test_lis2link_classes.txt");
				list2_clear(list);
				break;
	
			case KEY_F2:
				list1 = list2_loadfromfile(list1, "d:\\test_lis2link_classes.txt");
				list2_print(list1);
				break;
			}
		} while (0== flag);
	


		list2_clear(list1);
	consoleGotoXY(0, consoleBuffSizeY()-1);
	consoleSetColors(clWhite, clBlack);
	return (0);
}
