#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

const int SCREEN_WIDHT = 937;
const int SCREEN_HIGHT = 576;

bool Init(); // start SDL and creat window
bool Init_IMG();
bool LoadMedia(); // Loads media
void Pause();
void Close(); // Free media and shuts down SDL

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

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
