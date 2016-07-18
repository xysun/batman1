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

void init();
void loadMedia();
void close();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FRAME_CONTROLLER = 8;

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;

class LTexture{
public:
    LTexture();
    ~LTexture();
    
    void loadFromFile(std::string path);
    
    void free();
    
    void render(int x, int y);
    
    int getWidth() {return mWidth;};
    int getHeight() {return mHeight;};
    
private:
    SDL_Texture* mTexture;
    
    int mWidth;
    int mHeight;
    
};

LTexture::LTexture(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture(){
    free();
}

void LTexture::free(){
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mHeight = 0;
        mWidth = 0;
    }
}

void LTexture::loadFromFile(std::string path){
    
    printf("loading image from: %s\n", path.c_str());
    
    free();
    
    SDL_Texture* newTexture = NULL;
    
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    
    SDL_FreeSurface(loadedSurface);
    
    mTexture = newTexture;
    
}

void LTexture::render(int x, int y){
    SDL_Rect renderQuad = {x,y,mWidth,mHeight};
    
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

const int RUNNING_ANIMATION_FRAMES = 7;
LTexture gRunningSpriteTextures[RUNNING_ANIMATION_FRAMES];


void init(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    
    gWindow = SDL_CreateWindow("batman 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    IMG_Init(IMG_INIT_PNG);
    
}

void loadMedia(){
    for (int i = 0; i < RUNNING_ANIMATION_FRAMES; i++) {
        gRunningSpriteTextures[i].loadFromFile("media/sprites/batman-running-" + std::to_string(i+2) + ".png");
    }
}

void close(){
    for (int i = 0; i < RUNNING_ANIMATION_FRAMES; i++) {
        gRunningSpriteTextures[i].free();
    }
    
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
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        
        gRunningSpriteTextures[frame / FRAME_CONTROLLER].render(50, 50); // TODO
        
        SDL_RenderPresent(gRenderer);
        
        ++frame;
        
        if (frame / FRAME_CONTROLLER >= RUNNING_ANIMATION_FRAMES) {
            frame = 0;
        }
    }
    
    
    return 0;
}
