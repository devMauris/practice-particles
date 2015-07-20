//
// Created by zemuvier on 20/07/15.
//

#ifndef SUMMERTIME_SLIDE_H
#define SUMMERTIME_SLIDE_H

#include <stdbool.h>
#include <SDL.h>
#include "dragarea.h"

typedef struct
{
    SDL_Rect area;
    DragArea dragArea;
    int color;
} Slider;

extern int SliderInit(Slider *slider, int x, int y, int w, int color);
extern int SliderHandle(Slider *slider, SDL_Event event);
extern int SliderRender(Slider *slider);
extern int SliderReset(Slider *slider);

#endif //SUMMERTIME_SLIDE_H
