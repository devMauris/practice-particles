//
// Created by zemuvier on 17.07.2015.
//

#ifndef SUMMERTIME_BUTTON_H
#define SUMMERTIME_BUTTON_H

#include <stdbool.h>
#include <SDL.h>

typedef struct
{
    SDL_Rect area;
    bool clicked, released, over;
    int color;
} Button;

extern int ButtonInit(Button *button, int x, int y, int w, int h, int color);
extern int ButtonRender(Button *button);
extern int ButtonHandle(Button *button, SDL_Event event);
extern int ButtonSetColor(Button *but, int color);
extern int ButtonReset(Button *button);


#endif //SUMMERTIME_BUTTON_H