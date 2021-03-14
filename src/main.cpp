#include <iostream>
#include <PixelEngine.h>

class script : public PixelLoop
{
public:
    pixel::Mesh* mesh;
    float rotation = 0.0;

    void GenerateGrid(int size)
    {
        for(int y = -window->GetHeight(); y < window->GetHeight(); y += size)
            for(int x = -window->GetWidth(); x < window->GetWidth(); x += size)
                window->GetFrameBuffer()->DrawPixel(window, x, y, pixel::Color(51, 51, 51, 255));
    }
public:
    void Setup() override
    {
        window = new pixel::Window("Pixel Engine", 800, 600, SDL_WINDOW_SHOWN, 0, false);

        mesh = new pixel::Mesh();
        mesh->LoadMesh("assets\\cube.obj");
    }

    void ProcessInput(SDL_Event event) override
    {
        switch(event.type)
        {
            case SDL_QUIT:
            {
                delete window;
                break;
            }
            case SDL_KEYDOWN:
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    delete window;
                    break;
                }
                if(event.key.keysym.sym == SDLK_1)
                {
                    mesh->renderMode = pixel::WIREFRAME;
                    break;
                }
                else if(event.key.keysym.sym == SDLK_2)
                {
                    mesh->renderMode = pixel::SOLID;
                    break;
                }
                else if(event.key.keysym.sym == SDLK_3)
                {
                    mesh->renderMode = pixel::WIREFRAME_AND_SOLID;
                    break;
                }
                else if(event.key.keysym.sym == SDLK_4)
                {
                    mesh->renderOption = pixel::ENABLE_BACKFACECULLING;
                    break;
                }
                else if(event.key.keysym.sym == SDLK_5)
                {
                    mesh->renderOption = pixel::DISABLE_BACKFACECULLING;
                    break;
                }
            }
        }
    }

    void Update() override
    {
        //Update Stuff
        mesh->scale.x = 200;
        mesh->scale.y = 200;
        
        mesh->position.x = 0;
        mesh->position.z = 3;

        mesh->UpdateMesh();
    }

    void Render() override
    {
        window->GetFrameBuffer()->ClearBuffer(window, pixel::Color::Black());

        //Render Stuff
        GenerateGrid(10);

        static float c = 0.0;
        pixel::Color red(255, 0, 0, 255);
        pixel::Color blue(0, 0, 255, 255);
        mesh->RenderMesh(window, pixel::Color::Lerp(red, blue, c += 0.005));
        
        window->GetFrameBuffer()->RenderBuffer(window);
    }
}_script;


int main(int argc, char* argv[])
{
    _script.Run();
    
    return 0;
}
