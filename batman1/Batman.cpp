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

Batman::Batman(){
    renderer = NULL;
    state = standing;
}

void Batman::loadMedia(){
    // only loading sprite 2 to 8
    for (int i = 0; i < RUNNING_ANIMATION_FRAMES; i++) {
        runningSprites[i].loadFromFile("media/sprites/batman-running-" + std::to_string(i+2) + ".png", renderer);
    }
}

void Batman::close(){
    for (int i = 0; i < RUNNING_ANIMATION_FRAMES; i++) {
        runningSprites[i].free();
    }
}

void Batman::renderRunning(int x, int y){
    
    runningSprites[currFrameRunning / FRAME_CONTROLLER].render(x,y, renderer);
    
    ++currFrameRunning;
    
    if (currFrameRunning / FRAME_CONTROLLER >= RUNNING_ANIMATION_FRAMES) {
        currFrameRunning = 0;
    }
}

void Batman::render(int x, int y){
    switch (state) {
        case running:
            renderRunning(x, y);
        default:
            renderRunning(x, y);
            break;
    }
}