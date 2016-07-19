//
//  LTexture.hpp
//  batman1
//
//  Created by Sun, Joy (Agoda) on 7/19/2559 BE.
//  Copyright © 2559 Xiayun Sun. All rights reserved.
//

#ifndef LTexture_hpp
#define LTexture_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>

#endif /* LTexture_hpp */

class LTexture{
public:
    LTexture();
    ~LTexture();
    
    void loadFromFile(std::string path, SDL_Renderer* renderer);
    
    void free();
    
    void render(int x, int y, SDL_Renderer* renderer);
    
    int getWidth() {return mWidth;};
    int getHeight() {return mHeight;};
    
private:
    SDL_Texture* mTexture;
    
    int mWidth;
    int mHeight;
    
};
