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
}

void close(){
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
    
    int scrollingOffset = 0;
    
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
