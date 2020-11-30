#ifndef TEXTUREANIM_H
#define TEXTUREANIM_H

#include "TexturePack.h"
#include <math.h>

class TextureAnimation
{
public:
    TextureAnimation();
    ~TextureAnimation();
    void render(int x, int y, int frame = NULL);
    void play(float speedMultiplier = 1.0f) { playDirection = speedMultiplier; }
    void stop() { playDirection = 0; }
    void reverse(float speedMultiplier = 1.0f) { playDirection = -speedMultiplier; }
    void setMinMaxCellIds(int minId, int maxId);
    void setTexturePack(TexturePack *texture);
    int getMinCellId() { return minCellId; }
    int getMaxCellId() { return maxCellId; }

private:
    TexturePack *texturepack;
    int minCellId;
    int maxCellId;
    float currentFrame;
    float playDirection;
};

#endif