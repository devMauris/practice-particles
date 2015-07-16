//
// Created by mauris on 14.07.2015.
//
#include "button.h"
#include "engine.h"

Engine* mainEngine; //to have access from every module;

int EngineInit(Engine* engine, int argc, char* args[]) //initialize SDL in main thread
{
    //Analyze starting parameters;
    for(int i =0; i<argc; i++)
    {
        printf("%s\n", args[i]);
    }

    engine->width = 640;
    engine->height = 480;

    //Init SDL 2;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    int nameLength = strlen(spec_productName) + strlen(spec_version) + 1;
    char *name = malloc(nameLength);
    memset(name, '\0' , nameLength);
    strncat(name, spec_productName, nameLength - strlen(name) - 1);
    strncat(name, spec_version, nameLength - strlen(name)- 1);


    engine->gWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, engine->width, engine->height, SDL_WINDOW_SHOWN);
    if( engine->gWindow == NULL )
    {
        printf("Can't create window! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    free(name);

    engine->gRenderer = SDL_CreateRenderer(engine->gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(engine->gRenderer == NULL)
    {
        printf("Can't create renderer! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetRenderDrawColor(engine->gRenderer, 0xAF, 0xAF, 0xAF, 0xFF);

    engine->done = false;
    return 0;
}

int EngineQuit(Engine* engine)
{
    if(engine->gRenderer != NULL)
        SDL_DestroyRenderer(engine->gRenderer);
    if(engine->gWindow != NULL)
        SDL_DestroyWindow(engine->gWindow);

    SDL_Quit();
    return 0;
}

int EngineRun(Engine* engine)
{
    SDL_Event e;
    ButtonClick(e);
    while(!engine->done)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                engine->done = true;
            }
        }
        SDL_SetRenderDrawColor(engine->gRenderer, 0xAF, 0xAF, 0xAF, 0xAF);
        SDL_RenderClear(engine->gRenderer);
        SDL_Rect butt = {20, 20, 40, 40};
        SDL_SetRenderDrawColor(engine->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(engine->gRenderer, &butt);
        SDL_RenderPresent(engine->gRenderer);
        SDL_Delay(16);
    }
    return 0;
}