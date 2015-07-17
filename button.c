//
// Created by zemuvier on 17.07.2015.
//

#include "button.h"
#include "engine.h"

int ButtonInit(Button *button, int x, int y, int w, int h)
{
    button->area.x = x;
    button->area.y = y;
    button->area.w = w;
    button->area.h = h;
    button->clicked = false;
    button->a = 0xFF;
    button->b = 0xFF;
    button->c = 0xFF;
    return 0;
}

int ButtonRender(Button *button)
{
    SDL_SetRenderDrawColor(mainEngine->gRenderer, button->a, button->b, button->c, 0xFF);
    SDL_RenderFillRect(mainEngine->gRenderer, &(button->area));
    return 0;
}

int ButtonHandle(Button *button, SDL_Event event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
    {
        //now check if it inside our area
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);

        if (x >= button->area.x && x <= button->area.x + button->area.w
            && y >= button->area.y
            && y <= button->area.y + button->area.h)
        {
            button->clicked = true;
        }
    }

    return 0;
}

int ChangeColorButton(Button *button, int r, int g, int b)
{
    button->a = r;
    button->b = g;
    button->c = b;
    return 0;
}