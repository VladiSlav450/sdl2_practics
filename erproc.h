#ifndef ERPROC_h
#define ERPROC_h

bool Init_SDL();
bool Create_Window();
bool Create_RenderColors();
bool Init_IMG();
bool LoadMedia();
bool EventHandler();
bool Close();
SDL_Texture* loadTexture(const char *imagePath);

class FuExeption
{
    int err_code;
    char *comment;
    char *get_errorSDL;
public:
    FuExeption(const char *comment, const char *get_errorSDL);
    FuExeption(const FuExeption& other);
    ~FuExeption();
    const char *GetComment() { return comment; }
    const char *Get_ErrorSdl() { return get_errorSDL; }
    int GetErrno() const { return err_code; }
    static char *strdup(const char *str);
};

#endif
