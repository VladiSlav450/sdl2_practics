// file: game.cpp

#include "erproc.h"
#include "global.h"

int mySDL_main()
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
