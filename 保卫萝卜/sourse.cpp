#include"menu.h"
extern IMAGE guaiwu1, guaiwu2;
extern int kx, ky;//窝的位置
extern int timeover;
extern int backmap[7][13];
extern int  zx, zy;//萝卜的位置
extern bool jieshu;
extern radish bradish;
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
			zx = i, zy = j;
		}
		if (a.front() == -1)kx = i, ky = j;
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
	line(0, 100, 1000, 100);
	line(780, 100, 780, 1000);
	//cout << tem.x << tem.y << endl;
	//cout << &guaiwu1<<endl;
}
void gameover()
{
	jieshu = false;
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
	rectangle(x +20, y +95, x + 85, y + 115);
	//cout << kx << ky << endl;
	setfillcolor(RED);
	fillrectangle(x + 20, y + 95, x + 20 + (blood / mmax)*65, y + 115);
}
void monst1::showimage()
{
	int a = t / 50%3;
	switch (a)
	{
	case 0:transparentimage(x, y+100, 120, 60, 6, 10, &guaiwu2, &guaiwu1); break;
	case 1:transparentimage(x, y+100, 130, 70, 130, 0, &guaiwu2, &guaiwu1); break;
	case 2:transparentimage(x, y+100, 129, 70, 260, 0, &guaiwu2, &guaiwu1); break;
	}
	t++;
}
void monst::move()
{
	stt = clock();
	if (stt - tt < 100)return;
	int dx[4] = { 0,1,-1,0 }, dy[4] = { 1,0,0,-1 };
	//cout << x << y << "kkk" << endl;
	//if (st[0][0])cout << "llllllll";
	//cout << zx << zy << endl;
	if (x % 60 == 0 && y % 60 == 0)
	{
		st[y / 60][x / 60] = false;
		if (y / 60 == zx && x / 60 == zy) is_death = true, bradish.injured();
		for (int i = 0; i < 4; i++)
		{
			int a = x / 60 + dy[i], b = y/60 + dx[i];
			if (a>=0&&b>=0&&a<7&&b<13&&st[b][a])fx = a - x / 60, fy = b - y / 60;
			//cout << a << b << "ll" << endl;
		}
		//cout << a << b <<"ll"<< endl;
	}
	x +=  fx, y +=  fy;
	tt = clock();
}
void gametime::showtime()
{
	int a = clock();
	string tem;
	tem = to_string((a - t) / 1000);
	outtextxy(5, 5, tem.c_str());
	for (int i = 0; i < ba.size(); i++)
	{
		if ((a - t) / 1000 == ba[i].first && aa[i]==1)
		{
			this->generate(ba[i].second.first, ba[i].second.second);
			aa[i] = 0;
			//cout << "lll" << endl;
		}
	}
}
void gametime::check()
{
	for(int i=0;i<qun.size();i++)
	{
		
		if (qun[i]->if_death())delete qun[i],qun.erase(qun.begin()+i),caichan+=300;
		else qun[i]->showblood(), qun[i]->showimage(), qun[i]->move();
	}
	bool flag = false;
	for (int i = 0; i < aa.size(); i++)if (aa[i] == 1)flag = true;
	if (qun.empty() && !flag)gameover();
}
void gametime:: generate(int lei, int size)
{

	switch (lei)
	{
	case 1:for (int i = 0; i < size; i++)
	{
		monst* tem = new monst1(1);
		qun.push_back(tem);
	}
		  break;
	default: break;
	}
}
void gametime::mianban(ExMessage a)
{
	int ddy = a.x / 60, ddx = (a.y - 100) / 60;
	
	if (backmap[ddx][ddy] != -1 && backmap[ddx][ddy] != 1 && backmap[ddx][ddy] != 2)this->showmianban(a.x, a.y);
}
void gametime::showmianban(int x, int y)
{
	if (zhankai)
	{
		int ddy = x / 60, ddx = (y - 100) / 60;
		int sxy = zkx / 60, sxx = (zky - 100) / 60;
		if (ddy == sxy + 1 && sxx == ddx&&backmap[sxx][sxy]!=0)
		{
			zhankai = false;
			tzhankai = clock();
		}
		else if (sxy == ddy && sxx ==ddx)
		{
			if (caichan >= 160)
			{
				weapon* tem = new bullet1(zkx / 60 * 60, (zky - 100) / 60 * 60+100,this);
				ta.push_back(tem);
				//system("pause");
			}
			zhankai = false;
		}
		else if (ddy == sxy && sxx == ddx + 1 && backmap[sxx][sxy] != 0)
		{
			//cout << "jjjjjjjjj" << endl;
			tisheng();
			zhankai = false;
		}
		else
		{
			tzhankai = clock();
			zhankai = true;
			zkx = x, zky = y;
		}
	}
	else
	{
		tzhankai = clock();
		zhankai = true;
		zkx = x, zky = y;
	}
}
void gametime::showwwmian()
{
	if (zhankai)
	{
		auto c = backmap[(zky - 100) / 60][zkx / 60];
		//cout << c << "c=多少" << endl;
		switch (c)
		{
		case 11:transparentimage2(zkx / 60 * 60, (zky - 100) / 60 * 60 - 60+100, &tusheng1, &tusheng2);
			transparentimage2(zkx / 60 * 60+60, (zky - 100) / 60 * 60+100, &cha1, &cha2); break;
		case 0: if (this->caichan >= 160)transparentimage(zkx / 60 * 60, (zky - 100) / 60 * 60+100, 60, 60, 70, 0, &tu1, &tu2); 
			  else transparentimage(zkx / 60 * 60, (zky - 100) / 60 * 60+100, 60, 60, 130, 0, &tu1, &tu2);  break;
		}
		int temt = clock();
		if (temt - tzhankai >= 3000)zhankai = false;
	}
	//transparentimage( 200,100, 60, 60, 130, 0, &tu1, &tu2); 
}
void gametime::showcaichan()
{
	string tem = to_string(this->caichan);
	outtextxy(20, 20, tem.c_str());
}
void gametime::tisheng()
{
	int temx = zkx / 60 * 60, temy = (zky-100)/ 60 * 60+100;
	for (int i = 0; i < ta.size(); i++)
	{
		if (ta[i]->is_xiang(this->caichan, temx, temy))ta[i]->gr(this);
	}
}
void gametime::jiancheshifou()
{
	for (int i = 0; i < ta.size(); i++)
	{
		for (int j = 0; j < qun.size(); j++)
		{
			//cout << "kkk" << endl;
			if (ta[i]->jianche(qun[j]))break;
		}
	}
}
void bullet1::showimage()
{
	IMAGE ttem1,ttem2;
	if (jiaodu >= 6.28)jiaodu = 0;
	transparentimage(x+10, y+10, 60, 50, 345, 20, &tu1, &tu2);
	rotateimage(&ttem1, &tt1[deng], jiaodu, WHITE);
	rotateimage(&ttem2, &tt2[deng], jiaodu, BLACK);
	transparentimage2(x , y , &ttem2, &ttem1); 
	int tem1, tem2;
	if (gongji == NULL)
	{
		if (jiaodu == 0)return;
		if (jiaodu > 6.283 - jiaodu)
		{
			jiaodu += min(0.001, 6.283 - jiaodu);
			return;
		}
		else
		{
			jiaodu -= min(0.001, jiaodu - 0);
			return;
		}
		return;
	}
	
	gongji->huoqu(tem1, tem2);
	tem2 += 100;
	double len = sqrt((y - tem2 - 5) * 1.0 * (y - tem2 - 5) * 1.0 + (tem1 + 35 - x) * 1.0 * (tem1 + 35 - x));
	double ss = acos((tem1 + 35 - x) * 1.0 / len);
	//cout << tem2 << " " << tem1 << " " << y << " " << x << endl;
	if (abs(ss - jiaodu) < 0.002)
	{
		IMAGE hh,hh2;
		rotateimage(&hh, &guangshu1, jiaodu, WHITE);
		rotateimage(&hh2, &guangshu2, jiaodu, BLACK);
		double zzx= (tem1 + 95 + x)*1.0/2, zzy = (tem2 + 65 + y) * 1.0 / 2;
		double minx = min(tem1 + 65, x + 30), miny = min(tem2+35, y + 30);
		transparentimage(minx,miny,2*zzx-2*minx,2*zzy-2*miny,400-zzx+minx,400-zzy+miny,&hh2,&hh);
		jiaodu = ss;
		gongji->injured(harm[deng]);
		if (gongji->if_death())gongji = NULL;
	}
	else
	{
		if (ss > jiaodu )
		{
			jiaodu += 0.001;
		}
		else
		{
			jiaodu -= 0.001;
		}
	};
}
void gametime::showhuopao()
{
	for (int i = 0; i < ta.size(); i++)ta[i]->showimage();
}