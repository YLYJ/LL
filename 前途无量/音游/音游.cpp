
#include"pch.h"
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tlhelp32.h>
#pragma comment(lib,"Winmm.lib")

//123分别代表红黄蓝，
char key;
IMAGE img_bk;
IMAGE img_victory;
IMAGE img_tools;
IMAGE img_beijing;
IMAGE logo;
int GamePrase = 0;
int z;//测试数据
int high, wedith;
int x, y;	//坐标
int gap;	//点与点之间的间距
int i, j, smallC, middleC, largeC;		//循环使用的变量
int size;	//点到能拖动边界的距离
int num = 0;
int color_size;
MOUSEMSG m;
COLORREF Defcolor[4];
int score;
int money;
int faulse=0;  //划分两种增加金钱的值
int colorrecorder;//记录颜色的
int a;
int b = 0;
int position_x, position_y;
int jnnum;
int k ;
int jnget;  //是否点到锦囊
int q=15;   //j锦囊单价
int n; //最多能买锦囊的个数

struct Circle
{
	int x;
	int y;
	int get;
	int exist;
	int type[3];
	int color[3];
	int birth[3];//是圆还是矩形
};  


struct point
{
	int x;
	int y;
	int getcircle[3];
	int getcolor[3];
	int getbirth[3];
};

point p[10];
Circle c[4];



void back1()	//圆环1回到初始位置
{
	c[1].x = p[1].x;
	c[1].y = p[9].y +80;
}

void back2()	//圆环2回到初始位置
{
	c[2].x = p[2].x;
	c[2].y = p[9].y + 80;
}

void back3()	//圆环3回到初始位置
{
	c[3].x = p[3].x;
	c[3].y = p[9].y + 80;
}

void back4()		//锦囊回到最初的位置
{
	position_x = 50;
	position_y = 490;
}
void stay1()	//圆环1在鼠标弹起位置定位到临近点
{
	c[1].x = p[i].x;
	c[1].y = p[i].y;
}

void stay2()	//圆环2在鼠标弹起位置定位到临近点
{
	c[2].x = p[i].x;
	c[2].y = p[i].y;
}

void stay3()	//圆环3在鼠标弹起位置定位到临近点
{
	c[3].x = p[i].x;
	c[3].y = p[i].y;
}

void out(int n)
{
	c[n].x = -100;
	c[n].y = -100;
}

void ini()
{
	score = 0;
	money = 0;
	for (i = 1; i <= 9; i++)
	{
		for (j = 0; j < 3; j++)
		{
			p[i].getcircle[j] = 0;
			p[i].getcolor[j] = 0;
			back1();
			back2();
			back3();
		}
	}
}
void MoneyPlus()   //消除后有铜钱加金币
{
	if (p[i].getcircle[0] == 1 && p[i].getcircle[1] == 1 && p[i].getcircle[2] == 0&& p[i].getbirth[0] == 1&& p[i].getbirth[1] == 0)
	{money = money + 3;
	mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
	mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
	}
	if (p[i].getcircle[0] == 1 && p[i].getcircle[1] == 0 && p[i].getcircle[2] == 1 && p[i].getbirth[0] == 1 && p[i].getbirth[2] == 0)
	{
		money = money + 5;
		mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
		mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
		mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
		mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
	}
	
}
void clean_xieshuheng1(int clean_color)
{
	for (i = 1; i <= 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[7].getcolor[j] == clean_color)
		{
			p[7].getcolor[j] = 0;
			p[7].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (i = 5; i <= 9; i = i + 4)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	score = score + 10;

	mciSendString("stop music1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music1", NULL, 0, NULL);
	mciSendString("play music1", NULL, 0, NULL); // 仅播放一次
}
void judgeclean_xieshuheng1(int judge_color)	//判断第一行第一列和斜对角线颜色是否相同
{
	num = 0;
	for (i = 1; i <= 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[7].getcircle[j] == 1 && p[7].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (i = 5; i <= 9; i = i + 4)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 7)
	{
		clean_xieshuheng1(judge_color);
	}
}
void clean_xieshuheng2(int clean_color)
{
	for (i = 7; i <= 9; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[3].getcolor[j] == clean_color)
		{
			p[3].getcolor[j] = 0;
			p[3].getcircle[j] = 0;
			MoneyPlus();
		}
	}

	for (j = 0; j < 3; j++)
	{
		if (p[6].getcolor[j] == clean_color)
		{
			p[6].getcolor[j] = 0;
			p[6].getcircle[j] = 0;
			MoneyPlus();
		}
	}

	for (i = 1; i <= 5; i = i + 4)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	score = score + 10;

	mciSendString("stop music1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music1", NULL, 0, NULL);
	mciSendString("play music1", NULL, 0, NULL); // 仅播放一次

}
void judgeclean_xieshuheng2(int judge_color)	//判断第三行第三列和斜对角线颜色是否相同
{
	num = 0;
	for (i = 7; i <= 9; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[3].getcircle[j] == 1 && p[3].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[6].getcircle[j] == 1 && p[6].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (i = 1; i <= 5; i = i + 4)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 7)
	{
		clean_xieshuheng2(judge_color);
	}
}
void clean_xieshuheng3(int clean_color)       //清除左下到右上斜对角线和第一行第三列
{
	for (i = 1; i <= 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[6].getcolor[j] == clean_color)
		{
			p[6].getcolor[j] = 0;
			p[6].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcolor[j] == clean_color)
		{
			p[9].getcolor[j] = 0;
			p[9].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (i = 5; i <= 7; i = i + 2)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	score = score + 10;

	mciSendString("stop music1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music1", NULL, 0, NULL);
	mciSendString("play music1", NULL, 0, NULL); // 仅播放一次
}
void judgeclean_xieshuheng3(int judge_color)	//判断第一行第三列和斜对角线颜色是否相同
{
	num = 0;
	for (i = 1; i <= 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[6].getcircle[j] == 1 && p[6].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcircle[j] == 1 && p[9].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (i = 5; i <= 7; i = i + 2)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 7)
	{
		clean_xieshuheng3(judge_color);
	}
}

void clean_xieshuheng4(int clean_color)    //清除第三行第一列和斜对角线
{
	for (i = 1; i <= 7; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}


	for (j = 0; j < 3; j++)
	{
		if (p[8].getcolor[j] == clean_color)
		{
			p[8].getcolor[j] = 0;
			p[8].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcolor[j] == clean_color)
		{
			p[9].getcolor[j] = 0;
			p[9].getcircle[j] = 0;
			MoneyPlus();
		}

	}
	
	for (i = 3; i <= 5; i = i + 2)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	score = score + 10;

	mciSendString("stop music1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music1", NULL, 0, NULL);
	mciSendString("play music1", NULL, 0, NULL); // 仅播放一次
}
void judgeclean_xieshuheng4(int judge_color)	//判断第三行第一列和斜对角线颜色是否相同
{
	num = 0;
	for (i = 1; i <= 7; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[8].getcircle[j] == 1 && p[8].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcircle[j] == 1 && p[9].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (i = 3; i <=5; i = i + 2)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 7)
	{
		clean_xieshuheng4(judge_color);
	}
}
void clean_xieshuheng5(int clean_color)    //清除米字形
{
	for (i = 4; i <= 6; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}	

	for (j = 0; j < 3; j++)
	{
		if (p[2].getcolor[j] == clean_color)
		{
			p[2].getcolor[j] = 0;
			p[2].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[8].getcolor[j] == clean_color)
		{
			p[8].getcolor[j] = 0;
			p[8].getcircle[j] = 0;
			MoneyPlus();
		}
	}	
	
   for (j = 0; j < 3; j++)
	{
	if (p[1].getcolor[j] == clean_color)
	{
		p[1].getcolor[j] = 0;
		p[1].getcircle[j] = 0;
		MoneyPlus();
	}
	}
  
   for (j = 0; j < 3; j++)
   {
	   if (p[9].getcolor[j] == clean_color)
	   {
		   p[9].getcolor[j] = 0;
		   p[9].getcircle[j] = 0;
		   MoneyPlus();
	   }
   }
 
   for (j = 0; j < 3; j++)
   {
	   if (p[3].getcolor[j] == clean_color)
	   {
		   p[3].getcolor[j] = 0;
		   p[3].getcircle[j] = 0;
		   MoneyPlus();
	   }
   }
  
   for (j = 0; j < 3; j++)
   {
	   if (p[7].getcolor[j] == clean_color)
	   {
		   p[7].getcolor[j] = 0;
		   p[7].getcircle[j] = 0;
		   MoneyPlus();
	   }
   }
	
	score = score + 14;

	mciSendString("stop music1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music1", NULL, 0, NULL);
	mciSendString("play music1", NULL, 0, NULL); // 仅播放一次
}
void judgeclean_xieshuheng5(int judge_color)	//判断米字形是否颜色相同
{
	num = 0;
	for (i = 4; i <= 6; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
		for (j = 0; j < 3; j++)
		{
			if (p[2].getcircle[j] == 1 && p[2].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
		for (j = 0; j < 3; j++)
		{
			if (p[8].getcircle[j] == 1 && p[8].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
		for (j = 0; j < 3; j++)
		{
			if (p[1].getcircle[j] == 1 && p[1].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
		for (j = 0; j < 3; j++)
		{
			if (p[9].getcircle[j] == 1 && p[9].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
		for (j = 0; j < 3; j++)
		{
			if (p[3].getcircle[j] == 1 && p[3].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
		for (j = 0; j < 3; j++)
		{
			if (p[7].getcircle[j] == 1 && p[7].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	if (num == 9)
	{
		clean_xieshuheng5(judge_color);
	}
}
void clean_xieshu1(int clean_color)    //清除第二列和两条斜对角线
{
	for (i = 2; i <= 8; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[1].getcolor[j] == clean_color)
		{
			p[1].getcolor[j] = 0;
			p[1].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcolor[j] == clean_color)
		{
			p[9].getcolor[j] = 0;
			p[9].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[3].getcolor[j] == clean_color)
		{
			p[3].getcolor[j] = 0;
			p[3].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[7].getcolor[j] == clean_color)
		{
			p[7].getcolor[j] = 0;
			p[7].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	score = score + 10;

	mciSendString("stop music1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music1", NULL, 0, NULL);
	mciSendString("play music1", NULL, 0, NULL); // 仅播放一次
}
void judgeclean_xieshu1(int judge_color)	//判断第二列和两条对角线是否颜色相同
{
	num = 0;
	for (j = 0; j < 3; j++)
	{
		if (p[1].getcircle[j] == 1 && p[1].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcircle[j] == 1 && p[9].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[3].getcircle[j] == 1 && p[3].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[7].getcircle[j] == 1 && p[7].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (i = 2; i <= 8; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 7)
	{
		clean_xieshu1(judge_color);
	}
}
void clean_xieheng1(int clean_color)    //清除第二行和两条斜对角线
{
	for (i = 4; i <= 6; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[1].getcolor[j] == clean_color)
		{
			p[1].getcolor[j] = 0;
			p[1].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcolor[j] == clean_color)
		{
			p[9].getcolor[j] = 0;
			p[9].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[3].getcolor[j] == clean_color)
		{
			p[3].getcolor[j] = 0;
			p[3].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[7].getcolor[j] == clean_color)
		{
			p[7].getcolor[j] = 0;
			p[7].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	score = score + 10;

	mciSendString("stop music1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music1", NULL, 0, NULL);
	mciSendString("play music1", NULL, 0, NULL); // 仅播放一次
}
void judgeclean_xieheng1(int judge_color)	//判断第二行和两条对角线是否颜色相同
{
	num = 0;
	for (j = 0; j < 3; j++)
	{
		if (p[1].getcircle[j] == 1 && p[1].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcircle[j] == 1 && p[9].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[3].getcircle[j] == 1 && p[3].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[7].getcircle[j] == 1 && p[7].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (i = 4; i <= 6; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 7)
	{
		clean_xieheng1(judge_color);
	}
}
void clean_xieshu2(int clean_color)    //清除第二列和左上到右下斜对角线
{
	for (i = 2; i <= 8; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[1].getcolor[j] == clean_color)
		{
			p[1].getcolor[j] = 0;
			p[1].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcolor[j] == clean_color)
		{
			p[9].getcolor[j] = 0;
			p[9].getcircle[j] = 0;
			MoneyPlus();
		}
	}	
	
	score = score + 7;

	mciSendString("stop music1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music1", NULL, 0, NULL);
	mciSendString("play music1", NULL, 0, NULL); // 仅播放一次
}
void judgeclean_xieshu2(int judge_color)	//判断第二列和左上到右下斜对角线颜色是否相同
{
	num = 0;
	for (j = 0; j < 3; j++)
	{
		if (p[1].getcircle[j] == 1 && p[1].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcircle[j] == 1 && p[9].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	
	for (i = 2; i <= 8; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 5)
	{
		clean_xieshu2(judge_color);
	}
}
void clean_xieshu3(int clean_color)    //清除第二列和左下到右上斜对角线
{
	for (i = 2; i <= 8; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[3].getcolor[j] == clean_color)
		{
			p[3].getcolor[j] = 0;
			p[3].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[7].getcolor[j] == clean_color)
		{
			p[7].getcolor[j] = 0;
			p[7].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	score = score + 7;

	mciSendString("stop music1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music1", NULL, 0, NULL);
	mciSendString("play music1", NULL, 0, NULL); // 仅播放一次
}
void judgeclean_xieshu3(int judge_color)	//判断第二列和左下到右上斜对角线是否相同
{
	num = 0;
	for (j = 0; j < 3; j++)
	{
		if (p[3].getcircle[j] == 1 && p[3].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[7].getcircle[j] == 1 && p[7].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (i = 2; i <= 8; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 5)
	{
		clean_xieshu3(judge_color);
	}
}
void clean_xieheng2(int clean_color)    //清除第二行和左上到右下斜对角线
{
	for (i = 4; i <= 6; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[1].getcolor[j] == clean_color)
		{
			p[1].getcolor[j] = 0;
			p[1].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcolor[j] == clean_color)
		{
			p[9].getcolor[j] = 0;
			p[9].getcircle[j] = 0;
			MoneyPlus();
		}
	}

	score = score + 7;

	mciSendString("stop music1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music1", NULL, 0, NULL);
	mciSendString("play music1", NULL, 0, NULL); // 仅播放一次
}
void judgeclean_xieheng2(int judge_color)	//判断第二行和左上到右下斜对角线颜色是否相同
{
	num = 0;
	for (j = 0; j < 3; j++)
	{
		if (p[1].getcircle[j] == 1 && p[1].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcircle[j] == 1 && p[9].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (i = 4; i <= 6; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 5)
	{
		clean_xieheng2(judge_color);
	}
}
void clean_xieheng3(int clean_color)    //清除第二行和左下到右上斜对角线
{
	for (i = 4; i <= 6; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[3].getcolor[j] == clean_color)
		{
			p[3].getcolor[j] = 0;
			p[3].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[7].getcolor[j] == clean_color)
		{
			p[7].getcolor[j] = 0;
			p[7].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	score = score + 7;

	mciSendString("stop music1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music1", NULL, 0, NULL);
	mciSendString("play music1", NULL, 0, NULL); // 仅播放一次
}
void judgeclean_xieheng3(int judge_color)	//判断第二行和左下到右上斜对角线颜色是否相同
{
	num = 0;
	for (j = 0; j < 3; j++)
	{
		if (p[3].getcircle[j] == 1 && p[3].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[7].getcircle[j] == 1 && p[7].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (i = 4; i <= 6; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 5)
	{
		clean_xieheng3(judge_color);
	}
}
void CleanDouble_type_one(int clean_color)	//消除第一行和第一列
{
	for (i = 1; i <= 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[7].getcolor[j] == clean_color)
		{
			p[7].getcolor[j] = 0;
			p[7].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	score = score + 6;

	mciSendString("stop music1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music1", NULL, 0, NULL);
	mciSendString("play music1", NULL, 0, NULL); // 仅播放一次

}

void CleanDouble_type_two(int clean_color)	//消除第一行和第二列
{
	for (i = 1; i <= 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[5].getcolor[j] == clean_color)
		{
			p[5].getcolor[j] = 0;
			p[5].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[8].getcolor[j] == clean_color)
		{
			p[8].getcolor[j] = 0;
			p[8].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	score = score + 6;
	mciSendString("stop music2", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music2", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music2", NULL, 0, NULL);
	mciSendString("play music2", NULL, 0, NULL); // 仅播放一次 
}
void CleanDouble_type_three(int clean_color)	//消除第一行和第三列
{
	for (i = 1; i <= 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		
		}
	}
	
	for (j = 0; j < 3; j++)
	{
		if (p[6].getcolor[j] == clean_color)
		{
			p[6].getcolor[j] = 0;
			p[6].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcolor[j] == clean_color)
		{
			p[9].getcolor[j] = 0;
			p[9].getcircle[j] = 0;
			MoneyPlus();
		}	
	}
	score = score + 6;
	mciSendString("stop music3", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music3", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music3", NULL, 0, NULL);
	mciSendString("play music3", NULL, 0, NULL); // 仅播放一次 
}

void CleanDouble_type_four(int clean_color)	//消除第二行和第一列
{
	for (i = 1; i <= 7; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}		
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[5].getcolor[j] == clean_color)
		{
			p[5].getcolor[j] = 0;
			p[5].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[6].getcolor[j] == clean_color)
		{
			p[6].getcolor[j] = 0;
			p[6].getcircle[j] = 0;
			MoneyPlus();
		}	
	}

	score = score + 6;
	mciSendString("stop music4", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music4", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music4", NULL, 0, NULL);
	mciSendString("play music4", NULL, 0, NULL); // 仅播放一次 
}

void CleanDouble_type_five(int clean_color)	//消除第二行和第二列
{
	for (i = 2; i <= 8; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}			
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[4].getcolor[j] == clean_color)
		{
			p[4].getcolor[j] = 0;
			p[4].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[6].getcolor[j] == clean_color)
		{
			p[6].getcolor[j] = 0;
			p[6].getcircle[j] = 0;
			MoneyPlus();
		}		
	}
	score = score + 6;
	mciSendString("stop music5", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music5", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music5", NULL, 0, NULL);
	mciSendString("play music5", NULL, 0, NULL); // 仅播放一次 
}

void CleanDouble_type_six(int clean_color)	//消除第二行和第三列
{
	for (i = 3; i <= 9; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}			
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[4].getcolor[j] == clean_color)
		{
			p[4].getcolor[j] = 0;
			p[4].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[5].getcolor[j] == clean_color)
		{
			p[5].getcolor[j] = 0;
			p[5].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	score = score + 6;
	mciSendString("stop music6", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music6", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music6", NULL, 0, NULL);
	mciSendString("play music6", NULL, 0, NULL); // 仅播放一次 
}

void CleanDouble_type_seven(int clean_color)	//消除第三行和第一列
{
	for (i = 1; i <= 7; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[8].getcolor[j] == clean_color)
		{
			p[8].getcolor[j] = 0;
			p[8].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcolor[j] == clean_color)
		{
			p[9].getcolor[j] = 0;
			p[9].getcircle[j] = 0;
			MoneyPlus();
		}

	}

	score = score + 6;
	mciSendString("stop music7", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music7", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music7", NULL, 0, NULL);
	mciSendString("play music7", NULL, 0, NULL); // 仅播放一次 
}
void CleanDouble_type_eight(int clean_color)	//消除第三行和第二列
{
	for (i = 7; i <= 9; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}			
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[2].getcolor[j] == clean_color)
		{
			p[2].getcolor[j] = 0;
			p[2].getcircle[j] = 0;
			MoneyPlus();
		}	
	}
	for (j = 0; j < 3; j++)
	{
		if (p[5].getcolor[j] == clean_color)
		{
			p[5].getcolor[j] = 0;
			p[5].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	score = score + 6;
	mciSendString("stop music8", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music8", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music8", NULL, 0, NULL);
	mciSendString("play music8", NULL, 0, NULL); // 仅播放一次 
}
void CleanDouble_type_nine(int clean_color)	//消除第三行和第三列
{
	for (i = 7; i <= 9; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[3].getcolor[j] == clean_color)
		{
			p[3].getcolor[j] = 0;
			p[3].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[6].getcolor[j] == clean_color)
		{
			p[6].getcolor[j] = 0;
			p[6].getcircle[j] = 0;
			MoneyPlus();
		}
	}
	score = score + 6;
	mciSendString("stop music9", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music9", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias music9", NULL, 0, NULL);
	mciSendString("play music9", NULL, 0, NULL); // 仅播放一次 
}
void judgeclean_type_one(int judge_color)	//判断第一行第一列颜色是否相同
{
	num = 0;
	for (i = 1; i <= 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[7].getcircle[j] == 1 && p[7].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	if (num == 5)
	{
		CleanDouble_type_one(judge_color);
	}
}



void judgeclean_type_two(int judge_color)	//判断第一行第二列颜色是否相同

{
	num = 0;
	for (i = 1; i <= 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[5].getcircle[j] == 1 && p[5].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[8].getcircle[j] == 1 && p[8].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	if (num == 5)
	{
		CleanDouble_type_two(judge_color);
	}
}


void judgeclean_type_three(int judge_color)	//判断第一行第三列颜色是否相同

{
	num = 0;
	for (i = 1; i <= 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[6].getcircle[j] == 1 && p[6].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcircle[j] == 1 && p[9].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	if (num == 5)
	{
		CleanDouble_type_three(judge_color);
	}
}

void judgeclean_type_four(int judge_color)	//判断第二行第一列颜色是否相同

{
	num = 0;
	for (i = 1; i <= 7; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[5].getcircle[j] == 1 && p[5].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[6].getcircle[j] == 1 && p[6].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	if (num == 5)
	{
		CleanDouble_type_four(judge_color);
	}
}

void judgeclean_type_five(int judge_color)	//判断第二行第二列颜色是否相同

{
	num = 0;
	for (i = 2; i <= 8; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[4].getcircle[j] == 1 && p[4].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[6].getcircle[j] == 1 && p[6].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	if (num == 5)
	{
		CleanDouble_type_five(judge_color);
	}
}

void judgeclean_type_six(int judge_color)	//判断第二行第三列颜色是否相同

{
	num = 0;
	for (i = 3; i <= 9; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[4].getcircle[j] == 1 && p[4].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[5].getcircle[j] == 1 && p[5].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	if (num == 5)
	{
		CleanDouble_type_six(judge_color);
	}
}

void judgeclean_type_seven(int judge_color)	//判断第三行第一列颜色是否相同

{
	num = 0;
	for (i = 1; i <= 7; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[8].getcircle[j] == 1 && p[8].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[9].getcircle[j] == 1 && p[9].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	if (num == 5)
	{
		CleanDouble_type_seven(judge_color);
	}
}

void judgeclean_type_eight(int judge_color)	//判断第三行第二列颜色是否相同
{
	num = 0;
	for (i = 7; i <= 9; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[2].getcircle[j] == 1 && p[2].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[5].getcircle[j] == 1 && p[5].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	if (num == 5)
	{
		CleanDouble_type_eight(judge_color);
	}
}

void judgeclean_type_nine(int judge_color)	//判断第三行第三列颜色是否相同

{
	num = 0;
	for (i = 7; i <= 9; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[3].getcircle[j] == 1 && p[3].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	for (j = 0; j < 3; j++)
	{
		if (p[6].getcircle[j] == 1 && p[6].getcolor[j] == judge_color)
		{
			num++;
			break;
		}
	}
	if (num == 5)
	{
		CleanDouble_type_nine(judge_color);
	}
}



void Clear_FullPoint()	//消除同一点上三个圈颜色相同的环
{
	for (i = 1; i <= 9; i++)
	{
		if ((p[i].getcircle[0] == 1 && p[i].getcircle[1] == 1 && p[i].getcircle[2] == 1) && (p[i].getcolor[0] == 1 && p[i].getcolor[1] == 1 && p[i].getcolor[2] == 1))//同一点三个圆环颜色为红色
		{
			for (j = 0; j < 3; j++)
			{
				p[i].getcircle[j] = 0;
				p[i].getcolor[j] = 0;
				MoneyPlus();
			}		
			score = score + 6;
			mciSendString("stop xcmusic1", NULL, 0, NULL);   // 先把前面一次的音乐停止
			mciSendString("close xcmusic1", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open xtxiaochu.mp3 alias xcmusic1", NULL, 0, NULL);
			mciSendString("play xcmusic1", NULL, 0, NULL); // 仅播放一次
		}

		if ((p[i].getcircle[0] == 1 && p[i].getcircle[1] == 1 && p[i].getcircle[2] == 1) && (p[i].getcolor[0] == 2 && p[i].getcolor[1] == 2 && p[i].getcolor[2] == 2) )//同一点三个圆环颜色为蓝色
		{
			for (j = 0; j < 3; j++)
			{
				p[i].getcircle[j] = 0;
				p[i].getcolor[j] = 0;
				MoneyPlus();
			}			
			score = score + 6;
			mciSendString("stop xcmusic1", NULL, 0, NULL);   // 先把前面一次的音乐停止
			mciSendString("close xcmusic1", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open xtxiaochu.mp3 alias xcmusic1", NULL, 0, NULL);
			mciSendString("play xcmusic1", NULL, 0, NULL); // 仅播放一次
		}

		if ((p[i].getcircle[0] == 1 && p[i].getcircle[1] == 1 && p[i].getcircle[2] == 1) && (p[i].getcolor[0] == 3 && p[i].getcolor[1] == 3 && p[i].getcolor[2] == 3))//同一点三个圆环颜色为黄色
		{
			for (j = 0; j < 3; j++)
			{
				p[i].getcircle[j] = 0;
				p[i].getcolor[j] = 0;
				MoneyPlus();
			}		
			score = score + 6;
			mciSendString("stop xcmusic1", NULL, 0, NULL);   // 先把前面一次的音乐停止
			mciSendString("close xcmusic1", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open xtxiaochu.mp3 alias xcmusic1", NULL, 0, NULL);
			mciSendString("play xcmusic1", NULL, 0, NULL); // 仅播放一次
		}

		if ((p[i].getcircle[0] == 1 && p[i].getcircle[1] == 1 && p[i].getcircle[2] == 1) && (p[i].getcolor[0] == 4 && p[i].getcolor[1] == 4 && p[i].getcolor[2] == 4) )//同一点三个圆环颜色为绿色
		{
			for (j = 0; j < 3; j++)
			{
				p[i].getcircle[j] = 0;
				p[i].getcolor[j] = 0;
				MoneyPlus();
			}			
			score = score + 6;
			mciSendString("stop xcmusic1", NULL, 0, NULL);   // 先把前面一次的音乐停止
			mciSendString("close xcmusic1", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open xtxiaochu.mp3 alias xcmusic1", NULL, 0, NULL);
			mciSendString("play xcmusic1", NULL, 0, NULL); // 仅播放一次
		}

	}
}

void CleanHeng_1(int clean_color)	//消除第一行
{
	for (i = 1; i <= 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	score = score + 3;
	mciSendString("stop xcmusic1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias xcmusic1", NULL, 0, NULL);
	mciSendString("play xcmusic1", NULL, 0, NULL); // 仅播放一次
}
void CleanHeng_2(int clean_color)	//消除第二行
{
	for (i = 4; i <= 6; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	score = score + 3;
	mciSendString("stop xcmusic2", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic2", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias xcmusic2", NULL, 0, NULL);
	mciSendString("play xcmusic2", NULL, 0, NULL); // 仅播放一次
}
void CleanHeng_3(int clean_color)	//消除第三行
{
	for (i = 7; i <= 9; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
			
		}
	}
	score = score + 3;
	mciSendString("stop xcmusic3", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic3", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias xcmusic3", NULL, 0, NULL);
	mciSendString("play xcmusic3", NULL, 0, NULL); // 仅播放一次
}
void JudgeHeng_1(int judge_color)	//判断第一行三点是否有颜色相同的环
{
	num = 0;
	for (i = 1; i <= 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 3)
	{
		CleanHeng_1(judge_color);
	}
}


void JudgeHeng_2(int judge_color)	//判断第二行三点是否有颜色相同的环
{
	num = 0;
	for (i = 4; i <= 6; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 3)
	{
		CleanHeng_2(judge_color);
	}
}

void JudgeHeng_3(int judge_color)	//判断第三行三点是否有颜色相同的环
{
	num = 0;
	for (i = 7; i <= 9; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 3)
	{
		CleanHeng_3(judge_color);
	}
}


void CleanShu_1(int clean_color)	//消除第一列
{
	for (i = 1; i <= 7; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	score = score + 3;
	mciSendString("stop xcmusic4", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic4", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias xcmusic4", NULL, 0, NULL);
	mciSendString("play xcmusic4", NULL, 0, NULL); // 仅播放一次
}
void CleanShu_2(int clean_color)	//消除第二列
{
	for (i = 2; i <= 8; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	score = score + 3;
	mciSendString("stop xcmusic5", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic5", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias xcmusic5", NULL, 0, NULL);
	mciSendString("play xcmusic5", NULL, 0, NULL); // 仅播放一次
}
void CleanShu_3(int clean_color)	//消除第三列
{
	for (i = 3; i <= 9; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	score = score + 3;
	mciSendString("stop xcmusic6", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic6", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias xcmusic6", NULL, 0, NULL);
	mciSendString("play xcmusic6", NULL, 0, NULL); // 仅播放一次
}
void JudgeShu_1(int judge_color)	//判断第一列三点是否有颜色相同的环
{
	num = 0;
	for (i = 1; i <= 7; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}

	if (num == 3)
	{
		CleanShu_1(judge_color);
	}
}

void JudgeShu_2(int judge_color)	//判断第二列三点是否有颜色相同的环
{
	num = 0;
	for (i = 2; i <= 8; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}

	if (num == 3)
	{
		CleanShu_2(judge_color);
	}
}

void JudgeShu_3(int judge_color)	//判断第三列三点是否有颜色相同的环
{
	num = 0;
	for (i = 3; i <= 9; i = i + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}

	if (num == 3)
	{
		CleanShu_3(judge_color);
	}
}

void CleanXie_left(int clean_color)	//消除左上到右下颜色相同的环
{
	for (i = 1; i <= 9; i = i + 4)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	score = score + 4;
	mciSendString("stop xcmusic7", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic7", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias xcmusic7", NULL, 0, NULL);
	mciSendString("play xcmusic7", NULL, 0, NULL); // 仅播放一次
}
void CleanXie_right(int clean_color)	//消除左下到右上颜色相同的环

{
	for (i = 3; i <= 7; i = i + 2)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcolor[j] == clean_color)
			{
				p[i].getcolor[j] = 0;
				p[i].getcircle[j] = 0;
				MoneyPlus();
			}
		}
	}
	score = score + 4;
	mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open xiaochu.mp3 alias xcmusic8", NULL, 0, NULL);
	mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
}
void JudgeXie_left(int judge_color)		//判断左上到右下是否有颜色相同的环
{
	num = 0;
	for (i = 1; i <= 9; i = i + 4)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}

	if (num == 3)
	{
		CleanXie_left(judge_color);
	}
}
void JudgeXie_right(int judge_color)	//判断左下到右上是否有颜色相同的环
{
	num = 0;
	for (i = 3; i <= 7; i = i + 2)
	{
		for (j = 0; j < 3; j++)
		{
			if (p[i].getcircle[j] == 1 && p[i].getcolor[j] == judge_color)
			{
				num++;
				break;
			}
		}
	}
	if (num == 3)
	{
		CleanXie_right(judge_color);
	}
}



void starup()	//游戏初始化
{
	high = 390;
	wedith = 550;
	initgraph(high, wedith);		//画布大小
	gap = 95;		//点之间的间隔
	score = 0;
	money = 0;
	GamePrase = 0;
	a = 0;
	position_x = 50;
	position_y = 490;
	jnnum= 0;
	jnget = 0;
	k = 1;
	n = 0;
	// 定义 IMAGE 对象
	loadimage(&img_bk, _T("封面.jpg.jpg"));	// 读取图片到 img 对象中
	loadimage(&img_victory, _T("victory.jpg"));

	p[1].x = 100; p[2].x = 100 + gap; p[3].x = 100 + gap * 2;		//九个点的横坐标
	p[4].x = 100; p[5].x = 100 + gap; p[6].x = 100 + gap * 2;
	p[7].x = 100; p[8].x = 100 + gap; p[9].x = 100 + gap * 2;

	p[1].y = 180; p[4].y = 180 + gap; p[7].y = 180 + gap * 2;		//九个点的纵坐标		
	p[2].y = 180; p[5].y = 180 + gap; p[8].y = 180 + gap * 2;
	p[3].y = 180; p[6].y = 180 + gap; p[9].y = 180 + gap * 2;

	for (i = 1; i <= 3; i++)		//画出三个圆并定位
	{
		c[i].x = p[i].x;
		c[i].y = p[9].y + 80;
		c[i].get = 0;
		c[i].exist = 0;
		c[i].color[0] = rand() % 4 + 1;
		c[i].color[1] = rand() % 4 + 1;
		c[i].color[2] = rand() % 4 + 1;	
		
	
			for (j = 0; j < 3; j++)          //判断同时生成的三个图形是否颜色都一样，如果是则将第二个图形的相同颜色改变
			{
				if (c[1].color[0] == c[2].color[j])
				{
					for (int a = 0; a < 3;a++)
					{
						if (c[2].color[j] == c[3].color[a])
						{
							c[2].color[j] = rand() % 4 + 1;							
						}		
					}
				}
			
				if (c[1].color[1] == c[2].color[j])
				{
					for (int a = 0; a < 3;a++)
					{
						if (c[2].color[j] == c[3].color[a])
						{
							c[2].color[j] = rand() % 4 + 1;						
						}						
					}
				}				
				if (c[1].color[2] == c[2].color[j])
				{
					for (int a = 0; a < 3; a++)
					{
						if (c[2].color[j] == c[3].color[a])
						{
							c[2].color[j] = rand() % 4 + 1;
							
						}						
					}
				}
				
			}
		}

	
		
	for (i = 1; i <= 9; i++)//给点上的三个环全部初始化
	{
		for (j = 0; j < 3; j++)
		{
			p[i].getcircle[j] = 0;
			p[i].getbirth[j] = 0;
			p[i].getcolor[j] = 0;
		}
	}

	//预设颜色
	Defcolor[0] = RGB(178, 34, 34);		//RED
	Defcolor[1] = RGB(25, 147, 233);	//BLUE
	Defcolor[2] = RGB(255, 255, 36);	//YELLOW
	Defcolor[3] = RGB(76, 214, 40);		//GREEN

	//判断环1是否存在并随机生成三个环是否存在
	if (c[1].exist == 0)
	{
		for (i = 0; i < 3; i++)
		{
			c[1].type[i] = rand() % 2;
			c[1].birth[i] = rand() % 2;
		}
		c[1].exist = 1;
	}

	//判断环2是否存在并随机生成三个环是否存在
	if (c[2].exist == 0)
	{
		for (i = 0; i < 3; i++)
		{
			c[2].type[i] = rand() % 2;
			c[2].birth[i] = rand() % 2;
		}
		c[2].exist = 1;
	}

	//判断环3是否存在并随机生成三个环是否存在
	if (c[3].exist == 0)
	{
		
		for (i = 0; i < 3; i++)
		{
			c[3].type[i] = rand() % 2;
			c[3].birth[i] = rand() % 2;
		}
		c[3].exist = 1;
	}
	//避免出现三个环都没有和三个环都有的情况	
}
void Draw_ring(int c, Circle New_c[3])
{
	
	for (i = 1; i <= 3; i++)

	{
		
		
		if (New_c[i].type[0] == 1 && New_c[i].color[0] == c)
		{
			if (New_c[i].birth[0] == 0)
				circle(New_c[i].x, New_c[i].y, 10);
			else if
				(New_c[i].birth [0]== 1)
				rectangle(New_c[i].x - 8, New_c[i].y - 8, New_c[i].x + 8, New_c[i].y + 8);
		}
		if (New_c[i].type[1] == 1 && New_c[i].color[1] == c)
		{
			
			if (New_c[i].birth[1] == 0)
				circle(New_c[i].x, New_c[i].y, 17);
			else if
				(New_c[i].birth[1] == 1)
				rectangle(New_c[i].x - 14, New_c[i].y - 14, New_c[i].x + 14, New_c[i].y + 14);
		}
		if (New_c[i].type[2] == 1 && New_c[i].color[2] == c)
		{
			
			if (New_c[i].birth[2] == 0)
				circle(New_c[i].x, New_c[i].y, 25);
			else if
				(New_c[i].birth[2] == 1)
				rectangle(New_c[i].x - 24, New_c[i].y - 24, New_c[i].x + 24, New_c[i].y + 24);
		}
		srand((unsigned)time(NULL));
	}
}
void Draw_pointring(int c, point New_p[3])
{
	for (i = 1; i <= 9; i++)
	{
		for (int j = 1; j <=3; j++)
		{
			if (New_p[i].getcircle[0] == 1 && New_p[i].getcolor[0] == c)
			{
				if (New_p[i].getbirth[0] == 0)
					circle(New_p[i].x, New_p[i].y, 10);
				else if (New_p[i].getbirth[0] == 1)
					rectangle(New_p[i].x-8, New_p[i].y - 8, New_p[i].x + 8, New_p[i].y + 8);
			}
			if (New_p[i].getcircle[1] == 1 && New_p[i].getcolor[1] == c)
			{
				if (New_p[i].getbirth[1] == 0)
					circle(New_p[i].x, New_p[i].y, 17);
				else if (New_p[i].getbirth[1] == 1)
					rectangle(New_p[i].x - 14, New_p[i].y - 14, New_p[i].x + 14, New_p[i].y + 14);
			}

			if (New_p[i].getcircle[2] == 1 && New_p[i].getcolor[2] == c)
			{
				if (New_p[i].getbirth[2] == 0)
					circle(New_p[i].x, New_p[i].y, 25);
				else if(New_p[i].getbirth[2] == 1)
					rectangle(New_p[i].x - 24, New_p[i].y - 24, New_p[i].x + 24, New_p[i].y + 24);
			}	
		}
		
	}
}


void show()
{

	BeginBatchDraw();	//这个函数用于开始批量绘图。
	//执行后，任何绘图操作都将暂时不输出到屏幕上
	//直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(31, 78, 121));//设置背景颜色
	solidrectangle(0, 0, high, wedith);//画背景
	
	loadimage(&img_beijing, _T("bk.png"));	// 读取图片到 img 对象中
	putimage(0, 0, &img_beijing);
	loadimage(&img_tools, _T("jn.png"));	// 读取图片到 img 对象中
	putimage(position_x, position_y, &img_tools);
	setwritemode(R2_MERGEPEN);//设置画图方式为OR

	for (j = 1; j <= 3; j++)
	{
		if (c[j].exist == 0)
		{
			for (i = 0; i < 3; i++)
			{
				c[j].type[i] = rand() % 2;
				c[j].birth[i] = rand() % 2;
				c[j].color[i] = rand() % 4 + 1;
			}
			c[j].exist = 1;
		}
	}
	for (i = 1; i <= 3; i++)
	{
		if (c[i].type[0] == 0 && c[i].type[1] == 0 && c[i].type[2] == 0)
			c[i].type[0] = 1;
		if (c[i].type[0] == 1 && c[i].type[1] == 1)
			c[i].type[2] = 0;
	}

	//画出三个圆环
	
	setlinestyle(PS_SOLID, 5);//线条颜色为5
	setlinecolor(Defcolor[0]);//环的颜色为红
	Draw_ring(1, c);
	Draw_pointring(1, p);
	setlinecolor(Defcolor[1]);//环的颜色为蓝
	Draw_ring(2, c);
	Draw_pointring(2, p);
	setlinecolor(Defcolor[2]);//环的颜色为黄色
	Draw_ring(3, c);
	Draw_pointring(3, p);
	setlinecolor(Defcolor[3]);//环的颜色为绿色
	Draw_ring(4, c);
	Draw_pointring(4, p);
	
	setwritemode(R2_COPYPEN);


	//画九个点
	setcolor(WHITE);
	setfillcolor(WHITE);
	for (x = p[1].x; x <= p[3].x; x += gap)
		fillcircle(x, p[1].y, 1);//第一排的点
	for (x = p[4].x; x <= p[6].x; x += gap)
		fillcircle(x, p[4].y, 1);//第二排的点
	for (x = p[7].x; x <= p[9].x; x += gap)
		fillcircle(x, p[7].y, 1);//第三排的点

	

	settextstyle(40, 20, _T("华文隶书"));
	outtextxy(80, 40, "分数");
	char s[5];
	sprintf_s(s, "%d", score);
	outtextxy(101, 100, s);

	settextstyle(40, 20, _T("华文隶书"));
	outtextxy(103, 510, "*");
	char s0[5];
	sprintf_s(s0,"%d", jnnum);
	outtextxy(126, 499, s0);

	settextstyle(40, 20, _T("华文隶书"));
	outtextxy(220, 40, "金钱");
	char s1[5];
	sprintf_s(s1, "%d", money);
	outtextxy(250, 100, s1);

	settextstyle(25, 10, _T("华文隶书"));
	outtextxy(185, 500, "按r键重新游戏");

	FlushBatchDraw();
	// 执行未完成的绘制任务

}


void withoutinput()
{
	//三个环都放出去后重新刷新
	for (i = 1; i <= 3; i++)
	{
		if (c[i].exist == 2)
		{
			c[i].exist = 0;
			out(i);
		}
	}
	if (c[1].x == -100 && c[2].x == -100 && c[3].x == -100)
	{
		back1();
		back2();
		back3();
		mciSendString("stop cxmusic", NULL, 0, NULL);   // 先把前面一次的音乐停止
		mciSendString("close cxmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
		mciSendString("open chuxian.mp3 alias cxmusic", NULL, 0, NULL);
		mciSendString("play cxmusic", NULL, 0, NULL); // 仅播放一次
	}
	for (color_size = 1; color_size <= 4; color_size++)
	{
		judgeclean_xieshuheng1(color_size);
		judgeclean_xieshuheng2(color_size);
		judgeclean_xieshuheng3(color_size);
		judgeclean_xieshuheng4(color_size);
		judgeclean_xieshuheng5(color_size);
		judgeclean_xieshu1(color_size);
		judgeclean_xieheng1(color_size);
		judgeclean_xieshu2(color_size);
		judgeclean_xieshu3(color_size);
		judgeclean_xieheng2(color_size);
		judgeclean_xieheng3(color_size);
		judgeclean_type_one(color_size);
		judgeclean_type_two(color_size);
		judgeclean_type_three(color_size);
		judgeclean_type_four(color_size);
		judgeclean_type_five(color_size);
		judgeclean_type_six(color_size);
		judgeclean_type_seven(color_size);
		judgeclean_type_eight(color_size);
		judgeclean_type_nine(color_size);
		Clear_FullPoint();
		JudgeHeng_1(color_size);
		JudgeHeng_2(color_size);
		JudgeHeng_3(color_size);
		JudgeShu_1(color_size);
		JudgeShu_2(color_size);
		JudgeShu_3(color_size);
		JudgeXie_left(color_size);
		JudgeXie_right(color_size);

	}
}

void withinput()
{
	m = GetMouseMsg();
	size = 53;
	if (m.uMsg == WM_LBUTTONDOWN && m.x <= 314 && m.x >= 266 && m.y >= 426 && m.y <= 474)
	{
		faulse = 0;
		c[3].get = 1;	
	}
	if (m.uMsg == WM_LBUTTONDOWN && m.x <= 124 && m.x >= 76 && m.y >= 426 && m.y <= 474)
	{
		faulse = 0;
		c[1].get = 1;		
	}
	if (m.uMsg == WM_LBUTTONDOWN && m.x <= 219 && m.x >= 171 && m.y >= 426 && m.y <= 474)
	{
		faulse = 0;
		c[2].get = 1;		
	}

	if (m.uMsg == WM_LBUTTONDOWN && m.x <= 124 && m.x >= 60 && m.y >= 489 && m.y <= 550)
	{
		
		jnget = 1;
	}
	if (m.uMsg == WM_LBUTTONDOWN && m.x <= 124 && m.x >= 60 && m.y >= 489 && m.y <= 550)
	{

		jnget = 1;
	}
	

	if (jnget == 1)
	{
		position_x = m.x;
		position_y = m.y;
	  for (i = 1; i <= 9; i++)
	  {
		
		  
			  if (m.uMsg == WM_LBUTTONUP && m.x >= p[i].x - size && m.x <= p[i].x + size && m.y >= p[i].y - size && m.y <= p[i].y + size)
			  {
				  if (jnnum > 0)
				  {
					  
					  for (j = 0; j < 3; j++)
					  {
						  p[i].getcircle[j] = 0;
						  p[i].getcolor[j] = 0;
						  mciSendString("stop xcmusic1", NULL, 0, NULL);   // 先把前面一次的音乐停止
						  mciSendString("close xcmusic1", NULL, 0, NULL); // 先把前面一次的音乐关闭
						  mciSendString("open xiaochu.mp3 alias xcmusic1", NULL, 0, NULL);
						  mciSendString("play xcmusic1", NULL, 0, NULL); // 仅播放一次
					  }
					  jnnum = jnnum - 1;
					 
					  back4();
					  jnget = 0;
				  }
			  }
			  if (m.uMsg == WM_LBUTTONUP && m.x <= 330 && m.x >= 180 && m.y >= 10 && m.y <= 160)
			  {
				  if (money >= q)
				  {
					  mciSendString("stop xcmusic1", NULL, 0, NULL);   // 先把前面一次的音乐停止
					  mciSendString("close xcmusic1", NULL, 0, NULL); // 先把前面一次的音乐关闭
					  mciSendString("open yudi2.mp3 alias xcmusic1", NULL, 0, NULL);
					  mciSendString("play xcmusic1", NULL, 0, NULL); // 仅播放一次
					  n = money / q;
					  money = money - q*n;
					  jnnum = jnnum + n;				
					  back4();
					  jnget = 0;
				  }
			  }
			  else if (m.uMsg == WM_LBUTTONUP && (m.x <= p[1].x - size || m.x >= p[3].x + size || m.y <= p[1].y - size || m.y >= p[7].y + size))
			  {
				  back4();	//游戏边界外松开鼠标圆环1回到原位
				  jnget = 0;

			  }
			  else if (m.uMsg == WM_LBUTTONUP && m.x >= p[i].x - size && m.x <= p[i].x + size && m.y >= p[i].y - size && m.y <= p[i].y + size)
			  {
				  back4();	//游戏边界外松开鼠标圆环1回到原位
				  jnget = 0;
			  }
	  }
	}

	if (c[1].get == 1)	//当鼠标按下后圆环跟着鼠标移动
	{
		c[1].x = m.x;
		c[1].y = m.y;
		for (i = 1; i <= 9; i++)
		{
			if (m.uMsg == WM_LBUTTONUP && m.x >= p[i].x - size && m.x <= p[i].x + size && m.y >= p[i].y - size && m.y <= p[i].y + size)
			{
				for (j = 0; j < 3; j++)
				{
					if (c[1].type[j] == 1 && p[i].getcircle[j] == 1)
						z = 1;
				}
				for (j = 0; j < 3; j++)
				{
					if (c[1].type[j] == 1 && p[i].getcircle[j] == 0 && z == 0)
					{
						if (j == 0 && c[1].birth[j] == 1 && p[i].getcircle[j + 1] == 0 && p[i].getcircle[j + 2] == 0 && c[1].type[j + 1] == 1 && c[1].birth[j + 1] == 0 && c[1].type[j + 2] == 0)
						{
							money = money + 1;//系统白给的小铜钱
							faulse = 1;
							mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
							mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
							mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
							mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
						}
						if (j == 0 && c[1].birth[j] == 1 && p[i].getcircle[j + 1] == 0 && p[i].getcircle[j + 2] == 0 && c[1].type[j + 2] == 1 && c[1].birth[j + 2] == 0 && c[1].type[j + 1] == 0)
						{money = money +2;//系统白给的大铜钱
						faulse = 1;
						mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
						mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
						mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
						mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
						}
						p[i].getcircle[j] = 1;
						p[i].getcolor[j] = c[1].color[j];
						p[i].getbirth[j]= c[1].birth[j];
					}
					
				}
				if (z == 0)
				{
					stay1();	//在游戏边界内松开鼠标圆环1定位到临近点坐标
					if (faulse == 0&&p[i].getcircle[0] == 1 && p[i].getcircle[1] == 1 && p[i].getcircle[2] == 0 && p[i].getbirth[0] == 1 && p[i].getbirth[1] == 0)
					{
						money = money + 3;	
						mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
						mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
						mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
						mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
					}
					if (faulse == 0 && p[i].getcircle[0] == 1 && p[i].getcircle[ 1] == 0 && p[i].getcircle[2] == 1 && p[i].getbirth[0] == 1 && p[i].getbirth[2] == 0)
					{
						money = money + 5;
						mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
						mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
						mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
						mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
					}

					c[1].get = 0;
					c[1].exist = 2;//存在过但是移走了
				}
				else
				{
					back1();
					c[1].get = 0;
					z = 0;
					mciSendString("stop fhmusic1", NULL, 0, NULL);   // 先把前面一次的音乐停止
					mciSendString("close fhmusic1", NULL, 0, NULL); // 先把前面一次的音乐关闭
					mciSendString("open fanhui.mp3 alias fhmusic1", NULL, 0, NULL);
					mciSendString("play fhmusic1", NULL, 0, NULL); // 仅播放一次
				}
			}
			else if (m.uMsg == WM_LBUTTONUP && (m.x <= p[1].x - size || m.x >= p[3].x + size || m.y <= p[1].y - size || m.y >= p[7].y + size))
			{
				back1();	//游戏边界外松开鼠标圆环1回到原位
				c[1].get = 0;

			}
			else if (m.uMsg == WM_LBUTTONUP && m.x >= p[i].x - size && m.x <= p[i].x + size && m.y >= p[i].y - size && m.y <= p[i].y + size)
			{
				back1();
				c[1].get = 0;
			}
			
		}
	}
	if (c[2].get == 1)//当鼠标按下后圆环2跟着鼠标移动
	{
		c[2].x = m.x;
		c[2].y = m.y;
		for (i = 1; i <= 9; i++)
		{
			if (m.uMsg == WM_LBUTTONUP && m.x >= p[i].x - size && m.x <= p[i].x + size && m.y >= p[i].y - size && m.y <= p[i].y + size)
			{
				for (j = 0; j < 3; j++)
				{
					if (c[2].type[j] == 1 && p[i].getcircle[j] == 1)
						z = 1;
				}
				for (j = 0; j < 3; j++)
				{
					if (c[2].type[j] == 1 && p[i].getcircle[j] == 0 && z == 0)
					{
						if (j == 0 && c[2].birth[j] == 1 && p[i].getcircle[j + 1] == 0 && p[i].getcircle[j + 2] == 0 && c[2].type[j + 1] == 1 && c[2].birth[j + 1] == 0 && c[2].type[j + 2] == 0)
						{
							money = money + 1;//系统白给的小铜钱
						    faulse = 1;
						mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
						mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
						mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
						mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
						}
						if (j == 0 && c[2].birth[j] == 1 && p[i].getcircle[j + 1] == 0 && p[i].getcircle[j + 2] == 0 && c[2].type[j + 2] == 1 && c[2].birth[j + 2] == 0 && c[2].type[j + 1] == 0)
						{
							money = money + 2;//系统白给的大铜钱
							faulse = 1;
							mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
							mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
							mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
							mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
						}
						p[i].getcircle[j] = 1;
						p[i].getcolor[j] = c[2].color[j];
						p[i].getbirth[j] = c[2].birth[j];
					}
					
				}
				if (z == 0)
				{
					stay2();//在游戏边界内松开鼠标圆环2定位到临近点坐标
					if (faulse == 0 && p[i].getcircle[0] == 1 && p[i].getcircle[1] == 1 && p[i].getcircle[2] == 0 && p[i].getbirth[0] == 1 && p[i].getbirth[1] == 0)
					{
						money = money + 3;
						mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
						mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
						mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
						mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
					}
					if (faulse == 0 && p[i].getcircle[0] == 1 && p[i].getcircle[1] == 0 && p[i].getcircle[2] == 1 && p[i].getbirth[0] == 1 && p[i].getbirth[2] == 0)
					{
						money = money + 5;
						mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
						mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
						mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
						mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
					}
					c[2].get = 0;
					c[2].exist = 2;//存在过但是移走了
				}
				else
				{
					back2();
					c[2].get = 0;
					z = 0;
					mciSendString("stop fhmusic2", NULL, 0, NULL);   // 先把前面一次的音乐停止
					mciSendString("close fhmusic2", NULL, 0, NULL); // 先把前面一次的音乐关闭
					mciSendString("open fanhui.mp3 alias fhmusic2", NULL, 0, NULL);
					mciSendString("play fhmusic2", NULL, 0, NULL); // 仅播放一次
				}
			}
			else if (m.uMsg == WM_LBUTTONUP && (m.x <= p[1].x - size || m.x >= p[3].x + size || m.y <= p[1].y - size || m.y >= p[7].y + size))
			{
				back2();	//游戏边界外松开鼠标圆环2回到原位
				c[2].get = 0;
			}
			else if (m.uMsg == WM_LBUTTONUP && m.x >= p[i].x - size && m.x <= p[i].x + size && m.y >= p[i].y - size && m.y <= p[i].y + size)
			{
				back2();
				c[2].get = 0;
			}
		}
	}
	if (c[3].get == 1)//当鼠标按下后圆环3跟着鼠标移动
	{
		c[3].x = m.x;
		c[3].y = m.y;
		for (i = 1; i <= 9; i++)
		{
			if (m.uMsg == WM_LBUTTONUP && m.x >= p[i].x - size && m.x <= p[i].x + size && m.y >= p[i].y - size && m.y <= p[i].y + size)//size/2会使得判断范围更好可是同时也会使得判断back失效
			{
				for (j = 0; j < 3; j++)
				{
					if (c[3].type[j] == 1 && p[i].getcircle[j] == 1)
						z = 1;
				}
				for (j = 0; j < 3; j++)
				{
					if (c[3].type[j] == 1 && p[i].getcircle[j] == 0 && z == 0)
					{
						if (j == 0 && c[3].birth[j] == 1 && p[i].getcircle[j + 1] == 0 && p[i].getcircle[j + 2] == 0 && c[3].type[j + 1] == 1 && c[3].birth[j + 1] == 0 && c[3].type[j + 2] == 0)
						{
							money = money + 1;//系统白给的小铜钱
							faulse = 1;
							mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
							mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
							mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
							mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
						}
						if (j == 0 && c[3].birth[j] == 1 && p[i].getcircle[j + 1] == 0 && p[i].getcircle[j + 2] == 0 && c[3].type[j + 2] == 1 && c[3].birth[j + 2] == 0 && c[3].type[j + 1] == 0)
						{
							money = money + 2;//系统白给的大铜钱
							faulse = 1;
							mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
							mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
							mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
							mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
						}
						p[i].getcircle[j] = 1;
						p[i].getcolor[j] = c[3].color[j];
						p[i].getbirth[j] = c[3].birth[j];
						
					}
					
				}
				if (z == 0)
				{
					stay3();	//在游戏边界内松开鼠标圆环3定位到临近点坐标
					if (faulse == 0 && p[i].getcircle[0] == 1 && p[i].getcircle[1] == 1 && p[i].getcircle[2] == 0 && p[i].getbirth[0] == 1 && p[i].getbirth[1] == 0)
					{
						money = money + 3;
						mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
						mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
						mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
						mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次

					}
					if (faulse == 0 && p[i].getcircle[0] == 1 && p[i].getcircle[1] == 0 && p[i].getcircle[2] == 1 && p[i].getbirth[0] == 1 && p[i].getbirth[2] == 0)
					{
						money = money + 5;
						mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
						mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
						mciSendString("open money.mp3 alias xcmusic8", NULL, 0, NULL);
						mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
					}
					c[3].get = 0;
					c[3].exist = 2;//存在过但是移走了
				}
				else
				{
					back3();
					c[3].get = 0;
					z = 0;
					mciSendString("stop fhmusic3", NULL, 0, NULL);   // 先把前面一次的音乐停止
					mciSendString("close fhmusic3", NULL, 0, NULL); // 先把前面一次的音乐关闭
					mciSendString("open fanhui.mp3 alias fhmusic3", NULL, 0, NULL);
					mciSendString("play fhmusic3", NULL, 0, NULL); // 仅播放一次
				}
			}

			else if (m.uMsg == WM_LBUTTONUP && (m.x <= p[1].x - size || m.x >= p[3].x + size || m.y <= p[1].y - size || m.y >= p[7].y + size))
			{
				back3();	//游戏边界外松开鼠标圆环3回到原位
				c[3].get = 0;
			}
			else if (m.uMsg == WM_LBUTTONUP && m.x >= p[i].x - size && m.x <= p[i].x + size && m.y >= p[i].y - size && m.y <= p[i].y + size)
			{
				back3();
				c[3].get = 0;
			}
		}
	}

}

void press()
{
	
	mciSendString("open renaodejieshi.mp3 alias fmmusic", NULL, 0, NULL);//背景音乐
	mciSendString("play fmmusic repeat", NULL, 0, NULL);  // 循环播放
	initgraph(high,wedith);	
	putimage(0, 0, &img_bk);	// 在坐标 (0, 0) 位置显示 IMAGE 对象
	COLORREF hui = RGB(245, 222,179);
	settextcolor(hui);
	settextstyle(25, 10, _T("华文隶书"));
	outtextxy(190, 280, "按B键开始游戏");
	outtextxy(190, 310, "按A键了解作者");

	
	if (_getch() == 'b')
	{
		ini();
		mciSendString("stop fmmusic", NULL, 0, NULL);   // 先把前面一次的音乐停止
		mciSendString("close fmmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
		mciSendString("open hongbaodazhan.mp3 alias bkmusic", NULL, 0, NULL);//背景音乐
		mciSendString("play bkmusic repeat", NULL, 0, NULL);  // 循环播放
		GamePrase = 1;
	}
	if (_getch() == 'a')
	{
		GamePrase = 3;
	}
}
void about()
{
		high = 390;
		wedith = 550;
		initgraph(high, wedith);
		BeginBatchDraw();	//这个函数用于开始批量绘图。
	//执行后，任何绘图操作都将暂时不输出到屏幕上
	//直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出
		setbkmode(TRANSPARENT);
		setfillcolor(RGB(31, 78, 121));//设置背景颜色
		solidrectangle(0, 0, high, wedith);//画背景
		loadimage(&img_beijing, _T("bk1.png"));	// 读取图片到 img 对象中
		putimage(0, 0, &img_beijing);
		setwritemode(R2_MERGEPEN);//设置画图方式为OR
		EndBatchDraw();
		settextstyle(20, 6, _T("华文隶书"));
		outtextxy(30, 240, "出品人：廖祥忠 黄心渊 ");
		outtextxy(15, 260, "Presented by Liao Xiangzhogn & Huang Xinyuan ");
		outtextxy(15, 300, "监制：张歌东 陈京炜 郑丹琪  ");
		outtextxy(15, 320, "Produced by Zhang Gedong, Chen Jingwei & Zheng Danqi ");
		outtextxy(15, 360, "指导教师：韩红雷 ");
		outtextxy(15, 380, "Academic Advised by Han Honglei ");
		outtextxy(15, 420, "策划/程序/音乐：于璐");
		outtextxy(15, 440, "Game Designed by/Programmed by/Music by  Yu Lu ");
		outtextxy(15, 480, "美工：梁雅迪");
		outtextxy(15, 500, "Art Designed by Liang Yadi ");
		COLORREF hui = RGB(245, 222, 179);
		settextcolor(hui);
		settextstyle(24, 8, _T("华文隶书"));
		outtextxy(220, 500, "按b键开始游戏");
		_getch();
		if (_getch() == 'b')
		{
			ini();
			mciSendString("stop fmmusic", NULL, 0, NULL);   // 先把前面一次的音乐停止
			mciSendString("close fmmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open hongbaodazhan.mp3 alias bkmusic", NULL, 0, NULL);//背景音乐
			mciSendString("play bkmusic repeat", NULL, 0, NULL);  // 循环播放
			GamePrase = 1;
		}
}
void restart()
{
	mciSendString("close bkmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
	starup();
	GamePrase = 0;
	loadimage(&img_bk, _T("封面.jpg.jpg"));	// 读取图片到 img 对象中
	loadimage(&img_victory, _T("victory.jpg"));
	putimage(0, 0, &img_bk);
	EndBatchDraw();
}

void gaming()
{
	
	withinput();
	withoutinput();
	show();	
	if (_kbhit())//a
	{
		key = _getch();
		if (key == 'r')
		{
			GamePrase = 2;
			key='a';
		}
	}
 }
void proces()
{
	if (a == 0)
	{
		gaming();
		if (score >= 200&&b==0)
			a = 1;
	}
	else
	{
		mciSendString("close bkmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
		mciSendString("open xinniandao.mp3 alias bkmusic", NULL, 0, NULL);//背景音乐
		mciSendString("play bkmusic repeat", NULL, 0, NULL);  // 循环播放
		high = 390;
		wedith = 550;
		initgraph(high, wedith);
		BeginBatchDraw();	//这个函数用于开始批量绘图。
	//执行后，任何绘图操作都将暂时不输出到屏幕上
	//直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出
		setbkmode(TRANSPARENT);
		setfillcolor(RGB(31, 78, 121));//设置背景颜色
		solidrectangle(0, 0, high, wedith);//画背景
		loadimage(&img_victory, _T("victory.png"));
		putimage(0, 0, &img_victory);
				setwritemode(R2_MERGEPEN);//设置画图方式为OR
		EndBatchDraw();
		settextstyle(40, 20, _T("华文隶书"));
		char s[5];
		sprintf_s(s, "%d", score);
		outtextxy(169, 230, s);
		settextstyle(45, 20, _T("华文隶书"));
		COLORREF TH1 = RGB(245, 222, 179);
		settextcolor(TH1);
		outtextxy(60, 320, "金钱");
		char s1[5];
		sprintf_s(s1, "%d", money);
		outtextxy(90, 380, s1);
		COLORREF TH= RGB(218,165, 105);
		settextcolor(TH);
		settextstyle(18, 7, _T("华文隶书"));
		outtextxy(186, 330, "按r键");
		outtextxy(176, 390, "按g键");
		if (_getch() == 'r')
		{
			ini();
			a = 0;
			GamePrase = 2;
		}
		if (_getch() == 'g')
		{		
			mciSendString("close bkmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open hongbaodazhan.mp3 alias bkmusic", NULL, 0, NULL);//背景音乐
			mciSendString("play bkmusic repeat", NULL, 0, NULL);  // 循环播放
			a = 0;
			b++;
		}
	}	
}
int main()
{
	srand((unsigned)time(NULL));
	ini();
	starup();	
	while (1)
	{
		switch (GamePrase)
		{
		case 0:press(); break;
		case 1:proces(); break;
		case 2:restart(); break;
		case 3:about(); break;
		}
	}
	EndBatchDraw();
	_getch();
	closegraph();
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
