#pragma once
#include<iostream>
using namespace std;
class menu
{
public :

private :
};
void gameover();//��Ϸ����
class radish//�ܲ�
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
private:int x, y,blood;//x��y���꣬bloodѪ��
};
class monst//����
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
	int blood;//Ѫ��
	int x, y;//����
};