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

        void line(glm::vec2 start, glm::vec2 end, const Color &color);
        void circle(const Circle &circle, const Color &color);
        void rect(const Rect &rect, const Color &color);
        void polygon(const std::vector<glm::vec2> &vertices, const Color &color);

    private:
        SDL_Renderer *renderer;
    };
}