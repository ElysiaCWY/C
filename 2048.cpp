#include <stdio.h>
#include <graphics.h> //ͼ��� 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <mmsystem.h> 
#include <conio.h>
#pragma comment (lib,"winmm.lib") //���ļ�
#define WIDETH 475  //��Ϸ����Ŀ��
#define HEIGTH 475  //��Ϸ����ĸ߶�
#define ROW 4//���������
#define COL 4//���������
//��ö�ٶ�Ҫʹ�õ���ɫ���ж��壬�������
enum Color
{
	zero = RGB(205, 193, 180),//0����ɫ
	two1 = RGB(238, 228, 218),//2����ɫ
	two2 = RGB(237, 224, 200),//4����ɫ
	two3 = RGB(242, 177, 121),//8
	two4 = RGB(245, 149, 99),//16
	two5 = RGB(246, 124, 95),//32
	two6 = RGB(246, 94, 59),//64
	two7 = RGB(237, 206, 113),//128
	two8 = RGB(237, 204, 97),//256
	two9 = RGB(255, 0, 128),//512
	two10 = RGB(145, 0, 72),//1024
	two11 = RGB(242, 17, 158),//2048
	back = RGB(187, 173, 160)//������ɫ
};
Color colors[13] = { zero,two1,two2,two3,two4,two5,two6,two7,two8,two9,two10,two11,back};
//�������ݵ�����
int map[ROW][COL];
//����һ���� 2��4 2�ĸ��ʸ���
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
//�ڿհ׷���������������
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
//��������г�ʼ��
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
//������Ϸ����
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
			int index = map[i][j] ? log2(map[i][j]) : 0;//���map[i][j]������0�����log2,�������0
			setfillcolor(colors[index]);
			solidroundrect(x, y, x + 100, y + 100, 10, 10);
			if (map[i][j])
			{
				char number[10] = { 0 };
				sprintf(number, "%d", map[i][j]);
				setbkmode(TRANSPARENT);
				settextcolor(RGB(119, 110, 101));
				settextstyle(50, 0, "΢���ź�");
				int hspace = (100 - textwidth(number)) / 2;
				int wspace = (100 - textheight(number)) / 2;
				outtextxy(x + hspace, y + wspace, number);
			}
		}
	}
}
//�ƶ�
void light()//����
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
void right()//����
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
void up()//����
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
void down()//����
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
	int key = _getch();//��ȡ����  72 80 75 77 ��������
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
//�ж��Ƿ����
int over() //�жϽ���
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
int victory()//�ж�ʤ��
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
			settextstyle(50, 0, "�����п�");
			outtextxy(125, 215, "�ɹ�ͨ�أ�");
			mciSendString("close MoonHalo.mp3", 0, 0, 0);
			break;
		}
		if (over() == 0)
		{
			cleardevice();
			settextcolor(RED);
			settextstyle(50, 0, "�����п�");
			outtextxy(125, 215, "ͨ��ʧ�ܣ�");
			mciSendString("close MoonHalo.mp3", 0, 0, 0);
			break;
		}
	}
	getchar();
	return 0;
}