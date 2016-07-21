//
//  Batman.hpp
//  batman1
//
//  Created by Sun, Joy (Agoda) on 7/20/2559 BE.
//  Copyright © 2559 Xiayun Sun. All rights reserved.
//

#ifndef Batman_hpp
#define Batman_hpp

#include <stdio.h>
#include "Moveable.hpp"
#include <SDL2/SDL.h>
#include "LTexture.hpp"

#endif /* Batman_hpp */

enum BatmanStates{
    standing,
    running
};

class Batman: public Moveable{
public:
    
    const static int RUNNING_ANIMATION_FRAMES = 7;
    const int FRAME_CONTROLLER = 8;
    
    void handleEvent(SDL_Event& e);
    
    void render(int x, int y);
    
    Batman(SDL_Renderer* renderer);
    
    void loadMedia();
    void close();
    
    bool isMovingFwd();
    
    
private:
    
    LTexture runningSprites[RUNNING_ANIMATION_FRAMES];
    LTexture standingSprite;
    
    SDL_Renderer* renderer;
    
    int currFrameRunning = 0;
    
    BatmanStates state;
    
    void renderRunning(int x, int y);
    void renderStanding(int x, int y);
    
};