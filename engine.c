//
// Created by mauris on 14.07.2015.
// Created by zemuvier on 17.07.2015.
//

#include "engine.h"
#include "button.h"
#include "dragarea.h"
#include "slide.h"

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
    engine->bgcolor = 0xaaaaaaff;

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


    engine->gWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       engine->width, engine->height,
                                       SDL_WINDOW_SHOWN);
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

int EngineSetBackgroundColor(Engine *engine, int color)
{
    engine->bgcolor = color;
    return 0;
}

int EngineRun(Engine* engine)
{
    SDL_Event e;
    Slider sliderR, sliderG, sliderB;

    SliderInit(&sliderR, 55, 80, 300, 0xAA0000FF);
    SliderInit(&sliderG, 55, 110, 300, 0x00AA00FF);
    SliderInit(&sliderB, 55, 140, 300, 0x0000AAFF);


    while(!engine->done) //main loop;
    {
        SliderReset(&sliderR);
        SliderReset(&sliderG);
        SliderReset(&sliderB);
        //Handle events;
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                engine->done = true;
            }
            SliderHandle(&sliderR, e);
            SliderHandle(&sliderG, e);
            SliderHandle(&sliderB, e);

        }

        //Render;
        SDL_SetRenderDrawColor(engine->gRenderer,
                               (uint8_t) (engine->bgcolor>>24),
                               (uint8_t) (engine->bgcolor>>16),
                               (uint8_t) (engine->bgcolor>>8),
                               (uint8_t) (engine->bgcolor));
        SDL_RenderClear(engine->gRenderer);


        SliderRender(&sliderR);
        SliderRender(&sliderG);
        SliderRender(&sliderB);


        EngineSetBackgroundColor(engine, (int)(SliderNumber(&sliderR) * 0xff)<<24|(int)(SliderNumber(&sliderG) * 0xff)<<16
                              |(int)(SliderNumber(&sliderB) * 0xff)<<8 | 0xff);


        //----------------
        SDL_RenderPresent(engine->gRenderer);
        SDL_Delay(16);
    }
    return 0;
}

unsigned int TimerGetPassed(unsigned int time)
{
    return SDL_GetTicks() - time;
}

unsigned int TimerInit()
{
    return SDL_GetTicks();
}

int NanoTimerInit()
{
    return (Uint64)SDL_GetPerformanceCounter() * 1000000000;
}

unsigned int NanoTimerGetPassed(unsigned int time)
{
    return (Uint64)((SDL_GetPerformanceCounter() - time)/SDL_GetPerformanceFrequency() * 1000000000);
}