#include "graphics.h"

#include "stdlib.h"

void main()

{
	int size;

	int driver = VGA;

	int mode = VGAHI;

	int d[] = { 60 - 40,60 + 65,65 - 40,50 + 65,70 - 40,60 + 65,80 - 40,60 + 65,72 - 40,67 + 65,75 - 40,77 + 65,

	65 - 40,70 + 65,55 - 40,77 + 65,58 - 40,67 + 65,50 - 40,60 + 65,60 - 40,60 + 65 };

	int a[] = { 60 - 40,60 + 62,65 - 40,50 + 62,70 - 40,60 + 62,80 - 40,60 + 62,72 - 40,67 + 62,75 - 40,77 + 62,

	65 - 40,70 + 62,55 - 40,77 + 62,58 - 40,67 + 62,50 - 40,60 + 62,60 - 40,60 + 62 };

	int b[] = { 60 - 40,60 + 59,65 - 40,50 + 59,70 - 40,60 + 59,80 - 40,60 + 59,72 - 40,67 + 59,75 - 40,77 + 59,

	65 - 40,70 + 59,55 - 40,77 + 59,58 - 40,67 + 59,50 - 40,60 + 59,60 - 40,60 + 59 };

	int c[] = { 60 - 40,60 + 56,56 - 40,50 + 56,70 - 40,60 + 56,80 - 40,60 + 56,72 - 40,67 + 56,75 - 40,77 + 56,

	56 - 40,70 + 56,55 - 40,77 + 56,58 - 40,67 + 56,50 - 40,60 + 56,60 - 40,60 + 56 };

	int e[] = { 60 - 40,60 + 53,65 - 40,50 + 53,70 - 40,60 + 53,80 - 40,60 + 53,72 - 40,67 + 53,75 - 40,77 + 53,

	65 - 40,70 + 53,55 - 40,77 + 53,58 - 40,67 + 53,50 - 40,60 + 53,60 - 40,60 + 53 };

	int dl[] = { 20 - 10,150 + 5,25 - 10,150 + 5,27 - 10,145 + 5,30 - 10,150 + 5,35 - 10,150 + 5,30 - 10,155 - 2 + 5,

	34 - 1 - 10,162 - 3 + 5,27 - 10,155 + 5,20 + 1 - 10,162 - 3 + 5,25 - 10,155 - 2 + 5,20 - 10,155 + 5 };

	char* buffer;

	initgraph(&driver, &mode, "e:\\win-tc");

	cleardevice();

	setcolor(RED);

	setbkcolor(BLUE);

	setfillstyle(1, WHITE);

	rectangle(148, 100, 152, 400);

	floodfill(150, 101, RED);

	circle(150, 98, 5);

	floodfill(150, 98, RED);

	rectangle(152, 104, 156, 184);

	setfillstyle(1, RED);

	do

	{
		setviewport(156, 0, 258, 240, 1);

		clearviewport();

		arc(180 - 156, 50, 247, 297, 60);

		arc(180 - 156, 130, 247, 297, 60);

		arc(230 - 156, 159, 63, 113, 60);

		arc(230 - 156, 239, 63, 113, 60);

		line(258 - 156, 105, 258 - 156, 184); /*画五星红旗的边线*/

		setfillstyle(1, YELLOW);

		fillpoly(11, dl);

		fillpoly(11, d); /*画黄色的五星红旗*/

		floodfill(65 - 40, 120, RED);

		floodfill(20, 160, RED); /*填充五星，边线为红色*/

		size = imagesize(8, 148, 27, 168);

		buffer = malloc(size);

		getimage(8, 148, 27, 168, buffer); /*保存五星的信息*/

		putimage(8 + 20, 148 - 3, buffer, 1);

		putimage(8 + 30 + 2, 130, buffer, 1);

		putimage(8 + 33, 112, buffer, 1); /*将缓冲区中保存的内容回写到指定的地址*/

		setfillstyle(1, RED);

		floodfill(2, 165, RED); /*填充红旗旗面为红色*/

		delay(4000); /*延时*/

		clearviewport(); /*清屏，重新画第二面位置不同的红旗*/

		arc(180 - 156, 0, 247, 285, 107);

		arc(180 - 156, 80, 247, 285, 107);

		arc(230 - 156, 196, 70, 105, 96);

		arc(258 - 156, 279, 70, 105, 98);

		line(258 - 156, 105, 258 - 156, 184);

		setfillstyle(1, YELLOW);

		fillpoly(11, a);

		floodfill(65 - 40, 115, RED);

		putimage(8, 148 - 2, buffer, 1);

		putimage(8 + 20, 148 - 3 - 2, buffer, 1);

		putimage(8 + 30 + 2, 130 - 2, buffer, 1);

		putimage(8 + 33, 112 - 2, buffer, 1);

		setfillstyle(1, RED);

		floodfill(2, 165, RED);

		delay(3000); /*延时后再画第三面不同位置的红旗*/

		clearviewport();

		rectangle(0, 104, 100, 184);

		setfillstyle(1, YELLOW);

		fillpoly(11, b);

		floodfill(65 - 40, 115, RED);

		putimage(8, 148 - 4, buffer, 1);

		putimage(8 + 20, 148 - 3 - 4, buffer, 1);

		putimage(8 + 30 + 2, 130 - 4, buffer, 1);

		putimage(8 + 33, 112 - 4, buffer, 1);

		setfillstyle(1, RED);

		floodfill(2, 165, RED);

		delay(2000); /*延时后再画第四面红旗*/

		clearviewport();

		arc(180 - 156, 196, 75, 105, 96);

		arc(180 - 156, 279, 75, 105, 98);

		arc(230 - 156, 0, 257, 285, 107);

		arc(230 - 156, 80, 257, 285, 107);

		line(258 - 156, 105, 258 - 156, 184);

		setfillstyle(1, YELLOW);

		fillpoly(11, c);

		floodfill(65 - 40, 120, RED);

		putimage(8, 148 - 6, buffer, 1);

		putimage(8 + 20, 148 - 3 - 6, buffer, 1);

		putimage(8 + 30 + 2, 130 - 6, buffer, 1);

		putimage(8 + 33, 112 - 6, buffer, 1);

		setfillstyle(1, RED);

		floodfill(2, 165, RED);

		delay(3000); /*延时后画第五面红旗*/

		clearviewport();

		arc(180 - 156, 159, 63, 113, 60);

		arc(180 - 156, 239, 63, 113, 60);

		arc(230 - 156, 50, 247, 297, 60);

		arc(230 - 156, 130, 247, 297, 60);

		line(258 - 156, 105, 258, 184);

		setfillstyle(1, YELLOW);

		fillpoly(11, e);

		floodfill(65 - 40, 120, RED);

		putimage(8, 148 - 8, buffer, 1);

		putimage(8 + 20, 148 - 3 - 8, buffer, 1);

		putimage(8 + 30 + 2, 130 - 8, buffer, 1);

		putimage(8 + 33, 112 - 8, buffer, 1);

		setfillstyle(1, RED);

		floodfill(2, 165, RED);

		delay(3000);

		clearviewport(); /*整个*/

	}

	while (!kbhit()); /*按任意键退出动画*/

	closegraph();

	getch();

}