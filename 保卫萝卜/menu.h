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
#include<ctime>
#include<queue>
#include<vector>
#pragma comment (lib,"winmm.lib")
using namespace std;
typedef pair<int,pair<int, int> >PII;
extern IMAGE guaiwu1, guaiwu2;
extern int kx, ky;//�ѵ�λ��
extern int timeover;
extern int backmap[7][13];
extern int  zx, zy;//�ܲ���λ��
extern bool jieshu;
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
		blood = 2;
	}
	radish() {
		blood = 2;
	}
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
		string tem;
		tem = to_string(blood);
		//cout << blood << endl;
		outtextxy(60 * y, 100 + 60 * x, tem.c_str());
	}
private:
	int x, y,blood;//x��y���꣬bloodѪ��
	IMAGE tupian1,tupian2;
};
extern radish bradish;
class monst//����
{
public:
	monst(int c) 
	{
		v = c;
		x = ky*60, y = kx*60;
		//cout << kx << ky << endl;
		blood = 10;
		for (int i = 0; i < 7; i++)for (int j = 0; j < 13; j++)
		{
			if (backmap[i][j] != 0)st[i][j] = true;
		}
		is_death = false;
		//if (st[0][0])cout << "sss";
	}
	void attack(radish& a)
	{
		a.injured();
	}
	void showblood();
	void injured(int a)
	{
		blood -= a;
		if (blood <= 0)is_death = true;
	}
	void move();
	int showx()
	{
		return x;
	}
	int showy()
	{
		return y;
	}
	bool if_death()
	{
		return is_death;
	}
	virtual void showimage() = 0;
	int x, y;//����
private :
	const double mmax = 100;
	double blood;//Ѫ��
	int v;//�ٶ�
	bool st[7][13];//������¼��Щ����
	int fx, fy;//����λ��
	IMAGE tupian;
	bool is_death;
};
class monst1 :public monst
{
public :
	void showimage();
	monst1(int c) :monst(c) { t = 0; };
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
	int a, b;//-1Ϊ����ĳ����㣬1Ϊ·����2Ϊ�ܲ��ĵص㡣
};
class weapon;
class bullet1;
class gametime
{
public:
	friend bullet1;
	gametime()
	{
		t = clock();
		while (qun.size())qun.pop();
		while (temm.size())temm.pop();
		ba.push_back({ 3,{1,1} });
		aa.push_back(1);
		ba.push_back({ 100,{1,1} });
		aa.push_back(1);
		//ba.push_back({ 10,{1,1} });
		//aa.push_back(1);
		zhankai = false;
		loadimage(&cha1, _T("��1.png"));
		loadimage(&cha2, _T("��2.png"));
		loadimage(&tusheng1, _T("����.png"));
		loadimage(&tusheng2, _T("����2.png"));
		loadimage(&tu1, _T("����2.png"));
		loadimage(&tu2, _T("����1.png"));
		caichan = 300;
	}
	//void settime();//����ʱ�䲨��
	void generate(int lei, int size);
	void mianban(ExMessage);
	void check();
	void showtime();
	void showmianban(int x, int y);
	void showwwmian();
	void showcaichan();//չʾ�ж���Ǯ
	void tisheng();//�����ȼ�
private:
	int t;//ʱ��;
	queue<monst*>qun, temm;
	vector <weapon*> ta;
	vector<PII> ba;
	vector<int> aa;
	bool zhankai;//�Ƿ�չ��
	int tzhankai;//չ��ʱ��
	int zkx, zky;
	IMAGE cha1, cha2;
	IMAGE tusheng1, tusheng2;
	IMAGE tu1, tu2;
	int caichan;
};
class weapon//��
{
public:
	weapon()
	{
		t = clock();
		is_death = false;
		gongjijuli = 10;
	}
	void gr()
	{
		if (deng < 2)deng++;
	}
	bool fandeath()
	{
		return is_death;
	}
	bool is_xiang(int a, int b)
	{
		return x == a && y == b;
	}
	void setgongji(monst* tem)
	{
		gongji = tem;
	}
	virtual void showimage(int a, int b) = 0;
private:
	bool is_death;
	int gongjijuli;
protected:
	int x, y;
	int deng;//�ȼ�
	int t;//����ʱ��
	monst* gongji;
};
class bullet1 :public weapon//������1
{
public:
	bullet1(int a, int b,gametime*m) :weapon()
	{
		x = a, y = b;
		m->caichan -= 200;
		loadimage(&tu1, _T("����2.png"));
		loadimage(&tu2, _T("����1.png"));
		harm[0] = 10, harm[1] = 20, harm[2] = 30;
		groop[0] = 300, groop[1] = 400;
		gongji = NULL;
		backmap[(b-100) / 60][a / 60] = 11;//�ı��ͼ
		int jiaodu;
	}
	void showimage(int a, int b);//a,bΪ�����λ��
	void attack()
	{

	}
	~bullet1()
	{
		backmap[x / 60][(y - 100) / 60] = 0;
	}
private:
	int harm[3];
	int groop[2];

	IMAGE tu1, tu2;
	int worth;
	int jiaodu;
};