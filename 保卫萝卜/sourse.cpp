#include"menu.h"
extern IMAGE guaiwu1, guaiwu2;
extern int kx, ky;//窝的位置
extern int timeover;
void map::upload(radish &tem)
{
	queue<int>a;
	loadimage(&background, _T("background1.jpeg"));
	loadimage(&lujin, _T("路径.png"));
	loadimage(&wo1, _T("窝1.png"));
	loadimage(&wo2, _T("窝2.png"));
	fstream four("map.txt");
	loadimage(&guaiwu1, _T("怪物图片.png"));
	loadimage(&guaiwu2, _T("怪物2.png"));
	while (four.good())
	{
		int tem;
		four >> tem;
		if (four.eof())break;
		a.push(tem);
	}
	
	for (int i = 0; i < 7; i++)for (int j = 0; j < 13; j++)
	{
		backmap[i][j] = a.front();
		if (a.front() == 2)
		{
			tem.x = i, tem.y = j;
		}
		a.pop();
	}
}
void map::show(radish& tem)
{
	
	putimage(0,0, &background);
	for (int i = 0; i < 7; i++)for (int j = 0; j < 13; j++)
		if (backmap[i][j] == 1 || backmap[i][j] == 2)putimage(j * 60, i * 60 + 100, &lujin);
		else if (backmap[i][j] == -1)transparentimage2((j-1) * 60, (i-1) * 60 + 105, &wo2,&wo1),kx=i,ky=j;
	tem.show();
	//cout << tem.x << tem.y << endl;
	//cout << &guaiwu1<<endl;
}
void gameover()
{

}
void transparentimage2(int x, int y, IMAGE* srcimg, IMAGE* maskimg)
{
	putimage(x, y, maskimg, SRCAND);
	putimage(x, y, srcimg, SRCPAINT);
}
void transparentimage(int x,int y,int w,int h,int tx,int ty, IMAGE* srcimg, IMAGE* maskimg)
{
	putimage(x, y,w,h, maskimg,tx,ty, SRCAND);
	putimage(x, y,w,h, srcimg,tx,ty, SRCPAINT);
}
void monst::showblood()
{
	rectangle(x + 5, y + 5, x + 55, y + 15);
}
void monst1::showimage()
{
	int a = t % 3;
	switch (a)
	{
	//case 1:transparentimage()
	}
}