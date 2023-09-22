#pragma once

#include "./Renderer.h"

#include <SDL2/SDL.h>

namespace Renderer
{

    class SDLRenderer : public Renderer
    {
    public:
        SDLRenderer(SDL_Renderer *renderer);

        void clear();
        void present();

        void circle(const Circle &circle, const Color &color);

    private:
        SDL_Renderer *renderer;
    };
}