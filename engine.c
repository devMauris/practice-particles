//
// Created by mauris on 14.07.2015.
//

#include "engine.h"
#include "button.h"

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


    engine->gWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, engine->width, engine->height, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
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

int ChangeColorBack(Engine *e, int a, int b, int c)
{
    SDL_SetRenderDrawColor(e->gRenderer, a, b, c, 0xFF);
    SDL_RenderClear(e->gRenderer);
    return 0;
}


int EngineRun(Engine* engine)
{
    SDL_Event e;
    Button exitButton, colorButton, bigButton;
    ButtonInit(&exitButton, engine->width-32, 0, 32, 24);
    ButtonInit(&colorButton, 0, 0, 32, 24);
    ButtonInit(&bigButton, 50, 50, 100, 100);

    while(!engine->done) //main loop;
    {
        //Handle events;
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                engine->done = true;
            }
            ButtonHandle(&exitButton, e);
            ButtonHandle(&colorButton, e);
            ButtonHandle(&bigButton, e);

        }

        if(exitButton.clicked) //exit from the programm
            engine->done = true;

        //Render;
        ChangeColorBack(engine, 0xAF, 0xAF, 0xAF);


        if (colorButton.clicked) //change the color of background
        {
            ChangeColorBack(engine, 0x61, 0xAC, 0xE1);
        }

        ButtonRender(&exitButton);
        ButtonRender(&colorButton);
        ButtonRender(&bigButton);

        if (bigButton.clicked) //change the color of this button
        {
           ChangeColorButton(&bigButton, 0xE1, 0x7F, 0x61);
        }

        //----------------
        SDL_RenderPresent(engine->gRenderer);
        SDL_Delay(16);
    }
    return 0;
}