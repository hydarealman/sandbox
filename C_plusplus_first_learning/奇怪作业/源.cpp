#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
	system(" color 0c");
	float x, y, a;
	for (y = 1.4f; y > -1; y = y - 0.1f)
	{
		for (x = -1.4f; x < 1.4f; x = x + .04f)
		{
			a = x * x + y * y - 1;
			putchar(a * a * a - x * x * y * y * y < 0.0f ? 'x' : ' ');
		}
		Sleep(50);
		printf("\n");
	}
	printf("\t王子公主们\n");
	printf("\t要天天开心\n");
	return 0;
}
