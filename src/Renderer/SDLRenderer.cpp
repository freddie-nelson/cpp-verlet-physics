#include "../../include/Renderer/SDLRenderer.h"

#include <math.h>

Renderer::SDLRenderer::SDLRenderer(SDL_Renderer *renderer) : renderer(renderer)
{
}

void Renderer::SDLRenderer::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::SDLRenderer::present()
{
    SDL_RenderPresent(renderer);
}

void Renderer::SDLRenderer::circle(const Circle &circle, const Color &color)
{
    int x = floor(circle.centre[0]);
    int y = floor(circle.centre[1]);
    int radius = floor(circle.radius);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset

            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
};