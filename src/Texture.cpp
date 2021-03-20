#include <Pixel_Texture.h>
#include <Pixel_FrameBuffer.h>
#include <Pixel_Color.h>

pixel::Texture::Texture() : textureBuffer(nullptr) {}

pixel::Texture::~Texture()
{
    delete[] textureBuffer;
}

int pixel::Texture::GetWidth() const
{
    return width;
}

int pixel::Texture::GetHeight() const
{
    return height;
}

void pixel::Texture::LoadTexture(const char* filepath)
{
    SDL_Surface* image = IMG_Load(filepath);
    SDL_Surface* formattedImage = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);

    textureBuffer = new uint32[formattedImage->w * formattedImage->h];

    width = formattedImage->w;
    height = formattedImage->h;

    SDL_LockSurface(formattedImage);

    Uint32* pixels = (Uint32*)formattedImage->pixels;

    memcpy(textureBuffer, pixels, formattedImage->pitch * formattedImage->h);
    
    SDL_UnlockSurface(formattedImage);

    SDL_FreeSurface(image);
    SDL_FreeSurface(formattedImage);    
}

void pixel::Texture::Render(Window* window, int x, int y)
{   
    try
    {
        if(textureBuffer == nullptr)
            throw new std::runtime_error("[ERROR]: There are no data to render");
    }
    catch(const std::runtime_error*& e)
    {
        e->what();
        abort();
    }

    for(int _y = 0; _y < height; _y++)
        for(int _x = 0; _x < width; _x++)
        {
            uint32 pixel = textureBuffer[(width * _y) + _x];
            Color color = Color::HextoRGB(pixel);
            window->GetFrameBuffer()->DrawPixel(window, x + _x, y - _y, color);
        }        
}

void pixel::Texture::Destroy()
{
    delete[] textureBuffer;
}