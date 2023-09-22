#include "../include/Application.h"
#include "../include/Renderer/SDLRenderer.h"
#include "../include/Physics/Objects/Circle.h"

#include <time.h>
#include <iostream>

Application::Application(std::string windowTitle, int windowWidth, int windowHeight) : windowTitle(windowTitle), windowWidth(windowWidth), windowHeight(windowHeight)
{
}

Application::~Application()
{
    destroy();
}

int Application::run()
{
    const int initCode = init();
    if (initCode != 0)
    {
        return initCode;
    }

    int lastUpdateTime = time(NULL);

    while (state == ApplicationState::RUNNING)
    {
        // update timestep
        const int now = time(NULL);
        const int diff = now - lastUpdateTime;
        const float dt = diff / 1000;
        lastUpdateTime = now;

        // wait for sdl events to be processed
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                destroy();
            }
        }

        update(dt);
        render();
    }

    return 0;
}

int Application::init()
{
    // init sdl
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to initialize SDL." << std::endl;
        return 1;
    }

    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    sdlRenderer = SDL_CreateRenderer(window, -1, 0);

    // init renderer
    renderer = new Renderer::SDLRenderer(sdlRenderer);

    // init physics
    world = new Physics::World();

    world->addObject(new Physics::Circle(glm::vec2{200, 200}, 50));

    return 0;
}

void Application::destroy()
{
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    delete this;
}

void Application::update(float dt)
{
    // update physics
    int substeps = 8;
    float subDt = dt / substeps;

    for (int i = 0; i < substeps; i++)
    {
        world->step(subDt);
    }
}

void Application::render()
{
    // clear last frame
    renderer->clear();

    // add physics world to renderer
    const Renderer::Color color{r : 255, g : 255, b : 255, a : 255};

    for (auto o : world->getObjects())
    {
        if (typeid(*o) == typeid(Physics::Circle))
        {
            const Renderer::Circle circle{
                centre :
                    o->getPosition(),
                radius : o->getSize()[0]
            };

            renderer->circle(circle, color);
        }
    }

    // render
    renderer->present();
}
