//
// Created by mauris on 14.07.2015.
//

#ifndef SUMMERTIME_ENGINE_H
#define SUMMERTIME_ENGINE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <SDL.h>

#include "spec.h"
#include "button.h"
#include "dragarea.h"

typedef struct
{
    SDL_Window *gWindow;
    SDL_Renderer* gRenderer;
    int width, height, bgcolor;
    bool done;
} Engine;

extern int EngineInit(Engine* engine, int argc, char* args[]); //initialize SDL in main thread
extern int EngineQuit(Engine* engine);
extern int EngineRun(Engine* engine);
extern int EngineSetBackgroundColor(Engine *engine, int color);

extern Engine* mainEngine; //to have access from every module;
#endif //SUMMERTIME_ENGINE_H
