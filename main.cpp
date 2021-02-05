#include <sstream>      //stringstream, rand, srand, string
#include <ctime>        //time
#include <iostream>

#include <sdl.h>
#include <sdl_ttf.h>

#include "c:\z\_MI\Window.h"
#include "c:\z\_MI\drawshapes.h"
#include "c:\z\_MI\defines.h"
#include "c:\z\_MI\drawfontsolid.h"
#include "c:\z\_MI\colors.h"

#undef main

SDL_Renderer*  renderer;
SDL_Window*    window;
SDL_Event      e;

SDL_Texture*	solidTexture;
SDL_Texture*	text;
SDL_Rect			solidRect;
TTF_Font*		gFont;

float FPS =    1000/33.3f;
bool running = true;

static int val1 = 50;
static int val2 = 0;

void input()
{
	while(POLLEVENT)
	{
		/*
      switch(e.window.event)
		{
			case SDL_WINDOWEVENT_ENTER:break;
			case SDL_WINDOWEVENT_LEAVE:break;
		}
      */
		
		if(QUIT){running = false;}
		if(DOWNPRESS)
		{
			if(ESCAPE)     running = false;
			if(UP)         val1++;         
			if(DOWN)       val1--;         
			if(LEFT)       val2--;         
			if(RIGHT)      val2++;         
			if(PAGEUP)     val1 += 10;     
			if(PAGEDOWN)   val1 -= 10;
		}
	}
}

#include <math.h>

void circle(int x, int y, int r, int g, int b, int a)
{
	static double angle = 0.0;
#pragma warning(disable: 4244)
	
   for(double i = 0.0; i < 360.0; i++)
   {
		for(int j = 0; j < 10; j++)
		{
			drawPoint(x+cos(i)*j,
						 y+sin(i)*j,
						 r,g,b,a);
		}
   }

	angle+=1.0;
}

void draw()
{
	SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0x00);
	SDL_RenderClear(renderer);

	// begins at a random value form 0-99
	// then incremts from 1-10 randomly
	unsigned int rnx = rand() % 1440;
	unsigned int rny = rand() % 900;
		
	unsigned int rnx2 = rand() % 1440;
	unsigned int rny2 = rand() % 900;

	static int incre = 0;
	static int incre2 = 0;
	static bool toggle = true;
	static bool toggle2 = true;
	static bool attdef = true;

	static unsigned int nrnx;
	static unsigned int nrny;
		
	static unsigned int nrnx2;
	static unsigned int nrny2;

	//CONVERSION INT TO CONST CHAR*
	std::stringstream convert1;
	convert1 << val1;
	std::string one  = convert1.str();
	const char* cone = one.c_str();

	std::stringstream convert2;
	convert2 << val2;
	std::string two  = convert2.str();
	const char* ctwo = two.c_str();
		
	//  1-300 1000ms /   1
	//  2-200  500ms /   2
	//  3-150  333ms /   3
	//  4-125  250ms /   4
	//  8-100  125ms /   8
	// 45- 50   20ms /  24
	//256-  1    4ms / 128
	
	drawFontSolid(0,0,0,0, 0,cone,CYAN,"c:/z/_MI/data/font/arial.ttf",32);
	//drawFontSolid(0,0,0,0,32,ctwo,CYAN,"c:/z/_MI/data/font/arial.ttf",32);

	// white
	if(incre >= val1)
	{
		incre = 0;
		toggle = true;
	}
	else
	{
		if(toggle)
		{
			nrnx = rnx;
			nrny = rny;
			toggle = false;
		}
		drawFillRect(nrnx,  nrny,25,25,255,255,255,255);//white
		//circle(nrnx, nrny,WHITE);
	}

	// red
	if(incre2 >= 50)
	{
		//drawFillRect(nrnx2,nrny2,25,25,255,0,0,255);//red
		incre2 = 0;
		toggle2 = true;
	}
	else
	{
		if(toggle2)
		{
			nrnx2 = rnx2;
			nrny2 = rny2;
			toggle2 = false;
		}
	}

	incre++;
	incre2++;
		
	//SDL_Delay((Uint32)FPS);
	SDL_RenderPresent(renderer);
}

void update()
{
   SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS,"0"); 
}

int main()
{
	init_Window(0,0,1440,900,2,1);
	
	#pragma warning(disable:4244)
		
	srand(time(NULL));
	
	while(running)
   {
		input();
		draw();
		update();
	}
	return(0);
}

