#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "functions.h"
#include "menus.h"

int main()
{
    srand(time(NULL));
    init();
    SDL_Window *window = SDL_CreateWindow("Maps",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_OPENGL);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    music1=Mix_LoadMUS("music0.mp3");
    music2=Mix_LoadMUS("music4.mp3");
    Mix_PlayMusic( music1, -1 );
    first(window);

    while (running)
    {
        if (hmenu)
            menu(window);
        if (hsettings)
            settingsmenu(window);
        if (hranking)
            rankingmenu(window);
        if (hstart)
            startmenu(window);
        if (hmap)
            map(window);
        if (hend)
            endmenu(window);
    }
    Mix_FreeMusic( music1 );
    Mix_FreeMusic( music2 );
    music1 = NULL;
    music2 = NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();
}