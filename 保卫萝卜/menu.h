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
void gameover();//��Ϸ����
void transparentimage2(int x, int y, IMAGE* srcimg, IMAGE* maskimg);
void transparentimage(int x, int y, int w, int h, int tx, int ty, IMAGE* srcimg, IMAGE* maskimg);
class radish//�ܲ�
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
		loadimage(&tupian1, _T("�ܲ���ͼƬ.jpeg"));
		loadimage(&tupian2, _T("�ܲ���ͼƬ1.png"));
		transparentimage2(60 * y, 100 + 60 * x, &tupian1, &tupian2);
	}
private:
	int x, y,blood;//x��y���꣬bloodѪ��
	IMAGE tupian1,tupian2;
};
class monst//����
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
	int blood;//Ѫ��
	int x, y;//����
	int v;//�ٶ�
	IMAGE tupian;
};
class monst1 :public monst
{
public :
	void showimage();
private:
	int t;//ʱ��
};
class map
{
public:
	void upload(radish &tem);//��ȡ
	void show(radish& tem);
private:
	IMAGE background,lujin,wo1,wo2;
	const int breadth = 60;
	int backmap[7][13];//-1Ϊ����ĳ����㣬1Ϊ·����2Ϊ�ܲ��ĵص㡣
};
