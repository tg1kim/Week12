#pragma once

#include <stdio.h>

#pragma warning(disable: 4996 4326 6031)

#define	Abs(x)	((x) > 0 ? (x) : -(x))

void DrawFigure(int n);
void PrintChars(int n, char chr = '*', int nwLn = false);
