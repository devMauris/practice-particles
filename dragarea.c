//
// Created by mauris on 17.07.2015.
//

#include "dragarea.h"
#include "engine.h"

int DragAreaInit(DragArea *dragArea, int x, int y, int w, int h, int color)
{
    dragArea->area.x = x;
    dragArea->area.y = y;
    dragArea->area.w = w;
    dragArea->area.h = h;
    dragArea->color = color;
    dragArea->dragging = dragArea->dragged = false;

    return 0;
}

int DragAreaReset(DragArea *dragArea)
{
    if(!dragArea->dragging)
    {
        dragArea->dragging = false;
        dragArea->dragged = false;
    }
    return 0;
}

int DragAreaGetDrag(DragArea *dragArea, int *x, int *y)
{
    if(dragArea->dragged)
    {
        *x = dragArea->drag_end.x - dragArea->drag_begin.x;
        *y = dragArea->drag_end.y - dragArea->drag_begin.y;
        return 0;
    }
    return 1;
}

int DragAreaHandle(DragArea *dragArea, SDL_Event e)
{
    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x >= dragArea->area.x && x <= dragArea->area.x + dragArea->area.w
            && y >= dragArea->area.y
            && y <= dragArea->area.y + dragArea->area.h)
        {
            dragArea->dragging = true;
            dragArea->dragged = true;
            dragArea->drag_begin.x = x;
            dragArea->drag_begin.y = y;
            dragArea->drag_end = dragArea->drag_begin;
        }
    }

    if(e.type == SDL_MOUSEBUTTONUP)
        dragArea->dragging = false;

    if(e.type == SDL_MOUSEMOTION && dragArea->dragging)
    {
        dragArea->drag_end.x = e.motion.x;
        dragArea->drag_end.y = e.motion.y;
    }

    return 0;
}

int DragAreaRender(DragArea *dragArea)
{
    SDL_SetRenderDrawColor(mainEngine->gRenderer,
                           (uint8_t) (dragArea->color>>24),
                           (uint8_t) (dragArea->color>>16),
                           (uint8_t) (dragArea->color>>8),
                           (uint8_t) (dragArea->color));
    SDL_RenderFillRect(mainEngine->gRenderer, &dragArea->area);


    if (dragArea->dragged)
    {
        SDL_SetRenderDrawColor(mainEngine->gRenderer, 0x4E, 0xFF, 0x4E, 0x9B);
        SDL_RenderDrawLine(mainEngine->gRenderer,
                           dragArea->drag_begin.x, dragArea->drag_begin.y,
                           dragArea->drag_end.x, dragArea->drag_end.y);
    }
    return 0;
}