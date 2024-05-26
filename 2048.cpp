#include <stdio.h>
#include <graphics.h> //图像库 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <mmsystem.h> 
#include <conio.h>
#pragma comment (lib,"winmm.lib") //库文件
#define WIDETH 475  //游戏界面的宽度
#define HEIGTH 475  //游戏界面的高度
#define ROW 4//数组的行数
#define COL 4//数组的列数
//用枚举对要使用的颜色进行定义，方便调用
enum Color
{
	zero = RGB(205, 193, 180),//0的颜色
	two1 = RGB(238, 228, 218),//2的颜色
	two2 = RGB(237, 224, 200),//4的颜色
	two3 = RGB(242, 177, 121),//8
	two4 = RGB(245, 149, 99),//16
	two5 = RGB(246, 124, 95),//32
	two6 = RGB(246, 94, 59),//64
	two7 = RGB(237, 206, 113),//128
	two8 = RGB(237, 204, 97),//256
	two9 = RGB(255, 0, 128),//512
	two10 = RGB(145, 0, 72),//1024
	two11 = RGB(242, 17, 158),//2048
	back = RGB(187, 173, 160)//背景颜色
};
Color colors[13] = { zero,two1,two2,two3,two4,two5,two6,two7,two8,two9,two10,two11,back};
//储存数据的数组
int map[ROW][COL];
//产生一个数 2或4 2的概率更高
int createnum()
{
	int num = 0;
	if (rand() % 8 != 0)
	{
		num = 2;
	}
	else
	{
		num = 4;
	}
	return num;
}
//在空白方格中随机添加数字
void mapfill()
{
	for (int i=0;i<1;)
	{
		int r = rand() % ROW;
		int c = rand() % COL;
		if (map[r][c] == 0)
		{
			map[r][c] = createnum();
			i++;
		}
	}
}
//对数组进行初始化
void init()
{
	srand(time(0));
	for (int i = 0; i < 2;)
	{
		int r = rand() % ROW;
		int c = rand() % COL;
		if (map[r][c] == 0)
		{
			map[r][c] = createnum();
			i++;
		}
	}
}
//绘制游戏界面
void draw()
{
	setbkcolor(back);
	cleardevice();
	int i, j;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			int x;
			int y;
			x = 15 + i * 115;
			y = 15 + j * 115;
			int index = map[i][j] ? log2(map[i][j]) : 0;//如果map[i][j]不等于0，输出log2,否则输出0
			setfillcolor(colors[index]);
			solidroundrect(x, y, x + 100, y + 100, 10, 10);
			if (map[i][j])
			{
				char number[10] = { 0 };
				sprintf(number, "%d", map[i][j]);
				setbkmode(TRANSPARENT);
				settextcolor(RGB(119, 110, 101));
				settextstyle(50, 0, "微软雅黑");
				int hspace = (100 - textwidth(number)) / 2;
				int wspace = (100 - textheight(number)) / 2;
				outtextxy(x + hspace, y + wspace, number);
			}
		}
	}
}
//移动
void light()//左移
{
	bool ismoved = false;
	for (int c = 0; c < COL; c++)
	{
		int temp = 0;
		for (int begin = 1; begin < ROW; begin++)
		{
			if (map[begin][c] != 0)
			{
				if (map[temp][c] == 0)
				{
					map[temp][c] = map[begin][c];
					map[begin][c] = 0;
					ismoved = true;
				}
				else if (map[temp][c] == map[begin][c])
				{
					map[temp][c] *= 2;
					map[begin][c] = 0;
					temp++;
					ismoved = true;
				}
				else
				{
					map[temp + 1][c] = map[begin][c];
					if (temp + 1 != begin)
					{
						map[begin][c] = 0;
						ismoved = true;
					}
					temp++;
				}
			}
		}
	}
	if (ismoved)
	{
		mapfill();
	}
}
void right()//右移
{
	bool ismoved = false;
	for (int c = 0; c < COL; c++)
	{
		int temp = ROW-1;
		for (int begin = ROW-2; begin >= 0; begin--)
		{
			if (map[begin][c] != 0)
			{
				if (map[temp][c] == 0)
				{
					map[temp][c] = map[begin][c];
					map[begin][c] = 0;
					ismoved = true;
				}
				else if (map[temp][c] == map[begin][c])
				{
					map[temp][c] *= 2;
					map[begin][c] = 0;
					temp--;
					ismoved = true;
				}
				else
				{
					map[temp - 1][c] = map[begin][c];
					if (temp - 1 != begin)
					{
						map[begin][c] = 0;
						ismoved = true;
					}
					temp--;
				}
			}
		}
	}
	if (ismoved)
	{
		mapfill();
	}
}
void up()//上移
{
	bool ismoved = false;
	for (int c = 0; c < COL; c++)
	{
		int temp = 0;
		for (int begin = 1; begin < ROW; begin++)
		{
			if (map[c][begin] != 0)
			{
				if (map[c][temp] == 0)
				{
					map[c][temp] = map[c][begin];
					map[c][begin] = 0;
					ismoved = true;
				}
				else if (map[c][temp] == map[c][begin])
				{
					map[c][temp] *= 2;
					map[c][begin] = 0;
					ismoved = true;
					temp++;
				}
				else
				{
					map[c][temp + 1] = map[c][begin];
					if (temp + 1 != begin)
					{
						map[c][begin] = 0;
						ismoved = true;
					}
					temp++;
				}
			}
		}
	}
	if (ismoved)
	{
		mapfill();
	}
}
void down()//下移
{
	bool ismoved = false;
	for (int c = 0; c < COL; c++)
	{
		int temp = ROW - 1;
		for (int begin = ROW - 2; begin >= 0; begin--)
		{
			if (map[c][begin] != 0)
			{
				if (map[c][temp] == 0)
				{
					map[c][temp] = map[c][begin];
					map[c][begin] = 0;
					ismoved = true;
				}
				else if (map[c][temp] == map[c][begin])
				{
					map[c][temp] *= 2;
					map[c][begin] = 0;
					ismoved = true;
					temp--;
				}
				else
				{
					map[c][temp - 1] = map[c][begin];
					if (temp - 1 != begin)
					{
						map[c][begin] = 0;
						ismoved = true;
					}
					temp--;
				}
			}
		}
	}
	if (ismoved)
	{
		mapfill();
	}
}
void move()
{
	int key = _getch();//获取按键  72 80 75 77 上下左右
	switch (key)
	{
	case 72:
		up();
		break;
	case 80:
		down();
		break;
	case 75:
		light();
		break;
	case 77:
		right();
		break;
	}
}
//判断是否结束
int over() //判断结束
{
	int i, j;
	int gameover = 0;
	for (i = 0; i < 4; i++)
	{
	    for (j = 0; j < 4; j++)
		{
			if (map[i][j] == 0)
				gameover = 1;
			if (i >= 1) 
			{
				if (map[i][j] == map[i - 1][j])
				    gameover = 1;
			}
			if (j >= 1)
			{
				if (map[i][j] == map[i][j - 1])
					gameover = 1;
			}
		}
	}
	return gameover;
}
int victory()//判断胜利
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (map[i][j] == 2048)
			{
				return 1;
			}
		}
	}
}
int main()
{
	initgraph(WIDETH, HEIGTH,EW_NOCLOSE);
	mciSendString("open MoonHalo.mp3", 0, 0, 0);
	mciSendString("play MoonHalo.mp3", 0, 0, 0);
	init();
	while (1)
	{
		draw();
		move();
		if (victory() == 1)
		{
			cleardevice();
			settextcolor(RED);
			settextstyle(50, 0, "华文行楷");
			outtextxy(125, 215, "成功通关！");
			mciSendString("close MoonHalo.mp3", 0, 0, 0);
			break;
		}
		if (over() == 0)
		{
			cleardevice();
			settextcolor(RED);
			settextstyle(50, 0, "华文行楷");
			outtextxy(125, 215, "通关失败！");
			mciSendString("close MoonHalo.mp3", 0, 0, 0);
			break;
		}
	}
	getchar();
	return 0;
}