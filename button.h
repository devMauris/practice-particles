//
// Created by zemuvier on 16.07.2015.
//

#ifndef SUMMERTIME_BUTTON_H
#define SUMMERTIME_BUTTON_H

#include <stdbool.h>
#include <SDL.h>

typedef struct
{
    SDL_Rect area;
    bool click;
} Button;

extern int ButtonInit(Button *button, int x, int y, int w, int h);
extern int ButtonRender(Button *button);
extern int ButtonHandle(Button *button, SDL_Event event);

#endif //SUMMERTIME_BUTTON_H