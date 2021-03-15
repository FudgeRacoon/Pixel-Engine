#include <Pixel_Input.h>

SDL_Event pixel::Input::event;

bool pixel::Input::GetKey(KeyCode key)
{
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == key)
        return true;
    else
        return false;
}

bool pixel::Input::GetKeyUp(KeyCode key)
{
    if(event.type == SDL_KEYUP && event.key.keysym.sym == key)
        return true;
    else
        return false;
}

int pixel::Input::GetMouseScroll()
{
    if(event.type == SDL_MOUSEWHEEL)
    {
        if(event.wheel.y > 0)
            return 1;
        else if(event.wheel.y < 0)
            return -1;
    }
    return 0;
}

pixel::Vec2 pixel::Input::GetMousePosition()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return Vec2(x, y);
}

bool pixel::Input::GetMouseButtonDown(int index)
{
    if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == index)
        return true;
    else
        return false;
}

bool pixel::Input::GetMouseButtonUp(int index)
{
    if(event.type == SDL_MOUSEBUTTONUP && event.button.button == index)
        return true;
    else
        return false;
}