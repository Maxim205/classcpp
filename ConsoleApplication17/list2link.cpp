#include "pch.h"
#include <iostream>
#include "consts.h"
#include "strutils.h"
#include "tgeom.h"
#include "tpoint.h"
#include "trect.h"
#include "circle.h"
#include "list2link.h"

list2 *list2_create() {
	list2 *item;
	item = (list2 *)malloc(sizeof(struct list2));
	item->geom = NULL;
	item->next = NULL;
	item->prev = NULL;
	return(item);
};

list2 *list2_ins(list2 *list) {
	list2 *item = list2_create(); //создание эл.
	item->prev = list;  // инициализация указателя предыдущего эл-та
	if (NULL != list) {  // преверяем, существует ли предыдущий элемент (пустой список)
		item->next = list->next;
		if (NULL != list->next) { // проверяем, является ли предыдущий эл-т конечным или за ним есть ещё?
			list->next->prev = item;
		}
		list->next = item; // переопределение упредыдущего эл-та указателя следующего на себя
	}
	return(item);
};

void list2_del(list2 *list) {
	if (NULL == list) {
		return;
	}
	list2 *nxt, *prv;
	nxt = list->next;
	prv = list->prev;
	if (NULL != nxt) {   // не является ли элемент конечным в списке? 
		nxt->prev = list->prev;
	}
	if (NULL != prv) {   // не является ли элемент первым в списке?
		prv->next = list->next;
	}
	if (NULL != list->geom) {
		delete list->geom;
	}
	free(list);
};

list2 *list2_gotofirst(list2 *list) {
	list2 *item = list;
	if (NULL != item) {
		while (NULL != item->prev) {
			item = item->prev;
		}
	}
	return (item);
};

list2 *list2_gotolast(list2 *list) {
	list2 *item = list;
	if (NULL != item) {
		while (NULL != item->next) {
			item = item->next;
		}
	}
	return (item);
};

int list2_count(list2 *list) {
	int result = 0;
	list2 *item = list2_gotofirst(list);
	while (NULL != item) {
		result++;
		item = item->next;
	}
	return result;
};

void list2_print(list2 *list) {
	if (NULL != list)
	{
		list2 *item = list2_gotofirst(list);
		while (NULL != item) {
			if (NULL != item->geom) {
				item->geom->Print();
			}
			item = item->next;
		}
	}
};

void list2_clear(list2 *list) {
	list2 *item = list2_gotolast(list);
	while (NULL != item) {
		list2 *delitem = item;
		item = item->prev;
		list2_del(delitem);
	}
}

int list2_savetofile(list2 *list, const char *filename) {
	FILE *file;
	int result = fopen_s(&file, filename, "w+");
	if (0 == result) {
		list2 *item = list2_gotofirst(list);
		while (NULL != item) {
			item->geom->SaveToFile(file);
			item = item->next;
		}
		fclose(file);
	}
	return result;
}


list2 *list2_loadfromfile(list2 *list, const char *filename) {
	FILE *file;
	list2 *item = list;
	int result = fopen_s(&file, filename, "r");
	if (0 == result) {
		char *objname = NULL, *buffer = NULL, *work = NULL;
		objname = (char*)malloc(defaultNameLength * sizeof(char));
		buffer = (char *)malloc(bufferLen * sizeof(char));
		work = buffer;

		nullStr(buffer, bufferLen);
		while (EOF != (*work = fgetc(file))) {
			if ('\n' == *work) {
				parseItem(buffer, '|', objname);
				item = list2_ins(item);
				if (0 == strcmp(objname, "TGEOM")) {
					item->geom = new TPoint();
				}
				else if (0 == strcmp(objname, "TRECT")) {
					item->geom = new TRect();
				}
				else if (0 == strcmp(objname, "TCIRC")) {
					item->geom = new Circle();
				}
				if (NULL != item->geom) {
					item->geom->LoadFromStr(buffer);
				}
				nullStr(buffer, bufferLen);
				work = buffer;
			}
			else {
				work++;
			}
		}
		if ((work != buffer) && (0 < strlen(buffer))) {
			parseItem(buffer, '|', objname);
			item = list2_ins(item);
			if (0 == strcmp(objname, "TGEOM")) {
				item->geom = new TPoint();
			}
			else if (0 == strcmp(objname, "TRECT")) {
				item->geom = new TRect();
			}
			else if (0 == strcmp(objname, "TCIRC")) {
				item->geom = new Circle();
			}
			if (NULL != item->geom) {
				item->geom->LoadFromStr(buffer);
			}
		}
		free(buffer);
		free(objname);
		fclose(file);
	}
	return item;
}

list2 *map_add_TPoint(list2 *map, short x, short y, TPointType t,
	ConsoleColors color, ConsoleColors bgcolor) {
	TPoint *p = new TPoint();
	p->x = x;
	p->y = y;
	p->typ = t;
	p->color = color;
	p->bgcolor = bgcolor;
	list2 *result = list2_ins(map);
	result->geom = p;
	return result;
}
void printStatus1(short x, short y, short Left, short Top) {
	char *s = (char *)malloc(255 * sizeof(char));
	nullStr(s, 255);
	strcpy_s(s, 255, "F2=Save DEL=Delete F3=TPoint(Bank) F4=TPoint(House) F5=TPoint(Cafe) F6=TPoint(Shop) ");
	consoleSetColors(clBlack, clLightRed);
	consoleGotoXY(Left, Top);
	printf("x:3%d y:%3d      %s", x, y, s);
	free(s);
}
int map_contains(list2 *map, short x, short y) {
	list2 *item = list2_gotofirst(map);
	while (NULL != item) {
		if (1 == item->geom->Contains(x, y)) {
			return 1;
		}
		item = item->next;
	}
	return 0;
}
