#pragma once
#include<iostream>
using namespace std;
class menu
{
public :

private :
};
void gameover();//游戏结束
class radish//萝卜
{
public :
	radish(int a, int b) :x(a), y(b)
	{
		blood = 10;
	}
	void injured()
	{
		blood--;
		if (blood == 0)gameover();
	}
private:int x, y,blood;//x和y坐标，blood血量
};
class monst//基类
{
public:
	void attack(radish& a)
	{
		a.injured();
	}
	void showblood();
	void injured();
private :
	const int mmax = 100;
	int blood;//血量
	int x, y;//坐标
};