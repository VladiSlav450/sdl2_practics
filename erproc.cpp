#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "erproc.h"
#include "global.h"

void Init_SDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw FuExeption("SDL no be initiaze!", SDL_GetError());
    }
}

void Create_Window()
{
    gWindow = SDL_CreateWindow("First Bloode", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDHT, SCREEN_HIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL)
    {
        throw("SDL no CREATE WINDOW!", SDL_GetError());
    }
}

void Create_RenderColors(int one_col, int two_col, int three_col, int four_col)
{
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED); 
    if(gRenderer == NULL)
    {
        throw("SDL no CREATE Render!", SDL_GetError());
    }
    else
    {
        SDL_SetRenderDrawColor(gRenderer, one_col, two_col, three_col, four_col);
    }
}

void Init_IMG()
{
    if(!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
    {
        throw("SDL no CREATE IMG!", SDL_GetError());
    }
}

void LoadMedia()
{
    gTexture = LoadTexture(gOnePathImage);
    if(gTexture == NULL)
    {
        throw("Failed to load media!", SDL_GetError());
    }

}

SDL_Texture* loadTexture(const char *imagePath)
{   
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedsurface = IMG_Load(imagePath);
    if(loadedsurface == NULL)
    {
        throw("Failed to load texture image!", SDL_GetError());
    }

    newTexture = SDL_CreateTextureFromSurface(gRenderer, p_image);
    if(newTexture == NULL)
        throw("Failed to create texture image!", SDL_GetError());
    SDL_FreeSurface(p_image);
    return newTexture; 
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
        }
        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
        SDL_RenderPresent(gRenderer); 
    }
}

void Close()
{
    if(gTexture != NULL)
    {
        SDL_DestroyTexture(gTexture);
        gTexture = NULL;
    }
    if(gScreenSurface != NULL)
    {
    SDL_FreeSurface(gScreenSurface);
    gScreenSurface = NULL;
    }
    if(gRenderer != NULL)
    {
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    }
    if(gWindow != NULL)
    {
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    }
    IMG_Quit();  
    SDL_Quit();
}



FuExeption::FuExeption(const char *cmt, const char *geterSDL)
{
    err_code = errno;
    comment = strdup(cmt);
    get_errorSDL = strdup(geterSDL);
}

FuExeption::FuExeption(const FuExeption& other)
{
    err_code = other.err_code;
    comment = strdup(other.comment);
    get_errorSDL = strdup(other.get_errorSDL);
}

~FuExeption::FuExeption()
{
    delete[] comment;
    delete[] get_errorSDL;
}

char* FuExeption::strdup(const char *str)
{
    char *res = new char[strlen(str) + 1];
    strcpy(res, str);
    return res;
}
