#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>

class Texture
{
public:
    Texture();
    ~Texture();

    void setRenderer(SDL_Renderer *renderer);
    bool loadFromFile(std::string path);
    void free();
    void render(int x, int y);
    int getWidth() { return width; }
    int getHeight() { return height; }

private:
    SDL_Texture *sdlTexture;
    SDL_Renderer *sdlRenderer;
    int width;
    int height;

    bool checkRenderer();
};

#endif