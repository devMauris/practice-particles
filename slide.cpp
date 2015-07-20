//
// Created by zemuvier on 20/07/15.
//

#include "slide.h"
#include "engine.h"
#include "dragarea.h"
#include "button.h"

int SliderInit(Slider *slider, int x, int y, int w, int color)
{
    slider->area.x = x;
    slider->area.y = y;
    slider->area.w = w;
    slider->click = false;
    slider->upclick = false;
    slider->color = color;
    return 0;
}

int SliderHandle(Slider *slider, DragArea *dragArea, SDL_Event event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int a, b;
        SDL_GetMouseState(&a, &b);
        if (a >= dragArea->area.x && a <= dragArea->area.x + dragArea->area.w //if we pressed in the drag'area
            && b >= dragArea->area.y
            && b <= dragArea->area.y + dragArea->area.h)
        {
            slider->click = true;
            slider->upclick = true;
            dragArea->drag_begin.x = a;
            dragArea->drag_begin.y = b;
            dragArea->drag_end = dragArea->drag_begin;
        }
    }
    if (event.type == SDL_MOUSEBUTTONUP)
    {
        slider->click = false;
    }

    if (event.type == SDL_MOUSEMOTION && slider->click == true)
    {
        dragArea->drag_end.x = event.motion.x;
        dragArea->drag_end.y = event.motion.y;

        if (dragArea->drag_end.x > slider->area.x && dragArea->drag_end.x < slider->area.x + slider->area.w) //if slide on the line
        {
            dragArea->area.x = dragArea->drag_end.x;
        }

        if (dragArea->drag_end.x <= slider->area.x) //from the area on the right
        {
            dragArea->drag_begin.x = slider->area.x;
        }

        if (dragArea->drag_begin.x >= slider->area.x + slider->area.w)//on the left
        {
            dragArea->drag_begin.x = slider->area.x + slider->area.w;
        }
    }

    return 0;
}

int SliderRender(Slider *slider)
{
    SDL_SetRenderDrawColor(mainEngine->gRenderer,
                           (uint8_t) (slider->color>>24),
                           (uint8_t) (slider->color>>16),
                           (uint8_t) (slider->color>>8),
                           (uint8_t) (slider->color));
    SDL_RenderFillRect(mainEngine->gRenderer, &slider->area);


    return 0;
}

int SliderReset(Slider *slider)
{
    if (slider->upclick || !slider->click)
    {
        slider->upclick = false;
        slider->click = false;
    }
    return 0;
}
