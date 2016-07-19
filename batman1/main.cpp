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
#include "LTexture.hpp"

void init();
void loadMedia();
void close();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int FRAME_CONTROLLER = 8;

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;

const int RUNNING_ANIMATION_FRAMES = 7;
LTexture gRunningSpriteTextures[RUNNING_ANIMATION_FRAMES];

LTexture gBackGroundTexture;


void init(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    
    gWindow = SDL_CreateWindow("batman 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    IMG_Init(IMG_INIT_PNG);
    
}

void loadMedia(){
    // only loading sprite 2 to 8
    for (int i = 0; i < RUNNING_ANIMATION_FRAMES; i++) {
        gRunningSpriteTextures[i].loadFromFile("media/sprites/batman-running-" + std::to_string(i+2) + ".png", gRenderer);
    }
    
    // load background
    gBackGroundTexture.loadFromFile("media/gotham.jpg", gRenderer);
}

void close(){
    for (int i = 0; i < RUNNING_ANIMATION_FRAMES; i++) {
        gRunningSpriteTextures[i].free();
    }
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
        }
        
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        
        // load background first with offset
        -- scrollingOffset;
        if (scrollingOffset < -gBackGroundTexture.getWidth()) {
            scrollingOffset = 0;
        }
        gBackGroundTexture.render(scrollingOffset, 0, gRenderer);
        gBackGroundTexture.render(scrollingOffset + gBackGroundTexture.getWidth(), 0, gRenderer);
        
        gRunningSpriteTextures[frame / FRAME_CONTROLLER].render(50, SCREEN_HEIGHT - 60, gRenderer); // TODO
        
        SDL_RenderPresent(gRenderer);
        
        ++frame;
        
        if (frame / FRAME_CONTROLLER >= RUNNING_ANIMATION_FRAMES) {
            frame = 0;
        }
    }
    
    
    return 0;
}
