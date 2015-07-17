//
// Created by mauris on 17.07.2015.
//

#ifndef SUMMERTIME_DRAGAREA_H
#define SUMMERTIME_DRAGAREA_H

#include <SDL.h>
#include <stdbool.h>

typedef struct
{
    SDL_Rect area;
    bool dragging, dragged;
    SDL_Point drag_begin, drag_end;
    int color;
} DragArea;


extern int DragAreaInit(DragArea *dragArea, int x, int y, int w, int h, int color);
extern int DragAreaReset(DragArea *dragArea);
extern int DragAreaGetDrag(DragArea *dragArea, int *x, int *y);
extern int DragAreaHandle(DragArea *dragArea, SDL_Event e);
extern int DragAreaRender(DragArea *dragArea);
extern int DragAreaSetColor(DragArea *dragArea, int color);

#endif //SUMMERTIME_DRAGAREA_H
