#ifndef PIXEL_TEXTURE_H
#define PIXEL_TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Pixel_Window.h>
#include <Pixel_Color.h>

namespace pixel
{
    class Texture
    {
    private:
        Uint32* textureBuffer;

    private:
        int width;
        int height;

    public:
        Color color;

    public:
        Texture();
        ~Texture();

    public:
        int GetWidth() const;
        int GetHeight() const;

    public:
        void LoadTexture(const char* filepath);

    public:
        void Render(Window* window, int x, int y);

    public:
        void Destroy();
    };
};

#endif