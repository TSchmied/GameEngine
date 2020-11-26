#include "Texture.h"

Texture::Texture()
{
    sdlTexture = NULL;
    sdlRenderer = NULL;
    width = 0;
    height = 0;
    keyR = 255;
    keyG = 0;
    keyB = 200;
}
Texture::~Texture()
{
    free();
}
void Texture::setRenderer(SDL_Renderer *renderer)
{
    sdlRenderer = renderer;
}
void Texture::setKeyColor(Uint8 R, Uint8 G, Uint8 B)
{
    keyR = R;
    keyG = G;
    keyB = B;
}
void Texture::setModColor(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_SetTextureColorMod(sdlTexture, R, G, B);
}
void Texture::setBlendMode(SDL_BlendMode blendMode)
{
    SDL_SetTextureBlendMode(sdlTexture, blendMode);
}
void Texture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(sdlTexture, alpha);
}

bool Texture::loadFromFile(std::string path)
{
    if (!Texture::checkRenderer())
        return false;

    free();

    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, keyR, keyG, keyB));
    if ((newTexture = SDL_CreateTextureFromSurface(sdlRenderer, loadedSurface)) == NULL)
    {
        printf("Unable to create texture from %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }
    width = loadedSurface->w;
    height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    sdlTexture = newTexture;
    return true;
}
void Texture::free()
{
    if (sdlTexture != NULL)
    {
        SDL_DestroyTexture(sdlTexture);
        sdlTexture = NULL;
        width = 0;
        height = 0;
    }
}
void Texture::render(int x, int y, SDL_Rect *clip)
{
    if (!Texture::checkRenderer())
        return;
    SDL_Rect renderQuad = {x, y, width, height};
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(sdlRenderer, sdlTexture, clip, &renderQuad);
}
bool Texture::checkRenderer()
{
    if (sdlRenderer == NULL)
    {
        printf("Texture error: No renderer has been set!\n");
        return false;
    }
    return true;
}