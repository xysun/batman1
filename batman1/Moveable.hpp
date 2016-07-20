//
//  Moveable.hpp
//  batman1
//
//  Created by Sun, Joy (Agoda) on 7/20/2559 BE.
//  Copyright © 2559 Xiayun Sun. All rights reserved.
//

#ifndef Moveable_hpp
#define Moveable_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

#endif /* Moveable_hpp */

class Moveable{
    
public:
    Moveable();
    
    virtual void handleEvent(SDL_Event& e) = 0;
    
    virtual void render(int x, int y) = 0;
    
    virtual void loadMedia() = 0;
    
    virtual void close() = 0;
    
private:
    int mPosX, mPosY;
    
};