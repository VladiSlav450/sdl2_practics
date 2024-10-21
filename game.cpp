#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <cerrno>
#include "erproc.h"
#include "global.h"

int main(int argc, char *argv[])
{
    try
    {
        Init_SDL();
        Create_Window();
        Create_RenderColors();
//        Init_IMG();
//        LoadMedia();
        EventHandler();
        Close();
    }
    catch(const FuExeption &ex)
    {
        fprintf(stderr, "Failed initialize: %s (%s): %s\n", ex.Get_ErrorSDL(), ex.GetComment(), strerror(ex.GetErrno()));
        return 1;
    }
    return 0;
}
