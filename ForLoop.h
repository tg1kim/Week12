#pragma once

#include <stdio.h>

#define abs(x)	(((x) < 0) ? -(x) : (x))

#pragma warning(disable: 4326 4996 6031)

void DrawFigure(int n);
void PrintLine(int n, int nY);
void PrintChars(int n, char chr = '*', int nwLn = false);
