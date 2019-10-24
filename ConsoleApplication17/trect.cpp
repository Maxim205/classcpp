#include "pch.h"
#include <iostream>
#include "consts.h"
#include "tgeom.h"
#include "trect.h"
#include "strutils.h"
#include "consoleroutine.h"

TRect::TRect() {
	TGeom::TGeom();
	width = 0;
	height = 0;
}

TRect::~TRect() {
	Erase();
	TGeom::~TGeom();
}

void TRect::InitTest() {
	TGeom::InitTest();
	width = rand() % 5 + 3;
	height = rand() % 5 + 3;
};

int TRect::Contains(const short X, const short Y) {
	int result = 0;
	if ((X >= x) && (Y >= y) && (X <= (x + width)) && (Y <= (y + height))) {
		result = 1;
	}
	return result;
}

void TRect::Print() {
	consoleSetColors(color, bgcolor);
	for (int i = x; i < (x + width); i++) {
		for (int j = y; j < (y + height); j++) {
			consoleGotoXY(i, j);
			printf("%c", symb);
		}
	}
}

void TRect::Erase() {
	consoleSetColors(clBlack, clBlack);
	for (int i = x; i < (x + width); i++) {
		for (int j = y; j < (y + height); j++) {
			consoleGotoXY(i, j);
			printf(" ");
		}
	}
}

void TRect::SaveToFile(FILE *fileHandle) {
	fprintf_s(fileHandle, "TRECT|%d|%d|%d|%d|%d|%d|%d|%c|%s\n", id, x, y, width, height, (int)color, (int)bgcolor, symb, name);
}


int TRect::LoadFromStr(char *buffer) {
	int result = 0;
	char *p_block = (char *)malloc(defaultNameLength * sizeof(char));
	char *parser = buffer;
	parser = parseItem(parser, '|', p_block);
	parser = parseItem(parser, '|', p_block); id = atoi(p_block);
	parser = parseItem(parser, '|', p_block); x = atoi(p_block);
	parser = parseItem(parser, '|', p_block); y = atoi(p_block);
	parser = parseItem(parser, '|', p_block); width = atoi(p_block);
	parser = parseItem(parser, '|', p_block); height = atoi(p_block);
	parser = parseItem(parser, '|', p_block); color = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); bgcolor = (ConsoleColors)atoi(p_block);
	parser = parseItem(parser, '|', p_block); symb = *p_block;
	parser = parseItem(parser, '\n', p_block);
	strcpy_s(name, strlen(p_block)+1, p_block);
	
	free(p_block);
	return result;
}