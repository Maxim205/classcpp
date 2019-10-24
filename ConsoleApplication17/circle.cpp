#include "pch.h"
#include <iostream>
#include "consts.h"
#include "tgeom.h"
#include "circle.h"
#include "strutils.h"
#include "consoleroutine.h"

Circle::Circle() {
	TGeom::TGeom();

	r = 0;
}

Circle::~Circle() {
	Erase();
	TGeom::~TGeom();
}

void Circle::InitTest() {
	TGeom::InitTest();
	symb = '*';
	r = rand() % 4 + 3;
};

int Circle::Contains(const short X, const short Y) {
	int result = 0;
	if (((X - x)*(X - x) + (Y - y)*(Y - y)) <= (r * r)) {
		result = 1;
	}
	return result;
};

void Circle::Print() {
	consoleSetColors(color, bgcolor);
	for (int i = (x - r); i <= (x + r); i++) {
		for (int j = (y - r); j <= (y + r); j++) {
			if (1 == Contains(i, j)) {
				consoleGotoXY(i, j);
				printf("%c", symb);
			}
		}
	}
}

void Circle::Erase() {
	consoleSetColors(clBlack, clBlack);
	for (int i = (x - r); i <= (x + r); i++) {
		for (int j = (y - r); j <= (y + r); j++) {
			if (1 == Contains(i, j)) {
				consoleGotoXY(i, j);
				printf(" ");
			}
		}
	}
}

void Circle::SaveToFile(FILE *fileHandle) {
	fprintf_s(fileHandle, "TCIRC|%d|%d|%d|%d|%d|%d|%c|%s\n", id, x, y, r, (int)color, (int)bgcolor, symb, name);
}

int Circle::LoadFromStr(char *buffer) {
	int result = 0;
	char *p_block = (char *)malloc(defaultNameLength * sizeof(char));
	char *parser = buffer;
	parser = parseItem(parser, '|', p_block);
	parser = parseItem(parser, '|', p_block); id = atoi(p_block);
	parser = parseItem(parser, '|', p_block); x = atoi(p_block);
	parser = parseItem(parser, '|', p_block); y = atoi(p_block);
	parser = parseItem(parser, '|', p_block); r = atoi(p_block);
	parser = parseItem(parser, '|', p_block); color = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); bgcolor = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); symb = *p_block;
	parser = parseItem(parser, '\n', p_block); strcpy_s(name, strlen(p_block)+1, p_block);
	free(p_block);
	return result;
}
