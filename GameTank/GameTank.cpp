#include "pch.h"
#include <iostream>
#include "../ConsoleApplication17/consoleroutine.h"
#include "../ConsoleApplication17/strutils.h"
#include "../ConsoleApplication17/tgeom.h"
#include "../ConsoleApplication17/consts.h"
#include "../ConsoleApplication17/trect.h"
#include "../ConsoleApplication17/tpoint.h"
#include "../ConsoleApplication17/list2link.h"
#include "../ConsoleApplication17/circle.h"
#include<stdio.h>
#include <conio.h>


int tank_contains(list2 *map, short x, short y) {
	list2 *item = list2_gotofirst(map);
	while (NULL != item) {
		if (1 == item->geom->Contains(x, y)) {
			return 1;
		}
		item = item->next;
	}
	return 0;
}

int main(int argc, char*argv[])
{
	list2 *map1 = NULL;
	map1 = list2_loadfromfile(map1, "d:\\map.txt");
	TRect *console1 = new TRect();
	console1->x = 1;
	console1->y = 1;
	console1->width = consoleSizeX() - 1;
	console1->height = consoleSizeY() - 1;

	TPoint *tank1 = new TPoint();
	tank1->x = console1->x + console1->width / 2;
	tank1->y = console1->y + console1->height / 2;
	tank1->typ = ptPen;
	tank1->bgcolor = clLightGreen;
	tank1->color = clLightGreen;


	int flag1 = 0;
	int flag = 0;
	int key = 0;
	do {
		while (0 == flag1)
		{
			if (0 == map_contains(map1, tank1->x, tank1->y))
			{
				printStatus1(tank1->x, tank1->y, 0, 0);
				flag1 = 1;
			}
			tank1->x++;
		}
		list2_print(map1);

		tank1->Print();
		consoleGotoXY(tank1->x, tank1->y);
		key = _getch();
		tank1->Erase();
		switch (key) {
		case KEY_ESCAPE: {
			flag = 1;
			break;
		}


		case KEY_LEFT:
		{
			if ((tank1->x > console1->x) && (0 == map_contains(map1, tank1->x - 1, tank1->y))) {
				tank1->x--;
			}
			break;
		}
		case KEY_RIGHT: {
			if( (tank1->x < console1->width)&& (0 == map_contains(map1, tank1->x+1, tank1->y))) {
				tank1->x++;
			}
			break;
		}
		case KEY_UP: {
			if ((tank1->y > console1->y)&& (0 == map_contains(map1, tank1->x, tank1->y-1))) {
				tank1->y--;
			}
			break;
		}
		case KEY_DOWN: {
			if( (tank1->y < console1->height) && (0 == map_contains(map1, tank1->x, tank1->y + 1))) {
				tank1->y++;
			}
			break;
		}
		}
	} while (0 == flag);


	delete tank1;
	//delete console;

	consoleSetColors(clWhite, clBlack);




}