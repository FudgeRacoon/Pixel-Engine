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
                window->GetFrameBuffer()->DrawPixel(window, x, y, 0xFF333333);
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
            }
            case SDL_MOUSEWHEEL:
            {
                if(event.wheel.y > 0)
                {
                    rotation += 1;
                    break;
                }
                else if(event.wheel.y < 0)
                {
                    rotation += -1;
                    break;
                }
                else if(event.wheel.y == 0)
                {
                    rotation += 0;
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
    
        mesh->rotation.x += rotation * pixel::Time::DeltaTime();
        mesh->rotation.y += rotation * pixel::Time::DeltaTime();
        mesh->transform.z = 3;

        mesh->UpdateMesh();
    }

    void Render() override
    {
        window->GetFrameBuffer()->ClearBuffer(window, 0xFF000000);

        //Render Stuff
        GenerateGrid(10);
        mesh->RenderMesh(window, 0xFFFF0000);
        
        window->GetFrameBuffer()->RenderBuffer(window);
    }
}_script;

int main(int argc, char* argv[])
{
    _script.Run();

    return 0;
}