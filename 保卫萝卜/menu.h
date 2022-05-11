#pragma once
#include<iostream>
#include<fstream>
#include<thread>
#include<Windows.h>
#include<mmsystem.h>
#include<string>
#include <graphics.h>
#include <conio.h>
#include<queue>
#pragma comment (lib,"winmm.lib")
using namespace std;

class menu
{
public :

private :
};
void gameover();//游戏结束
void transparentimage2(int x, int y, IMAGE* srcimg, IMAGE* maskimg);
void transparentimage(int x, int y, int w, int h, int tx, int ty, IMAGE* srcimg, IMAGE* maskimg);
class radish//萝卜
{
public :
	friend class map;
	radish(int a, int b) :x(a), y(b)
	{
		blood = 10;
	}
	radish(){}
	void injured()
	{
		blood--;
		if (blood == 0)gameover();
	}
	void show()
	{
		loadimage(&tupian1, _T("萝卜的图片.jpeg"));
		loadimage(&tupian2, _T("萝卜的图片1.png"));
		transparentimage2(60 * y, 100 + 60 * x, &tupian1, &tupian2);
	}
private:
	int x, y,blood;//x和y坐标，blood血量
	IMAGE tupian1,tupian2;
};
class monst//基类
{
public:
	monst(int a, int b,int c,IMAGE tu) :x(a), y(b),v(c)
	{
		blood = 100;
		tu = tupian;
	}
	void attack(radish& a)
	{
		a.injured();
	}
	void showblood();
	void injured();
	void move();
private :
	const int mmax = 100;
	int blood;//血量
	int x, y;//坐标
	int v;//速度
	IMAGE tupian;
};
class monst1 :public monst
{
public :
	void showimage();
private:
	int t;//时间
};
class map
{
public:
	void upload(radish &tem);//读取
	void show(radish& tem);
private:
	IMAGE background,lujin,wo1,wo2;
	const int breadth = 60;
	int backmap[7][13];//-1为怪物的出生点，1为路径，2为萝卜的地点。
};
