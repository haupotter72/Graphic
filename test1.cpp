#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <math.h>
#include <stdio.h>

float t = 0.0;
float x, y,g,h;
int nx,ny;
int k = 1;
void dc()
{
  line(x+130, y-110, getmaxx()-83,35);
}

void dt()
{
  line(getmaxx()-33,h-285,getmaxx()-33,h-240);
}

void quay()
{
  int x1, y1, x2, y2;
  circle(getmaxx()-60, 50, 26);
  x1 = getmaxx()-60 - 26 * cos(t);
  y1 = 50 - 26 * sin(t);
  x2 = getmaxx()-60 + 26 * cos(t);
  y2 = 50 + 26 * sin(t);
  line(x1, y1, x2, y2);
}



void xe()
{
  line(x-50,y+30,x-15,y+6);
  line(x-50,y+30,x-75,y-40);
  line(x-75,y-40,x+45,y-120);
  line(x+45,y-120,x+70,y-50);
  line(x+70,y-50,x+13,y-11);

  line(x+70,y-50,x+85,y-60);
  line(x+113,y-79,x+134,y-94);
  line(x+134,y-94,x+115,y-144);
  line(x+115,y-144,x+52,y-100);
}
void chu()
{
  //ve M
  line(x-45,y-10,x-50,y-25);
  line(x-50,y-25,x-41,y-18);
  line(x-41,y-18,x-39,y-32);
  line(x-39,y-32,x-34,y-17);
  //ve E
  line(x-31,y-19,x-36,y-34);
  line(x-36,y-34,x-30,y-38);
  line(x-35,y-27,x-29,y-31);
  line(x-31,y-19,x-25,y-23);
  //ve R
  line(x-22,y-25,x-27,y-40);
  line(x-27,y-40,x-21,y-41);
  line(x-21,y-41,x-19,y-35);
  line(x-19,y-35,x-24,y-30);
  line(x-24,y-30,x-17,y-28);
  //ve C
  line(x-14,y-30,x-8,y-34);
  line(x-14,y-30,x-19,y-45);
  line(x-19,y-45,x-13,y-49);

  line(x-5,y-36,x-10,y-51);
  line(x-10,y-51,x-4,y-55);
  line(x-9,y-44,x-3,y-48);
  line(x-5,y-36,x+1,y-40);
  //ve D
  line(x+4,y-42,x-2,y-57);
  line(x-2,y-57,x+5,y-59);
  line(x+5,y-59,x+9,y-48);
  line(x+3,y-42,x+9,y-48);
  //ve E
  line(x+12,y-49,x+7,y-62);
  line(x+7,y-63,x+13,y-67);
  line(x+8,y-56,x+14,y-60);
  line(x+12,y-48,x+18,y-52);
  //ve C
  line(x+21,y-54,x+27,y-58);
  line(x+21,y-54,x+16,y-69);
  line(x+16,y-69,x+22,y-73);


}

void chunhat()
{
  line(getmaxx()-53,h-240,getmaxx()-13,h-240);
  line(getmaxx()-53,h-240,getmaxx()-53,h-150);
  line(getmaxx()-53,h-150,getmaxx()-13,h-150);
  line(getmaxx()-13,h-150,getmaxx()-13,h-240);
}
void vebanhxe(float a,float b)
{
  int x1, y1, x2, y2;
  circle(a, b, 15);
  x1 = a - 15 * cos(t);
  y1 = b - 15 * sin(t);
  x2 = a + 15 * cos(t);
  y2 = b + 15 * sin(t);
  line(x1, y1, x2, y2);
    //ve nan hoa
	nx=a+15*cos(t+2*M_PI/2);
	ny=b+15*sin(t+2*M_PI/2);
	line(a,b,nx,ny);
	nx=a+15*cos (t+4*M_PI/3);
	ny=b+15*sin(t+4*M_PI/3);
	line(a,b,nx,ny);
	nx=a-15*cos (t+3*M_PI/5);
	ny=b-15*sin(t+3*M_PI/5);
	line(a,b,nx,ny);
      nx=a+15*cos(t+2*M_PI/6);
      ny=b+15*sin(t+2*M_PI/6);
      line(a,b,nx,ny);
      nx=a+15*cos(t+4*M_PI/7);
	ny=b+15*sin(t+4*M_PI/7);
      line(a,b,nx,ny);
   }

void main()
{
  int gd = DETECT, gm ;
  initgraph(&gd, &gm, "C:\\TC\\BGI");
  printf("\nDANG THANH NAM\n");

  line(getmaxx()-100,91,getmaxx()-82,67);
  line(76, 400, getmaxx()-100,91);
  line(76, 400, getmaxx()-100,400);
  line(getmaxx()-100,400,getmaxx()-100,91);
  x = 135;
  y = 340;
  h = y;
  g = k;
  while (!kbhit())
  {
     setcolor(YELLOW);
     vebanhxe(x,y);vebanhxe(x+100,y-68);chu();
     setcolor(BLUE);quay();
     xe(); chu();
     setcolor(RED);
     chunhat(); chu();
     setcolor(GREEN);
     dc();dt();
     delay(25);
     setcolor(BLACK);
     xe(); chu();
     vebanhxe(x,y);vebanhxe(x+100,y-68);      chunhat();dc();quay();
     t += 0.09 * (float)k;
     x += k;
     y -=k/1.5;
     h += g;
     if (x > (getmaxx() - 250 - 2) || x < 135)
     {
	 k = -k;
     }
     if (h >345 + 247 || h < 340  )
     {
	 g = -g;
     }
  }
  getch();
  closegraph();
}

