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

void Renderer::SDLRenderer::line(glm::vec2 start, glm::vec2 end, const Color &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
}

void Renderer::SDLRenderer::circle(const Circle &circle, const Color &color)
{
    int x = std::floor(circle.centre[0]);
    int y = std::floor(circle.centre[1]);
    int radius = std::floor(circle.radius);

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

void Renderer::SDLRenderer::rect(const Rect &rect, const Color &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Rect sdlRect{
        x : static_cast<int>(rect.topLeft.x),
        y : static_cast<int>(rect.topLeft.y),
        w : static_cast<int>(rect.w),
        h : static_cast<int>(rect.h)
    };

    SDL_RenderDrawRect(renderer, &sdlRect);
};

void Renderer::SDLRenderer::polygon(const std::vector<glm::vec2> &vertices, const Color &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int i = 0; i < vertices.size(); i++)
    {
        int j = (i + 1) % vertices.size();

        SDL_RenderDrawLine(renderer, vertices[i].x, vertices[i].y, vertices[j].x, vertices[j].y);
    }
};