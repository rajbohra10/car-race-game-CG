#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <alloc.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <process.h>
#include <string.h>
#define maxx 640
#define maxy 480
int max_x, max_y;
int road[] = {150, 0, maxx-150, 0, maxx-150, maxy, 150, maxy, 150, 0};
int road_sides[] = {120, 0, maxx-120, 0, maxx-120, maxy, 120, maxy, 120, 0};
int rect3[]={150+103,1,150+103+15,1,150+103+15,50,150+103,50,150+103,1}; 
int rect4[]={maxx-150-119,1,maxx-150-119+15,1,maxx-150-119+15,50,maxx-150-119,50,maxx-150-119,1};
int car_size[] = {165, 390, 170, 375, 233, 375, 238, 390, 238, 450, 165, 450, 165, 390};
int wheels[] = {155, 390, 165, 390, 165, 410, 155, 410, 155, 390};
int fullscreen[] = {0, 0, 639, 0, 639, 479, 0, 479, 0, 0};
int cover[] = {maxx-110, 50, maxx, 50, maxx, 100, maxx-110, 100, maxx-110, 50};
void game();
void loading()
{
    int i,a, per = 0;
     for(i=0;i<=200;i++)
    {
     setcolor(7);
     outtextxy(300,244,"LOADING...");
     setcolor(WHITE);
     line(224+i,238,224+i,256);
     setcolor(WHITE);
     rectangle(224,238,425,256);
     delay(25);
     gotoxy(55,16);
     setcolor(RED);
     if(i % 2 == 0)
     {
	printf("%d%",per);
	per++;
     }

     }
     settextstyle(1, 0, 1);
     setcolor(WHITE);
     outtextxy(getmaxx()/2-100, getmaxy()/2+20, "Press any key to start");
     getch();
     cleardevice();
     game();
 }

void exitScreen(int displayscore)
{
	char op, string[100];
	sprintf(string, "%d", displayscore);
	outtextxy(getmaxx()/2-100, getmaxy()/2-30, "Your score : ") ;
	outtextxy(getmaxx()/2+30, getmaxy()/2-30, string);
	outtextxy(getmaxx()/2-100, getmaxy()/2, "Do you want to play again?");
	outtextxy(getmaxx()/2-100, getmaxy()/2+30, "Y: Yes   N: No");
	op = getch();
	if(op=='Y'|| op=='y')
	{
		cleardevice();
		game();
	}
	else if(op=='N' || op=='n')
	{
		cleardevice();
		exit(1);
	}else if(op==27)
	{
		cleardevice();
		exit(1);
	}
}
void game()
{
	int x=1, position=1, interval=75, enemy=1, carspeed=5, score=0;
	int displayscore=0, value1=0, value2=0;
	char ch;
	char string[100];
	void *buff1; // for road strips
	void *buff2; //for car wheels
	void *buff3; //for player car
	void *buff4; //for enemy car wheels
	void *buff5; //for enemy car
	max_x = getmaxx();
	max_y = getmaxy();
	cleardevice();
	/* setting up white strips */
	setfillstyle(SOLID_FILL,WHITE);
	fillpoly(5,rect3);//draw strips on road
	fillpoly(5,rect4);//as above
	buff1=malloc(imagesize(150+103,1,150+103+15,50)); //to store left strip on  memory
	getimage(150+103,1,150+103+15,50,buff1);//stored left strip on memory
	putimage(150+103,1,buff1,XOR_PUT);//strips on road deleted from the memory//
	cleardevice();
	/* setting up the player car */
	setfillstyle(SOLID_FILL, 8);
	fillpoly(5, road);
	setcolor(RED);
	setfillstyle(SOLID_FILL, RED);
	fillpoly(7, car_size);
	setfillstyle(SOLID_FILL, BLACK);
	fillpoly(5, wheels);
	buff2 = malloc(imagesize(155, 390, 165, 410));
	getimage(155, 390, 165, 410, buff2);
	putimage(155, 390, buff2, XOR_PUT);
	putimage(155, 390, buff2, COPY_PUT);
	putimage(238, 390, buff2, COPY_PUT);
	putimage(155, 428, buff2, COPY_PUT);
	putimage(238, 428, buff2, COPY_PUT);
	buff3 = malloc(imagesize(155, 375, 248, 450));
	getimage(155, 375, 248, 450, buff3);
	putimage(155, 375, buff3, XOR_PUT);
	cleardevice();
	/* setting up the enemy cars */
	setfillstyle(SOLID_FILL, 8);
	fillpoly(5, road);
	setcolor(YELLOW);
	setfillstyle(SOLID_FILL, YELLOW);
	fillpoly(7, car_size);
	setfillstyle(SOLID_FILL, BLACK);
	fillpoly(5, wheels);
	buff4 = malloc(imagesize(155, 390, 165, 410));
	getimage(155, 390, 165, 410, buff4);
	putimage(155, 390, buff4, XOR_PUT);
	putimage(155, 390, buff4, COPY_PUT);
	putimage(238, 390, buff4, COPY_PUT);
	putimage(155, 428, buff4, COPY_PUT);
	putimage(238, 428, buff4, COPY_PUT);
	buff5 = malloc(imagesize(155, 375, 248, 450));
	getimage(155, 375, 248, 450, buff5);
	putimage(155, 375, buff3, XOR_PUT);
	cleardevice();
	setfillstyle(SOLID_FILL, BLUE);
	fillpoly(5, fullscreen);
	setfillstyle(SOLID_FILL, 7);
	fillpoly(5, road_sides);
	setfillstyle(SOLID_FILL, 8);
	fillpoly(5, road);
	setcolor(WHITE);
	srand(time(NULL));
	while(value1==value2)
	{
		value1 = rand()%3+1;
		value2 = rand()%3+1;
	}
	while(1)
	{

		if(score<=5)
			carspeed=15;
		else if(score>5 && score<=10)
			carspeed=20;
		else if(score>10 && score<=15)
			carspeed=20;
		else if(score>15 && score<=20)
			carspeed=25;
		else if(score>20 && score<=30)
			carspeed=30;
		else if(score>30)
			carspeed=40;

		if(value1!=1 && value2!=1)
		{
			enemy = enemy + carspeed;
			if((enemy>=300) && (position==2 || position==3))
			{
				delay(100);
				cleardevice();
				exitScreen(displayscore);
			}
			putimage(273, enemy, buff5, COPY_PUT);
			putimage(391, enemy, buff5, COPY_PUT);
			if(enemy>=450)
			{
				enemy=1;
				score = score+5;
				srand(time(NULL));
				do
				{
					value1 = rand()%3+1;
					value2 = rand()%3+1;
				}while(value1==value2);
			}
		}
		if(value1!=2 && value2!=2)
		{
			enemy = enemy + carspeed;
			if(enemy>=300 && (position==1 || position==3))
			{
				delay(100);
				cleardevice();
				exitScreen(displayscore);
			}
			putimage(155, enemy, buff5, COPY_PUT);
			putimage(391, enemy, buff5, COPY_PUT);
			if(enemy>=450)
			{
				enemy=1;
				score = score+5;
				srand(time(NULL));
				do
				{
					value1 = rand()%3+1;
					value2 = rand()%3+1;
				}while(value1==value2);
			}
		}
		if(value1!=3 && value2!=3)
		{
			enemy = enemy + carspeed;
			if(enemy>=300 && (position==2 || position==1))
			{
				delay(100);
				cleardevice();
				exitScreen(displayscore);
			}
			putimage(155, enemy, buff5, COPY_PUT);
			putimage(273, enemy, buff5, COPY_PUT);
			if(enemy>=450)
			{
				enemy=1;
				score = score+5;
				srand(time(NULL));
				do
				{
					value1 = rand()%3+1;
					value2 = rand()%3+1;
				}while(value1==value2);
			}
		}
		putimage(150+103,(x-1)*25,buff1,COPY_PUT);
		putimage(150+103+15+103,(x-1)*25,buff1,COPY_PUT);
		putimage(150+103,100+(x-1)*25,buff1,COPY_PUT);
		putimage(150+103+15+103,100+(x-1)*25,buff1,COPY_PUT);
		putimage(150+103,200+(x-1)*25,buff1,COPY_PUT);
		putimage(150+103+15+103,200+(x-1)*25,buff1,COPY_PUT);
		putimage(150+103,300+(x-1)*25,buff1,COPY_PUT);
		putimage(150+103+15+103,300+(x-1)*25,buff1,COPY_PUT);
		if(x!=5)
		{
			delay(interval);
			putimage(150+103, 400+(x-1)*25, buff1, COPY_PUT);
			sprintf(string, "%d", displayscore);
			displayscore++;
			putimage(150+103+15+103, 400+(x-1)*25, buff1, COPY_PUT);
			setfillstyle(SOLID_FILL, BLUE);
			fillpoly(5, cover);
		}
		if(x==5)
		{
			delay(interval);
			setfillstyle(SOLID_FILL, BLUE);
			fillpoly(5, cover);
			putimage(150+103, 1, buff1, COPY_PUT);
			putimage(150+103+15+103, 1,buff1, COPY_PUT);
			sprintf(string, "%d", displayscore);
			displayscore++;
			
		}
		setfillstyle(SOLID_FILL, 8);
		fillpoly(5, road);
		x++;
		settextstyle(1, DEFAULT_FONT, 4);
		outtextxy(maxx-100, 50, string);
		if(x==6)x=1;
		if(position==1)
		putimage(155, 375, buff3, COPY_PUT);
		else if(position==2)
		putimage(273, 375, buff3, COPY_PUT);
		else if(position==3)
		putimage(391, 375, buff3, COPY_PUT);
		if(kbhit())
		{
			ch=getch();
			switch(ch)
			{
				case 75: //left arrow key
					position--;
					break;
				case 77:
					position++;
					break;
				case 27:
					nosound();
					exit(1);
					break;
				default:
					break;
			 }
		}
		if(position>3)position=3;
		else if(position<1)position=1;
		settextstyle(1, DEFAULT_FONT, 2);
		outtextxy(maxx-100, 25, "SCORE: ");

	}
}



void main()
{
	int gd=DETECT, gm;
	initgraph(&gd, &gm, "..//BGI");
	loading();

}
