#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "erproc.h"
#include "global.h"

int main(int argc, char *argv[])
{
    try
    {
        Init_SDL();
        Create_Window();
        Create_RenderColors();
        Init_IMG();
        LoadMedia();
        EventHandler();
        Close();
    }
    catch(const FuExeption &ex)
    {
        fprintf(stderr, "Failed initialize: %s (%s): %s\n", ex.get_errorSDL, ex.GetComment(), strerror(ex.Get_ErrorSdl()));
        return 1;
    }
    return 0;
}
