//
//  main.cpp
//  batman1
//  Copyright © 2559 Xiayun Sun. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include "Batman.hpp"
#include "GameState.h"

void init();
void loadMedia();
void close();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;

LTexture gBackGroundTexture;

Batman* batman = NULL;

GameState gameState;

void init(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    
    gWindow = SDL_CreateWindow("batman 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    batman = new Batman(gRenderer);
    
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    IMG_Init(IMG_INIT_PNG);
    
}

void loadMedia(){
    
    batman->loadMedia();
    
    // load background
    gBackGroundTexture.loadFromFile("media/gotham.jpg", gRenderer);
    
    // load game file
    SDL_RWops* file = SDL_RWFromFile("gamestates/01.bin", "r+b");
    if (file == NULL) {
        printf("game state file not exist!\n");
        file = SDL_RWFromFile("gamestates/01.bin", "w+b");
        printf("new game state file created!\n");
        gameState.scrollingOffset = 0;
        SDL_RWwrite(file, &gameState, sizeof(gameState), 1);
        SDL_RWclose(file);
    }
    else{
        printf("previous game state found, reading file..\n");
        SDL_RWread(file, &gameState, sizeof(gameState), 1);
        SDL_RWclose(file);
    }
}

void close(){
    
    // save game state
    SDL_RWops* file = SDL_RWFromFile("gamestates/01.bin", "w+b");
    if (file != NULL) {
        SDL_RWwrite(file, &gameState, sizeof(gameState), 1);
        printf("game state saved! \n");
        SDL_RWclose(file);
    }
    else{
        printf("fail to save game state! \n");
    }
    
    batman->close();
    
    gBackGroundTexture.free();
    
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
    
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, const char * argv[]) {
    init();
    loadMedia();
    
    bool quit = false;
    
    SDL_Event e;
    
    int frame = 0;
    
    int scrollingOffset = gameState.scrollingOffset;
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            batman->handleEvent(e);
        }
        
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        
        // load background first with offset
        if (batman->isMovingFwd()) {
            -- scrollingOffset;
            if (scrollingOffset < -gBackGroundTexture.getWidth()) {
                scrollingOffset = 0;
            }
        }
        
        gBackGroundTexture.render(scrollingOffset, 0, gRenderer);
        gBackGroundTexture.render(scrollingOffset + gBackGroundTexture.getWidth(), 0, gRenderer);
        
        batman->render(50, SCREEN_HEIGHT - 60);
        
        SDL_RenderPresent(gRenderer);
    }
    
    // save game state
    gameState.scrollingOffset = scrollingOffset;
    printf("saving game state: scrolling offset %d\n", gameState.scrollingOffset);
    
    // close
    close();
    
    
    return 0;
}
