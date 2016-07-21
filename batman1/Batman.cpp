//
//  Batman.cpp
//  batman1
//
//  Created by Sun, Joy (Agoda) on 7/20/2559 BE.
//  Copyright © 2559 Xiayun Sun. All rights reserved.
//

#include "Batman.hpp"

Batman::Batman(SDL_Renderer* inRenderer){
    
    renderer = inRenderer;
    state = standing;
}

void Batman::loadMedia(){
    // running, only loading sprite 2 to 8
    for (int i = 0; i < RUNNING_ANIMATION_FRAMES; i++) {
        runningSprites[i].loadFromFile("media/sprites/batman-running-" + std::to_string(i+2) + ".png", renderer);
    }
    // standing
    standingSprite.loadFromFile("media/sprites/batman-standing.png", renderer);
    
}

void Batman::close(){
    for (int i = 0; i < RUNNING_ANIMATION_FRAMES; i++) {
        runningSprites[i].free();
    }
    standingSprite.free();
}

void Batman::renderRunning(int x, int y){
    
    runningSprites[currFrameRunning / FRAME_CONTROLLER].render(x,y, renderer);
    
    ++currFrameRunning;
    
    if (currFrameRunning / FRAME_CONTROLLER >= RUNNING_ANIMATION_FRAMES) {
        currFrameRunning = 0;
    }
}

void Batman::renderStanding(int x, int y){
    standingSprite.render(x, y, renderer);
}

void Batman::render(int x, int y){
    switch (state) {
        case running:
            renderRunning(x, y);
            break;
        case standing:
            renderStanding(x, y);
            break;
        default:
            renderRunning(x, y);
            break;
    }
}

bool Batman::isMovingFwd(){
    
    bool res = false;
    
    switch (state) {
        case running:
            res = true;
            break;
            
        case standing:
            res = false;
            break;
            
        default:
            break;
    }
    
    return res;
}