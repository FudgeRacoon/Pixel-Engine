#include <Pixel_Window.h>
#include <Pixel_FrameBuffer.h>

pixel::Window::Window(char* name, uint16_t width, uint16_t height, uint32_t windowFlag, uint32_t rendererFlag, bool isFullscreen)
{    
        //Initalize SDL
        try
        {
            if(SDL_Init(SDL_INIT_EVERYTHING) != 0 )
                throw new std::runtime_error("Error initializing SDL");
        }
        catch(const std::runtime_error*& e)
        {
            std::cout << e->what() << std::endl;
            abort();
        }

        this->name = name;

        if(isFullscreen)
        {
            SDL_DisplayMode displayMode;
            SDL_GetCurrentDisplayMode(0, &displayMode);
            this->width = displayMode.w;
            this->height = displayMode.h;
        }
        else
        {
            this->width = width;
            this->height = height;
        }
       
        //Create Window
        SDL_Window* window = SDL_CreateWindow
        (
            name, 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            this->width, 
            this->height, 
            isFullscreen ? SDL_WINDOW_FULLSCREEN : windowFlag
        );
        this->window = window;

        //Handle Window Error
        try
        {
            if(window == nullptr)
                throw new std::runtime_error("Error creating window");
        }
        catch(const std::runtime_error*& e)
        {
            std::cout << e->what() << std::endl;
            abort();
        }

        //Create Renderer
        SDL_Renderer* renderer = SDL_CreateRenderer
        (
            window, 
            -1, 
            rendererFlag
        );
        this->renderer = renderer;

        //Handle Renderer Error
        try
        {
            if(renderer == nullptr)
                throw new std::runtime_error("Error creating renderer");
        }
        catch(const std::runtime_error*& e)
        {
            std::cout << e->what() << std::endl;
            abort();
        }

        isRunning = true;

        frameBuffer = new FrameBuffer(this);
}
pixel::Window::~Window()
{
    isRunning = false;
    delete frameBuffer;
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}

char* pixel::Window::GetName()
{
    return this->name;
}
uint16_t pixel::Window::GetWidth()
{
    return this->width;
}
uint16_t pixel::Window::GetHeight()
{
    return this->height;
}

bool pixel::Window::IsRunning()
{
    return isRunning;
}

SDL_Window* pixel::Window::GetWindow()
{
    return this->window;
}
SDL_Renderer* pixel::Window::GetRenderer()
{
    return this->renderer;
}
pixel::FrameBuffer* pixel::Window::GetFrameBuffer()
{
    return this->frameBuffer;
}