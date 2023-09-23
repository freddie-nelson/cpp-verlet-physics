#include "../include/Application.h"
#include "../include/Renderer/SDLRenderer.h"
#include "../include/Physics/Objects/Circle.h"

#include <random>
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

    const int desiredFps = 60;
    const int desiredFrameTime = 1000 / desiredFps;

    auto lastUpdateTime = SDL_GetTicks64();

    while (state == ApplicationState::RUNNING)
    {
        // update timestep
        const auto now = SDL_GetTicks64();
        const auto diff = now - lastUpdateTime;
        lastUpdateTime = now;

        // dt in seconds
        const float dt = (float)diff / 1000.0f;

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

        // wait until frame time is reached
        const auto frameEndTime = now + desiredFrameTime;
        while (SDL_GetTicks64() < frameEndTime)
        {
            SDL_Delay(1);
        }
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
    world = new Physics::World(glm::vec2(0.0f, 10.0f));

    // test objects
    srand(time(NULL));

    for (int i = 0; i < 50; i++)
    {
        float x = rand() % windowWidth;
        float y = rand() % windowHeight;
        auto c = new Physics::Circle(glm::vec2(x, y), 20.0f);

        world->addObject(c);
    }

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
    int substeps = 1;
    float subDt = dt / substeps;

    // print dt
    std::cout << "\rdt: " << dt << ", subDt: " << subDt;

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
                    o->getCentre(),
                radius : o->getSize()[0]
            };

            renderer->circle(circle, color);
        }
    }

    // render
    renderer->present();
}
