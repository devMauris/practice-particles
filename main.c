//
// Created by mauris on 14.07.2015.
//

#include "engine.h"

int main(int argc, char* args[])
{
    mainEngine = malloc(sizeof(Engine));
    EngineInit(mainEngine, argc, args);//init

    EngineRun(mainEngine);

    EngineQuit(mainEngine);
    free(mainEngine);
    return 0;
}