#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	} else {
		gWindow = SDL_CreateWindow("SDL Tut", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		} else {
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			return true;
		}
	}
}

bool loadMedia() {
	gHelloWorld = SDL_LoadBMP("src/sample_640×426.bmp");
	if(gHelloWorld == NULL) {
		printf("Unable to load image %s! SDL_Error: %s\n", "src/sample_640×426.bmp", SDL_GetError());
		return false;
	}
	return true;
}

void close() {
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

int main( int argc, char* args[] )
{
	if(!init()) {
		printf("Fail to initilize!\n");
	} else {
		if(!loadMedia()) {
			printf("Fail to load media!\n");
		} else {
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface(gWindow);
			SDL_Delay(2000);
		}
	}
	close();
	return 0;
}