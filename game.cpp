#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "erproc.h"
#include "global.h"

int main(int argc, char *argv[])
{
    if(!Init())
        printf("Failed t initialize\n");
    else
    {
        if(!Init_IMG())
        {
            printf("Failed to IMG initialize\n");
        }
        else
        {
            if(!LoadMedia())
                printf("Failed to load media.\n");
            else
            {
                SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    } 
    Pause();
    Close();
    return 0;
}


