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
    button->released = false;
    button->over = false;
    button->color = color;
    return 0;
}

int ButtonRender(Button *button)
{
    if(button->clicked)
    {
        SDL_SetRenderDrawColor(mainEngine->gRenderer,
                               (uint8_t) ((button->color>>24) + 20),
                               (uint8_t) ((button->color>>16) + 20),
                               (uint8_t) ((button->color>>8) + 20),
                               (uint8_t) (button->color));
    }
    else
    {
        SDL_SetRenderDrawColor(mainEngine->gRenderer,
                               (uint8_t) (button->color>>24),
                               (uint8_t) (button->color>>16),
                               (uint8_t) (button->color>>8),
                               (uint8_t) (button->color));
    }
    SDL_RenderFillRect(mainEngine->gRenderer, &(button->area));
    return 0;
}

int ButtonHandle(Button *button, SDL_Event event)
{
    //check if mouse is over button
    if(event.type == SDL_MOUSEMOTION)
    {
        if (event.motion.x >= button->area.x && event.motion.x <= button->area.x + button->area.w
            && event.motion.y >= button->area.y
            && event.motion.y <= button->area.y + button->area.h)
        {
            button->over = true;
        }
        else
            button->over = false;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN && button->over)
    {
        button->clicked = true;
    }

    if (event.type == SDL_MOUSEBUTTONUP && button->clicked && button->over) //removes click inside -- release outside;
    {
        button->released = true;
    }

    return 0;
}

int ButtonSetColor(Button *button, int color)
{
    button->color = color;
    return 0;
}

int ButtonReset(Button *button)
{
    if(button->released || !button->over)   //reset if mouse left button or is UP;
    {
        button->clicked = false;
        button->released = false;
    }

    return 0;
}