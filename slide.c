//
// Created by zemuvier on 20/07/15.
//

#include "slide.h"
#include "engine.h"
#include "dragarea.h"


int SliderInit(Slider *slider, int x, int y, int w, int color)
{
    slider->area.x = x;
    slider->area.y = y;
    slider->area.w = w;
    slider->area.h = 1;
    slider->color = color;
    DragAreaInit(&slider->dragArea, x, y - 10, 10, 20, color);

    return 0;
}

int SliderHandle(Slider *slider, SDL_Event event)
{
    DragAreaHandle(&slider->dragArea, event);   //let it do it's thing
    int x, y;
    DragAreaGetDrag(&slider->dragArea, &x, &y); //get results
    slider->dragArea.area.x += x;
    slider->dragArea.drag_begin.x += x;

    if(slider->dragArea.area.x < slider->area.x)    //fix
    {
        slider->dragArea.drag_begin.x += slider->area.x - slider->dragArea.area.x;  //we need to fix this as well
        slider->dragArea.area.x = slider->area.x;
    }

    if(slider->dragArea.area.x > slider->area.x + slider->area.w - slider->dragArea.area.w)
    {
        slider->dragArea.drag_begin.x += slider->area.x + slider->area.w - slider->dragArea.area.w
                                         - slider->dragArea.area.x; //we need to fix this as well
        slider->dragArea.area.x = slider->area.x + slider->area.w - slider->dragArea.area.w;
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

    DragAreaRender(&slider->dragArea);


    return 0;
}

int SliderReset(Slider *slider)
{
    DragAreaReset(&slider->dragArea);
    return 0;
}

float SliderNumber(Slider *slider)
{
    float number = 0.0;
    number = (float) (slider->dragArea.area.x - slider->area.x) / (float) (slider->area.w - slider->dragArea.area.w);
    return number;
}