#include "menu.h"
using namespace std;
int backmap[7][13];
 IMAGE guaiwu1, guaiwu2;
 int kx, ky;//窝的位置
 int timeover;
 int zx, zy;//萝卜的位置
 bool jieshu = true;
 radish bradish;//萝卜

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
void showwwwwtime(gametime* l, map* a)
{
	l->check();
	l->showcaichan();
	l->showtime();
	l->showhuopao();
}
void game()
{
	ExMessage m;
	//initialize();
	//game();
	//initgraph(860, 550, EW_SHOWCONSOLE);
	gametime l;
	map a;
	a.upload(bradish);
	initgraph(860, 550, EW_SHOWCONSOLE);
	//weapon* tem = new bullet1(240, 220, &l);
	while (jieshu)
	{
		BeginBatchDraw();
		a.show(bradish);

		thread zh(showwwwwtime, &l, &a);
		l.jiancheshifou();
		if (peekmessage(&m, EM_MOUSE) && m.lbutton)
		{
			cout << m.x << m.y << endl;
			l.mianban(m);
		}
		zh.join();
		l.showwwmian();
		EndBatchDraw();
		cleardevice();
	}
}
void initialize()
{
	IMAGE img1,h1,h2;
	//initgraph(1280, 720, EW_SHOWCONSOLE);
	//setfillcolor(GREEN);
	loadimage(&img1,_T("backgrondtupian.jpeg"));
	loadimage(&h1, _T("开始游戏.png"));
	loadimage(&h2, _T("开始游戏2.png"));
	initgraph(780, 520, EW_SHOWCONSOLE);
	putimage(0, 0, &img1);
	setfillcolor(GREEN);
	MymciSendString(_T("open background.mp3 alias BackMusic"), NULL);
	MymciSendString("play BackMusic repeat", NULL);
	transparentimage2(-50, 200, &h1, &h2);
	ExMessage m;
	while (1) 
	{ 
		//fillroundrect(200, 550, 400, 650, 30, 30);
		if (peekmessage(&m, EM_MOUSE) && m.lbutton)
	    {
			if (m.x > 30 && m.x < 399 && m.y>362 && m.y < 446)
			{
				game();
				return;
			}
	    }
	}
	closegraph();
}


int main()
{
	initialize();
}