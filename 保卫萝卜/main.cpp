#include<iostream>
#include<thread>
#include<Windows.h>
#include<mmsystem.h>
#include<string>
#include <graphics.h>
#include <conio.h>

#pragma comment (lib,"winmm.lib")
using namespace std;
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
	//setfillcolor(GREEN);
	loadimage(&img1,_T("backgrondtupian.jpeg"));
	initgraph(1280, 720);
	putimage(0, 0, &img1);
	setfillcolor(GREEN);
	while (1) { fillroundrect(200, 550, 400, 650, 30, 30); }

	closegraph();
}
int main()
{
	initialize();

}