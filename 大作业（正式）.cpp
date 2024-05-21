#include <stdlib.h>
#include <process.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
////////////
//
//
///////////
void HideCursor(int x)    //光标显示与隐藏 1显示 0隐藏
{
	CONSOLE_CURSOR_INFO cursor_info = {1,x};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
void GotoXY(int x,int y)   //设置光标位置
{
	COORD pos;
	pos.X = x-1;
	pos.Y = y-1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void SetColorBK(int color)        //添加背景颜色
{
	HANDLE consolehwnd;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	consolehwnd=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(consolehwnd,&csbiInfo);
	color = (color<<4)+(csbiInfo.wAttributes & 0xf);
	SetConsoleTextAttribute(consolehwnd,color);

}
void SetColor(int color)        //添加颜色
{
	HANDLE consolehwnd;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	consolehwnd=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(consolehwnd,&csbiInfo);
	color = color+(csbiInfo.wAttributes & 0xf0);
	SetConsoleTextAttribute(consolehwnd,color);

}

void DrawRectangle(int x1,int y1,int x2,int y2)//绘制矩阵
{
	int i;
	for(i=x1;i<=x2;i=i+1)
	{
		GotoXY(i,y1);
		printf("■");
		GotoXY(i,y2);
		printf("■");
	}
	for(i=y1;i<=y2;i= i+1)
	{
		GotoXY(x1,i);
		printf("■");
		GotoXY(x2,i);
		printf("■");
	}
}

void DrawPlan(int x2,int y1)   //绘制小飞机
{
	GotoXY(x2+10,y1);
	if(y1>0)
		printf("      ▲");
	GotoXY(x2+10,y1+1);
	if(y1+1>0)
		printf("      ■");
	GotoXY(x2+10,y1+2);
	if(y1+2>0)
		printf("      ■");
	GotoXY(x2+10,y1+3);
	if(y1+3>0)
		printf("    ◢■◣");
	GotoXY(x2+10,y1+4);
	if(y1+4>0)
		printf("  ◢■■■◣");
	GotoXY(x2+10,y1+5);
	if(y1+5>0)
		printf("◢■■■■■◣");
	GotoXY(x2+10,y1+6);
	if(y1+6>0)
		printf("    ◢■◣");
	GotoXY(x2+10,y1+7);
	if(y1+7>0)
		printf("  ◢■■■◣");
}

int duan=1;
void Delay (unsigned int i)
{
	while(i--)
	{ Sleep(1);
		if(kbhit()!=0)
		{
			duan=0;
			break;
		}
	}
}

int main()//主程序
{
	int x1=20,y1=2,x2=x1+26+2,y2=y1+20;
	int i,t,s;
	int b;
	char c,d;
	SetColorBK(8);
	system("mode con cols=80 lines=22");//设置窗口大小
	PlaySound(TEXT("Fortune.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
	SetColor(11);
	GotoXY(x1+8,y1+4);//开场白
	printf("欢迎观赏奇妙的字幕雨");
	GotoXY(x1+10,y1+5);
	printf("(任意按键退出)");
	Delay(150);
	GotoXY(x1+8,y1+4);
	printf("                    ");
	GotoXY(x1+10,y1+5);
	printf("                    ");
	HideCursor (0);   //光标显示与隐藏 1显示 0隐藏
	SetColor(3);//矩形初始颜色
	DrawRectangle(x1,y1,x2,y2);//绘制矩阵
	GotoXY(x1+2,y2-1);  //设置光标位置
	SetColor(15);//字体初始颜色
	printf("ABCDEFGHIJKLMNOPQRSTUVWXYZ");


	do
	{
		for(t=0;duan!=0;t=t+1){//显示掉落字母  t
			SetColor(rand()%16);
			c = rand()%26+'A';//把一个26内的随机数赋值给 c
			SetColor(rand()%16);
			d = rand()%26+'A';//把一个26内的随机数赋值给 d
			if(c=d)
				c=rand()%26+'A';
			GotoXY(x2+4,y1+t);
			printf("%c %c",c,d);
			if(t>=20)
				t=0;
			for(i=y1+1;i<y2-1;i=i+1)
			{
				GotoXY(x1+c-'A'+2,i);//字母 下落位置
				printf("%c",c);  //显示陨落字母
				if(duan==0)
					break;
				GotoXY(x1+d-'A'+2,i);
				printf("%c",d);
				Delay(15); //程序停留10ms
				if(duan==0)
					break;
				GotoXY(x1+c-'A'+2,i);
				printf(" ");
				GotoXY(x1+d-'A'+2,i);
				printf(" "); 	// 清除陨落字母
			}
			GotoXY(x1+c-'A'+2,i);
			printf("=");//砸扁后代替陨落字母
			GotoXY(x1+d-'A'+2,i);
			printf("=");//砸扁后代替陨落字母
			Delay(100);  //陨落字母被砸扁的时间
			if(duan==0)
				break;
			GotoXY(x1+d-'A'+2,i);
			printf("%c",d);
			GotoXY(x1+c-'A'+2,i);
			printf("%c",c); //恢复替陨落字母.
			HideCursor(0);
			for(s=10;s>-10;s=s-1){
				SetColor(rand()%15+1);
				DrawPlan(55,s);
				Sleep(20);
				SetColor(8);//飞机尾坠颜色
				DrawPlan(55,s);
			}
		}
	}
	while(duan!=0);
	system("cls");//结束语
	HideCursor(1);
	system("mode con cols=80 lines=22");//设置窗口大小
	SetColor(11);
	GotoXY(x1+10,y1+5);
	printf("谢");
	SetColor(rand()%16);
	GotoXY(x1+11,y1+6);
	printf("谢");
	SetColor(rand()%16);
	GotoXY(x1+12,y1+7);
	printf("观");
	SetColor(rand()%16);
	GotoXY(x1+13,y1+8);
	printf("赏");
	
    HideCursor(0); 
	Sleep(1000);
	
	return 0;
}


