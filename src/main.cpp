#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];
SDL_Surface* gCurrentSurface = NULL;

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

SDL_Surface* loadSurface(std::string path) {
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if(loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
	}
	return loadedSurface;
}

bool loadMedia() {
	bool success = true;
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = SDL_LoadBMP("key_presses/press.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		printf("Failed to load default image!\n");
		success = false;
	}

	 //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "key_presses/up.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "key_presses/down.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "key_presses/left.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "key_presses/right.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;
}

void close() {
	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( gKeyPressSurfaces[ i ] );
		gKeyPressSurfaces[ i ] = NULL;
	}

	SDL_DestroyWindow( gWindow );
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
			bool quit = false;
			SDL_Event e;
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
			while(!quit) {
				while(SDL_PollEvent(&e) != 0) {
					if(e.type == SDL_QUIT) {
						quit = true;
					} else if(e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
							break;
						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
							break;
						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
							break;
						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
							break;
						default:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}
				SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	close();
	return 0;
}