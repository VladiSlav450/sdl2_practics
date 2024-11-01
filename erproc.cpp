// file: erproc.cpp

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
    Circle xyi(600, 400, 10, 0);
    xyi.Circle::Show();
    SDL_RenderPresent(gRenderer);

    Squre kv(200, 300, 150, 0);
    kv.PolygonalCahin::Show();  
    SDL_RenderPresent(gRenderer);
         
    SDL_Event e;
    bool quite = true;
    while (quite)
    {
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    quite = false;
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE)
                    quite = false;
            }
            xyi.HandEvent(e);
        }
        xyi.Move();
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);
        xyi.Circle::Show();

        Squre kv(200, 300, 150, 0);
        kv.PolygonalCahin::Show();  
     
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

void GraphObject::Move()
{
    //  Hide();
    
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
    SDL_SetRenderDrawColor(gRenderer, color, color, color, color);
    int crx = radius, cry = 0;
    int err = 0;
    while(crx >= cry)
    {
        DrawPointCircle(crx, cry);
        cry++;
        err += 2 * cry + 1;
        if(err >=  2 * crx)
        {
            crx--;
            err -= 2 * crx + 1;
        }
    }
    
}

void Circle::DrawPointCircle(int& crx, int& cry)
{
    SDL_RenderDrawPoint(gRenderer, x + crx, y + cry);
    SDL_RenderDrawPoint(gRenderer, x + cry, y + crx);
    SDL_RenderDrawPoint(gRenderer, x - cry, y + crx);
    SDL_RenderDrawPoint(gRenderer, x - crx, y + cry);
    SDL_RenderDrawPoint(gRenderer, x - crx, y - cry);
    SDL_RenderDrawPoint(gRenderer, x - cry, y - crx);
    SDL_RenderDrawPoint(gRenderer, x + cry, y - crx);
    SDL_RenderDrawPoint(gRenderer, x + crx, y - cry);
}

void Circle::HandEvent(SDL_Event& e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym) 
        {
            case SDLK_UP:
                mVelY -= DOT_VEL;
                break;
            case SDLK_DOWN:
                mVelY += DOT_VEL;
                break;
            case SDLK_LEFT:
                mVelX -= DOT_VEL;
                break;
            case SDLK_RIGHT:
                mVelX += DOT_VEL;
                break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym) 
        {
            case SDLK_UP:
                mVelY += DOT_VEL;
                break;
            case SDLK_DOWN:
                mVelY -= DOT_VEL;
                break;
            case SDLK_LEFT:
                mVelX += DOT_VEL;
                break;
            case SDLK_RIGHT:
                mVelX -= DOT_VEL;
                break;
        }
    }
}

void Circle::Hide()
{

}

void Circle::Move()
{
    x += mVelX;
    if((x - radius < 0) || (x + radius > SCREEN_WIDHT))
        x -= mVelX;
    y += mVelY;
    if((y - radius < radius) || (y + radius > SCREEN_HIGHT))
        y -= mVelY;
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
