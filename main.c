#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

#include "SDL/SDL.h"

#include "pixeltools.h"
#include "complex.h"

#define W_WIDTH 500
#define W_HEIGHT 500

void Error(char * msg, bool sys_error);
void EventLoop(SDL_Surface * screen);
void EventKeydown(void);

void DrawMandelbrot(SDL_Surface * surface, float magnify, float x_displacement,
	float y_displacement, int max_iter);

void Mb_GetPtColor(int x, int y, int *r, int *g, int *b);

int main(int argc, char *argv[]){
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER))
		Error("SDL_Init", 1);
	
	SDL_Surface * screen = SDL_SetVideoMode(W_WIDTH, W_HEIGHT, 24, 
		SDL_SWSURFACE | SDL_ASYNCBLIT | SDL_DOUBLEBUF);
		if(screen == NULL) Error("SDL_SetVideoMode", 1);
	
	atexit(SDL_Quit); // clean up sdl on exit
	
	//
	SDL_LockSurface(screen);
	DrawMandelbrot(screen, 1.0, 0, 0, 255);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_UnlockSurface(screen);
	
	
	EventLoop(screen);
	
	return 0;
}

void Error(char * msg, bool sys_error){
	if(sys_error) printf("From(%s): %s\n", msg, SDL_GetError());
	else printf("%s\n", msg);
	exit(1);
}

void EventLoop(SDL_Surface * screen){
	SDL_Event event;
	bool quit = 0;
	int max_iter = 255;
	float magnify = 1.0;
	float x_displacement = 0;
	float y_displacement = 0;
	
	while(!quit){
	while(SDL_PollEvent(&event)) {
		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					// --- navigation ----
					case (SDLK_LEFT):
						x_displacement -= 0.1;
						break;
					case (SDLK_RIGHT):
						x_displacement += 0.1;
						break;
					case (SDLK_DOWN):
						y_displacement -= 0.1;
						break;
					case (SDLK_UP):
						y_displacement += 0.1;
						break;
					// --- 
					
					// -- Magnification --
					case (SDLK_RETURN):
						magnify += 5;
						break;
					case (SDLK_BACKSPACE):
						magnify -= 5;
						break;
					// ---
					
					// -- Iteration control --
					case (SDLK_PLUS):
						max_iter += 100;
						break;
					case (SDLK_MINUS):
						max_iter -= 100;
						break;
					// ---
					
				}
			//
			SDL_LockSurface(screen);
			SDL_FillRect(screen, NULL, 0);
			DrawMandelbrot(screen,  magnify, x_displacement, 
				y_displacement, max_iter);
			//SDL_UpdateRect(screen, 0, 0, 0, 0);
			SDL_Flip(screen);
			SDL_UnlockSurface(screen);
			//
			break;
			case SDL_QUIT:
				quit = 1;
				break;
		}
	}}
}

void DrawMandelbrot(SDL_Surface * screen, float magnify, float x_displacement,
	float y_displacement, int max_iter) {
	int n; // number of iterations for current point
	int x = 0, y = 0; // pixel
	
	printf("%.0lf\n", magnify);
	Z p = {0, 0}; // Point on complex plane, used to pass to GetN
	
	
	//(target width / source width, target height / source height)

	for(; y != W_HEIGHT; y++){
		x = 0;
		for(; x != W_WIDTH; x++){
		
				//      Scale                	
			p.a = ( ((float)x) / ((float)W_WIDTH)   
				// Remember that the mandelbrot set is [-2,2] on
				// both axis, so we backtrack by 0.5
				+x_displacement-0.5)
			  /magnify*3.0;
			  
			p.b = ( ((float)y) / ((float)W_HEIGHT)-y_displacement-0.5) /magnify*3.0;
			
			//p.a = (float)x / float
			
			n = Mb_GetN(p, max_iter);
			if(n > 0){
				putpixel(screen, x, y, SDL_MapRGB(screen->format, (n/3)%255, 0, n%255 )) ;
			}
		}
		//printf("\n%d\n", y);
	}
	printf("\ndone\n");
}



