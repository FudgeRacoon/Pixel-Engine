#include <iostream>
#include <PixelEngine.h>

class script : public pixel::PixelLoop
{
public:
    pixel::Mesh* mesh;

    void GenerateGrid(int size)
    {
        for(int y = -window->GetHeight(); y < window->GetHeight(); y += size)
            for(int x = -window->GetWidth(); x < window->GetWidth(); x += size)
                window->GetFrameBuffer()->DrawPixel(window, x, y, pixel::Color(51, 51, 51, 255));
    }

    void HandleMeshInput()
    {
        if(pixel::Input::GetKeyDown(pixel::PIXELK_1))
            mesh->renderMode = pixel::WIREFRAME;
        else if(pixel::Input::GetKeyDown(pixel::PIXELK_2))
            mesh->renderMode = pixel::SOLID;
        else if(pixel::Input::GetKeyDown(pixel::PIXELK_3))
            mesh->renderMode = pixel::WIREFRAME_AND_SOLID;
        else if(pixel::Input::GetKeyDown(pixel::PIXELK_4))
            mesh->renderOption = pixel::ENABLE_BACKFACECULLING;
        else if(pixel::Input::GetKeyDown(pixel::PIXELK_5))
            mesh->renderOption = pixel::DISABLE_BACKFACECULLING;
    }

public:
    void Setup() override
    {
        window = new pixel::Window("Pixel Engine", 800, 600, SDL_WINDOW_SHOWN, 0, false);

        mesh = new pixel::Mesh();
        mesh->LoadMesh("assets\\cube.obj");
        mesh->scale.x = 200;
        mesh->scale.y = 200;
    }

    void Update() override
    {
        HandleMeshInput();

        mesh->rotation.y += 0.5;
        mesh->rotation.x += 0.5;
        mesh->rotation.z += 0.5;

        mesh->position.z = 3;

        mesh->UpdateMesh();
    }

    void Render() override
    {
        window->GetFrameBuffer()->ClearBuffer(window, pixel::Color::Black());

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
