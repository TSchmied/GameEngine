#include "TextureAnimation.h"

TextureAnimation::TextureAnimation()
{
    texturepack = NULL;
    minCellId = 0;
    maxCellId = 0;
    currentFrame = 0.0f;
    playDirection = 1.0f;
}
TextureAnimation::~TextureAnimation()
{
    texturepack = NULL;
}
void TextureAnimation::render(int x, int y, int frame)
{
    int fframe = floor(currentFrame);
    if (frame != NULL)
        fframe = frame;
    texturepack->render(x, y, fframe);

    currentFrame += playDirection;
    if (floor(currentFrame) > maxCellId)
        currentFrame = minCellId;
    else if (floor(currentFrame) < minCellId)
        currentFrame = maxCellId;
}
void TextureAnimation::setMinMaxCellIds(int minId, int maxId)
{
    if (minId != NULL)
        minCellId = minId;
    if (maxId != NULL)
        maxCellId = maxId;
}
void TextureAnimation::setTexturePack(TexturePack *texture)
{
    texturepack = texture;
}