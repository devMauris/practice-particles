//
// Created by zemuvier on 17.07.2015.
//

#include "button.h"
#include "engine.h"

int ButtonInit(Button *button, int x, int y, int w, int h, int color)
{
    button->area.x = x;
    button->area.y = y;
    button->area.w = w;
    button->area.h = h;
    button->clicked = false;
    button->color = color;
    return 0;
}

int ButtonRender(Button *button)
{
    SDL_SetRenderDrawColor(mainEngine->gRenderer,
                           (uint8_t) (button->color>>24),
                           (uint8_t) (button->color>>16),
                           (uint8_t) (button->color>>8),
                           (uint8_t) (button->color));
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

int ButtonSetColor(Button *button, int color)
{
    button->color = color;
    return 0;
}