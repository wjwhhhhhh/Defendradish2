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
extern int kx, ky;//窝的位置
extern int timeover;
extern int backmap[7][13];
extern int  zx, zy;//萝卜的位置
extern bool jieshu;
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
		loadimage(&tupian1, _T("萝卜的图片.jpeg"));
		loadimage(&tupian2, _T("萝卜的图片1.png"));
		transparentimage2(60 * y, 100 + 60 * x, &tupian1, &tupian2);
		string tem;
		tem = to_string(blood);
		//cout << blood << endl;
		outtextxy(60 * y, 100 + 60 * x, tem.c_str());
	}
private:
	int x, y,blood;//x和y坐标，blood血量
	IMAGE tupian1,tupian2;
};
extern radish bradish;
class monst//基类
{
public:
	monst(int c) 
	{
		v = c;
		x = ky*60, y = kx*60;
		//cout << kx << ky << endl;
		blood = 100;
		for (int i = 0; i < 7; i++)for (int j = 0; j < 13; j++)
		{
			if (backmap[i][j] != 0)st[i][j] = true;
		}
		is_death = false;
		//if (st[0][0])cout << "sss";
		 tt = clock();
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
	void huoqu(int &a, int &b)
	{
		a = x, b = y;
	}
	virtual void showimage() = 0;
	int x, y;//坐标
private :
	const double mmax = 100;
	double blood;//血量
	int v;//速度
	bool st[7][13];//用来记录那些经过
	int fx, fy;//用来位移
	IMAGE tupian;
	bool is_death;
	int tt;//开始时间
	int stt;//位移时间
};
class monst1 :public monst
{
public :
	void showimage();
	monst1(int c) :monst(c) { t = 0; };
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
	int a, b;//-1为怪物的出生点，1为路径，2为萝卜的地点。
};
class weapon;
class bullet1;
class gametime
{
public:
	friend bullet1;
	friend weapon;
	gametime()
	{
		t = clock();
		ba.push_back({ 3,{1,1} });
		aa.push_back(1);
		ba.push_back({ 10,{1,1} });
		aa.push_back(1);
		ba.push_back({ 15,{1,1} });
		aa.push_back(1);
		ba.push_back({ 20,{1,1} });
		aa.push_back(1);
		ba.push_back({ 100,{1,1} });
		aa.push_back(1);
		zhankai = false;
		loadimage(&cha1, _T("叉1.png"));
		loadimage(&cha2, _T("叉2.png"));
		loadimage(&tusheng1, _T("提升.png"));
		loadimage(&tusheng2, _T("提升2.png"));
		loadimage(&tu1, _T("火塔2.png"));
		loadimage(&tu2, _T("火塔1.png"));
		caichan = 1000;
	}
	//void settime();//设置时间波数
	void generate(int lei, int size);
	void mianban(ExMessage);
	void check();
	void showtime();
	void showmianban(int x, int y);
	void showwwmian();
	void showcaichan();//展示有多少钱
	void tisheng();//提升等级
	void jiancheshifou();
	void showhuopao();
private:
	int t;//时间;
	vector<monst*>qun;
	vector <weapon*> ta;
	vector<PII> ba;
	vector<int> aa;
	bool zhankai;//是否展开
	int tzhankai;//展开时间
	int zkx, zky;
	IMAGE cha1, cha2;
	IMAGE tusheng1, tusheng2;
	IMAGE tu1, tu2;
	int caichan;
};
class weapon//塔
{
public:
	weapon()
	{
		t = clock();
		is_death = false;
		gongjijuli = 10;
	}
	void gr(gametime *l)
	{
		//system("pause");
		l->caichan -= groop[deng];
		if (deng < 2)deng++;
	}
	bool fandeath()
	{
		return is_death;
	}
	bool is_xiang(int t,int a, int b)
	{
		return x == a && y == b && t >= groop[deng];
	}
	bool jianche(monst *tem)
	{
		int tem1, tem2;
		int ccx, ccy;
		tem->huoqu(tem1, tem2);
		//cout<<(x + 30 - tem1 - 60)* (x + 30 - tem1 - 60) + (y + 30 - tem2 - 30 - 100) * (y + 30 - tem2 - 30-100)<< endl;

		if (gongji != NULL)return true;
		if((x + 30 - tem1 - 60) * (x + 30 - tem1 - 60) + (y + 30 - tem2 - 30-100) * (y + 30 - tem2 - 30-100) < 50000)
		{
			gongji = tem;
			cout << "kkk";
			return true;
		}
		return false;
	}
	virtual void showimage() = 0;
private:
	bool is_death;
	int gongjijuli;
protected:
	int x, y;
	int deng;//等级
	int t;//产生时间
	monst* gongji;
	int harm[3];
	int groop[2];
};
class bullet1 :public weapon//塔类型1
{
public:
	bullet1(int a, int b,gametime*m) :weapon()
	{
		x = a, y = b;
		worth = 200;
		deng = 0;
		m->caichan -=worth;
		loadimage(&tu1, _T("火塔2.png"));
		loadimage(&tu2, _T("火塔1.png"));
		harm[0] = 1, harm[1] = 2, harm[2] = 3;
		groop[0] = 300, groop[1] = 400;
		gongji = NULL;
		backmap[(b-100) / 60][a / 60] = 11;//改变地图
	   jiaodu=0;
	   loadimage(&tt1[0], _T("火塔111.png"));
	   loadimage(&tt2[0], _T("火塔112.png"));
	   loadimage(&tt1[1], _T("火塔124.png"));
	   loadimage(&tt2[1], _T("火塔122.png"));
	   loadimage(&tt1[2], _T("火塔333.png"));
	   loadimage(&tt2[2], _T("火塔334.png"));
	   loadimage(&guangshu1, _T("光束.png"));
	   loadimage(&guangshu2, _T("光束2.png"));
	}
	void showimage();
	~bullet1()
	{
		backmap[x / 60][(y - 100) / 60] = 0;
	}
private:
	IMAGE tt1[3],tt2[3];
	IMAGE guangshu1, guangshu2;
	IMAGE tu1, tu2;
	int worth;
	double jiaodu;
};