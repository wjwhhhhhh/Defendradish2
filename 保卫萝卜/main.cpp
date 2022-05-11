#include "menu.h"
#include<queue>

using namespace std;
 IMAGE guaiwu1, guaiwu2;
 int kx, ky;//ÎÑµÄÎ»ÖÃ
 int timeover;
void MymciSendString(const char * szCommand , char* szbuffer)//const string szCommand)
{
	if (NULL == szbuffer)
	{
		if (0 != mciSendString(szCommand, NULL, 0, NULL))
		{
			printf("%s false!\n", szCommand);
		}
		else
		{
			printf("%s success!\n", szCommand);
		}
	}
	else
	{
		if (0 != mciSendString(szCommand, szbuffer, 1024, NULL))
		{
			printf("%s false!\n", szCommand);
		}
		else
		{
			printf("%s success!\n", szCommand);
		}
	}
}
void initialize()
{
	IMAGE img1;
	initgraph(1280, 720, EW_SHOWCONSOLE);
	//setfillcolor(GREEN);
	loadimage(&img1,_T("backgrondtupian.jpeg"));
	initgraph(780, 520);
	putimage(0, 0, &img1);
	setfillcolor(GREEN);
	while (1) { fillroundrect(200, 550, 400, 650, 30, 30); }
	closegraph();
}
void game()
{
	
}
int main()
{
	//initialize();
	//game();
	map a;
	radish b;
	a.upload(b);
	initgraph(800, 550,EW_SHOWCONSOLE);
	while (1)
	{
		BeginBatchDraw();
		a.show(b);
		//line(0, 100, 800, 100);
		transparentimage(0,0,80,80,0, 0, &guaiwu2, &guaiwu1);
		//cout << &guaiwu1<<endl;
		//putimage(0, 0, &guaiwu1);
		EndBatchDraw();
	}
}