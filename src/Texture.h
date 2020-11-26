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

    bool loadFromFile(std::string path);
    void free();
    void render(int x, int y, SDL_Rect *clip = NULL);
    int getWidth() { return width; }
    int getHeight() { return height; }
    void setRenderer(SDL_Renderer *renderer);
    void setKeyColor(Uint8 R, Uint8 G, Uint8 B);
    void setModColor(Uint8 R, Uint8 G, Uint8 B);
    void setBlendMode(SDL_BlendMode blendMode);
    void setAlpha(Uint8 alpha);

private:
    SDL_Texture *sdlTexture;
    SDL_Renderer *sdlRenderer;
    int width;
    int height;
    Uint8 keyR;
    Uint8 keyG;
    Uint8 keyB;

    bool checkRenderer();
};

#endif