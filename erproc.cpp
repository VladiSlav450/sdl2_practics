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

bool LoadMedia()
{
    bool succses = true;
    const char *imagePath = "/home/vlad/Изображения/first_blood.jpg";
    gHelloWorld =  IMG_Load(imagePath);
    if(gHelloWorld == NULL)
    {
        printf("Unable to load image %s! SDL_ERROR: %s\n", imagePath, SDL_GetError());
        succses = false;
    }
    return succses;
}

void Pause()
{
    SDL_Event e;
    bool quite = false;
    while (quite == false)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                quite = true;
        }
    }
}

void Close()
{
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    
    SDL_Quit();
}
