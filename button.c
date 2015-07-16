#include "button.h"

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
}
int ButtonClick(SDL_Event event)
{
    while (!button->click)
    {
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            //now check if it inside our area
            int x = 0, y = 0;
            SDL_GetMouseState(&x, &y);
            if (x >= button.area.x && x <= button.area.x + button.area.widht
                                      && y <= button.area.y + button.area.height
                                      && y >= button.area.y)
            {
                ButtonRender(button);
                SDL_Rect button = {60, 60, 40, 40};
                SDL_RenderPresent(button->gRenderer);
                SDL_Delay(16);
            }
        }
    }
}