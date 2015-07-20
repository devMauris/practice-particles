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
    engine->bgcolor = 0xdadadaff;

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
    Button colorButton, bigButton;
    DragArea testDrag;
    Slider slider;

    DragAreaInit(&testDrag, 10, 180, 80, 80, 0x0caa0cff);
    SliderInit(&slider, 5, 180, 300, 0x0caa0cff);

    ButtonInit(&colorButton, 0, 0, 32, 24, 0xaaaaaaff);
    ButtonInit(&bigButton, 50, 50, 100, 100, 0xaaaaaaff);

    while(!engine->done) //main loop;
    {
        ButtonReset(&colorButton);
        ButtonReset(&bigButton);
        DragAreaReset(&testDrag);
        SliderReset(&slider);
        //Handle events;
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                engine->done = true;
            }
            ButtonHandle(&colorButton, e);
            ButtonHandle(&bigButton, e);
            DragAreaHandle(&testDrag, e);
            SliderHandle(&slider, &testDrag, e);

        }

        //Render;
        SDL_SetRenderDrawColor(engine->gRenderer,
                               (uint8_t) (engine->bgcolor>>24),
                               (uint8_t) (engine->bgcolor>>16),
                               (uint8_t) (engine->bgcolor>>8),
                               (uint8_t) (engine->bgcolor));
        SDL_RenderClear(engine->gRenderer);


        ButtonRender(&colorButton);
        ButtonRender(&bigButton);

        DragAreaRender(&testDrag);

        SliderRender(&slider);

        if (colorButton.clicked)
            EngineSetBackgroundColor(engine, 0x61ACE1FF);

        if (bigButton.clicked)
            ButtonSetColor(&bigButton, 0xE17F61FF);

        //----------------
        SDL_RenderPresent(engine->gRenderer);
        SDL_Delay(16);
    }
    return 0;
}