#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "erproc.h"
#include "global.h"

bool Init()
{
    bool succses = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL no Init!, SDL_ERROR: %s\n", SDL_GetError());
        succses = false;
    }
    else 
    {
        gWindow = SDL_CreateWindow("First Bloode", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDHT, SCREEN_HIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            printf("SDL no CREATE WINDOW! SDL_ERROR: %s\n", SDL_GetError());
            succses = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return succses;
}

bool Init_IMG()
{
    bool succses = true;
    if(!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
    {
        printf("IMG no initialize: %s", IMG_GetError());
    }
    return succses;
}

SDL_Surface* LoadOneSurface(const char *imagePath)
{
    SDL_Surface* image_photo =  IMG_Load(imagePath);
    if(image_photo == NULL)
    {
        printf("Unable to load image %s! SDL_ERROR: %s\n", imagePath, SDL_GetError());
    }
    return image_photo;
}

bool LoadAllMedia()
{
    bool succses = true;
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFULT] = LoadOneSurface(gOnePathImage);
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFULT] == NULL)
    {
        printf("Failed to load One image!\n");
        succses = false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = LoadOneSurface(gTwoPathImage);
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        printf("Failed to load Two image!\n");
        succses = false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = LoadOneSurface(gThreePathImage);
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        printf("Failed to load Three image!\n");
        succses = false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = LoadOneSurface(gFourPathImage);
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        printf("Failed to load Four image!\n");
        succses = false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = LoadOneSurface(gFivePathImage);
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        printf("Failed to load Five image!\n");
        succses = false;
    }
    
    return succses;
}
void EventHandler()
{
    SDL_Event e;
    bool quite = false;
    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFULT];
    while (quite == false)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                quite = true;
            else if  (e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
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
                
                    defult:     
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFULT];
                        break;
                }
            }
        }
        SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
        SDL_UpdateWindowSurface(gWindow);
    }
}

void Close()
{
    SDL_FreeSurface(gScreenSurface);
    gScreenSurface = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    
    SDL_Quit();
}
