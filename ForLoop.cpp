#include "ForLoop.h"

void main()
{
	while (1) {
		printf("? ");
		int n;
		scanf("%d", &n);
		if (n < 0)
			break;
		DrawFigure(n);
		putchar('\n');
	}
	printf("Bye, ...\n\n");
}

void DrawFigure(int n)
{
}

void PrintLine(int n, int nY)
{
}

void PrintChars(int n, char chr, int nwLn)
{
	for (int i = 0; i < n; i++)
		putchar(chr);
	if (nwLn)
		putchar('\n');
}