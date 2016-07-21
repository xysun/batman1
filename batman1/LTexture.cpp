//
//  LTexture.cpp
//  batman1
//
//  Created by Sun, Joy (Agoda) on 7/19/2559 BE.
//  Copyright © 2559 Xiayun Sun. All rights reserved.
//

#include "LTexture.hpp"
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL.h>

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

void LTexture::loadFromFile(std::string path, SDL_Renderer* renderer){
    
    //printf("loading image from: %s\n", path.c_str());
    
    free();
    
    SDL_Texture* newTexture = NULL;
    
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    
    SDL_FreeSurface(loadedSurface);
    
    mTexture = newTexture;
    
}

void LTexture::render(int x, int y, SDL_Renderer* renderer){
    SDL_Rect renderQuad = {x,y,mWidth,mHeight};
    
    SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}

