#ifndef PIXEL_INPUT_H
#define PIXEL_INPUT_H

#include <Pixel_PixelLoop.h>
#include <Pixel_Vector.h>
#include <SDL2/SDL.h>

namespace pixel
{
    enum KeyCode
    {
        PIXELK_0 = '0',
        PIXELK_1 = '1',
        PIXELK_2 = '2',
        PIXELK_3 = '3',
        PIXELK_4 = '4',
        PIXELK_5 = '5',
        PIXELK_6 = '6',
        PIXELK_7 = '7',
        PIXELK_8 = '8',
        PIXELK_9 = '9',

        PIXELK_a = 'a',
        PIXELK_b = 'b',
        PIXELK_c = 'c',
        PIXELK_d = 'd',
        PIXELK_e = 'e',
        PIXELK_f = 'f',
        PIXELK_g = 'g',
        PIXELK_h = 'h',
        PIXELK_i = 'i',
        PIXELK_j = 'j',
        PIXELK_k = 'k',
        PIXELK_l = 'l',
        PIXELK_m = 'm',
        PIXELK_n = 'n',
        PIXELK_o = 'o',
        PIXELK_p = 'p',
        PIXELK_q = 'q',
        PIXELK_r = 'r',
        PIXELK_s = 's',
        PIXELK_t = 't',
        PIXELK_u = 'u',
        PIXELK_v = 'v',
        PIXELK_w = 'w',
        PIXELK_x = 'x',
        PIXELK_y = 'y',
        PIXELK_z = 'z',

        PIXELK_RETURN = '\r',
        PIXELK_ESCAPE = '\033',
        PIXELK_BACKSPACE = '\b',
        PIXELK_TAB = '\t',
        PIXELK_SPACE = ' ',
        PIXELK_EXCLAIM = '!',
        PIXELK_QUOTEDBL = '"',
        PIXELK_HASH = '#',
        PIXELK_PERCENT = '%',
        PIXELK_DOLLAR = '$',
        PIXELK_AMPERSAND = '&',
        PIXELK_QUOTE = '\'',
        PIXELK_LEFTPAREN = '(',
        PIXELK_RIGHTPAREN = ')',
        PIXELK_ASTERISK = '*',
        PIXELK_PLUS = '+',
        PIXELK_COMMA = ',',
        PIXELK_MINUS = '-',
        PIXELK_PERIOD = '.',
        PIXELK_SLASH = '/'
    };

    class Input
    {
    private:
        static SDL_Event event;

    private:
        Input() = delete;
    
    public:
        //Returns true while the user holds down the key identified by name
        static bool GetKey(KeyCode key);
        //Returns true during the frame the user starts pressing down the key identified by name
        static bool GetKeyDown(KeyCode key);
        //Returns true during the frame the user releases the key identified by name
        static bool GetKeyUp(KeyCode key);
        //Returns the current mouse scroll
        static int GetMouseScroll();
        //The current mouse position in pixel coordinates relative to the window
        static Vec2 GetMousePosition();
        //Returns true during the frame the user pressed the given mouse button
        static bool GetMouseButtonDown(int index);
        //Returns true during the frame the user releases the given mouse button
        static bool GetMouseButtonUp(int index);

        friend class PixelLoop;
    };
};

#endif