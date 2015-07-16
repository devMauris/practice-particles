#include "button.h"
#include "engine.h"

int ButtonInit(Button *button, int x, int y, int w, int h)
{
    button->area.x = x;
    button->area.y = y;
    button->area.w = w;
    button->area.h = h;
    button->click = false;
    return 0;
}

int ButtonRender(Button *button)
{
    SDL_SetRenderDrawColor(mainEngine->gRenderer, 0x9B, 0x9B, 0x9B, 0x9B);
    SDL_RenderFillRect(mainEngine->gRenderer, &(button->area));
    return 0;
}
int ButtonHandle(Button *button, SDL_Event event)
{

    //now check if it inside our area
    int x = 0, y = 0;
    SDL_GetMouseState(&x, &y);
    if (x >= button->area.x && x <= button->area.x + button->area.w
        && y <= button->area.y + button->area.h
        && y >= button->area.y)
    {

    }

    return 0;
}