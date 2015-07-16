#include <stdbool.h>

#include <SDL.h>

typedef struct
{
    SDL_Rect area;
    bool click;
} Button;

extern int ButtonInit(Button *button, int x, int y, int w, int h);
extern int ButtonRender(Button *button);
extern int ButtonClick(SDL_Event event);

