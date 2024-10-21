#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <cerrno>
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

void Create_RenderColors()
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
    gTexture = loadTexture(gOnePathImage);
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

    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedsurface);
    if(newTexture == NULL)
        throw("Failed to create texture image!", SDL_GetError());
    SDL_FreeSurface(loadedsurface);
    return newTexture; 
}


void EventHandler()
{   
    SDL_RenderClear(gRenderer);
    SDL_RenderPresent(gRenderer); 
    for( double i = 0; i < SCREEN_HIGHT; i++)
    {
        Pixel a(SCREEN_WIDHT / 2, i, 125);
        a.Show();
        SDL_RenderPresent(gRenderer);
    }

    for(double i = 0; i < SCREEN_WIDHT; i++)
    {
        Pixel a(i, SCREEN_HIGHT / 2, 125);
        a.Show();
        SDL_RenderPresent(gRenderer);
    }

    Squre kub(50, 50, 100, 200);
    kub.PolygonalCahin::Show();
    SDL_RenderPresent(gRenderer);

    Ractangle rac(150, 150, 300, 600, 86);
    rac.PolygonalCahin::Show();
    SDL_RenderPresent(gRenderer);
    
    FillRactange filrac(200, 320, 150, 200, 0);
    filrac.FillRactange::Show();
    SDL_RenderPresent(gRenderer);
    printf("Должны выводить цветной прямоугольник!\n"); 
    SDL_Delay(2000);
    
         
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
    if(gTexture != NULL)
    {
        SDL_DestroyTexture(gTexture);
        gTexture = NULL;
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

void GraphObject::Move(double nx, double ny)
{
    //  Hide();
    x = nx;
    y = ny;
    Show();
}

void Pixel::Show()
{
    SDL_SetRenderDrawColor(gRenderer, color, color, color, color);
    SDL_RenderDrawPoint(gRenderer, x, y);
}

void Pixel::Hide()
{
    
}

void Circle::Show()
{

}

void Circle::Hide()
{

}

void PolygonalCahin::AddVertex(double adx, double ady)
{
    Vertex *tmp = new Vertex;
    tmp->dx = adx;
    tmp->dy = ady;
    tmp->next = first;
    first = tmp;
}

PolygonalCahin::~PolygonalCahin()
{
    while(first)
    {
        Vertex *tmp = first;
        first = first->next;
        delete tmp;
    }
}

void PolygonalCahin::Show()
{
    SDL_SetRenderDrawColor(gRenderer, color, color, color, color);
    Vertex *tmp = first;
    while(tmp->next != 0)
    {
        SDL_RenderDrawLine(gRenderer, tmp->dx, tmp->dy, tmp->next->dx, tmp->next->dy);  
        tmp = tmp->next;
    }    
    
}

void PolygonalCahin::Hide()
{

}

void FillRactange::Show()
{
    SDL_SetRenderDrawColor(gRenderer, color, color, color, 255);
    SDL_RenderFillRect(gRenderer, &fillrect);
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

FuExeption::~FuExeption()
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
