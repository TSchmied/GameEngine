#ifndef TEXTUREPACK_H
#define TEXTUREPACK_H

#include "Texture.h"
#include <SDL.h>
#include <math.h>

class TexturePack : public Texture
{
public:
    TexturePack();
    void setCellSize(int width, int height);
    void setCellId(int cellId);
    void render(int x, int y);
    void render(int x, int y, int cellId);

private:
    int cellWidth;
    int cellHeight;
    int cellsPerRow;
    int cellId;
    SDL_Rect cellRect;
};

#endif