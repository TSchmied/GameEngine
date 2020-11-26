#include "TexturePack.h"

TexturePack::TexturePack()
{
    cellWidth = 64;
    cellHeight = 64;
    cellId = 0;
    cellsPerRow = 16;
    cellRect = {0, 0, 64, 64};
}

void TexturePack::setCellSize(int width, int height)
{
    if (width != NULL)
        cellWidth = width;
    if (height != NULL)
        cellHeight = height;
}
void TexturePack::setCellId(int id)
{
    cellId = id;
    int cellX = (id % cellsPerRow) * cellWidth;
    int cellY = floor(id / cellsPerRow) * cellHeight;
    cellRect = {cellX, cellY, cellWidth, cellHeight};
}
void TexturePack::render(int x, int y)
{
    Texture::render(x, y, &cellRect);
}
void TexturePack::render(int x, int y, int cellId)
{
    int cellX = (cellId % cellsPerRow) * cellWidth;
    int cellY = floor(cellId / cellsPerRow) * cellHeight;
    SDL_Rect tempRect = {cellX, cellY, cellWidth, cellHeight};
    Texture::render(x, y, &tempRect);
}