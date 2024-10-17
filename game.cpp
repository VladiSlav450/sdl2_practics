#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDHT = 640;
const int SCREEN_HIGHT = 480;

int main(int argc, char *argv[])
{
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        printf("SDL no Init!, SDL_ERROR: %s\n", SDL_GetError());
    else 
    {
        window = SDL_CreateWindow("First Bloode", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDHT, SCREEN_HIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
            printf("SDL no CREATE WINDOW! SDL_ERROR: %s", SDL_GetError());
        else
        {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 234, 111, 45));
            SDL_UpdateWindowSurface(window);
            
            SDL_Event e;
            bool quit = false;

            while(quit == false)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT)
                        quit = true;
                }
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit(); 
    
    return 0;
}
