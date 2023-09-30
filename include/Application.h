#pragma once

#include "../include/Physics/World.h"
#include "../include/Renderer/SDLRenderer.h"
#include "../include/Physics/Objects/Object.h"

#include <string>
#include <SDL2/SDL.h>

enum ApplicationState
{
    RUNNING,
    EXIT
};

class Application
{
public:
    Application(std::string windowTitle, int windowWidth, int windowHeight);
    ~Application();

    int run();

private:
    std::string windowTitle;
    int windowWidth;
    int windowHeight;

    ApplicationState state = ApplicationState::RUNNING;

    SDL_Window *window;
    SDL_Renderer *sdlRenderer;

    int init();
    void destroy();

    void testObjectsGrid(int count, Physics::ObjectType type, float size = 10, float force = 25000, float restitution = 1.0f, float friction = 0.0f, float drag = 0.0f);
    void testObjectsCollision(Physics::ObjectType type, float sizeA = 10, float sizeB = 10, float force = 25000, float restitution = 1.0f, float friction = 0.0f, float drag = 0.0f);
    void testChain(glm::vec2 start, int links, float linkLength, float linkStiffness);

    Renderer::SDLRenderer *renderer;
    Physics::World *world;

    void update(float dt);
    void render(bool clear = true);
};