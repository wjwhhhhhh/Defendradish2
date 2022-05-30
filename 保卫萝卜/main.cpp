#include "menu.h"
using namespace std;
int backmap[7][13];
 IMAGE guaiwu1, guaiwu2;
 int kx, ky;//ÎÑµÄÎ»ÖÃ
 int timeover;
 int zx, zy;//ÂÜ²·µÄÎ»ÖÃ
 bool jieshu = true;
 radish bradish;//ÂÜ²·

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
void showwwwwtime(gametime *l, map *a)
{
	l->check();
	l->showcaichan();
	l->showtime();
	l->showhuopao();
}
void game()
{
	
}
int main()
{
	
	ExMessage m;
	//initialize();
	//game();
	//initgraph(860, 550, EW_SHOWCONSOLE);
	gametime l;
	map a;
	a.upload(bradish);
	initgraph(860, 550,EW_SHOWCONSOLE);
	//weapon* tem = new bullet1(240, 220, &l);
	
	while (jieshu)
	{
		BeginBatchDraw();
		a.show(bradish);
		
		thread zh(showwwwwtime,&l,&a);
		l.jiancheshifou();
		if (peekmessage(&m, EM_MOUSE)&& m.lbutton)
		{
			cout << m.x<<m.y << endl;
			l.mianban(m);
		}
		zh.join();
		l.showwwmian();
		EndBatchDraw();
		cleardevice();
	}
}