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

    auto lastUpdateTime = SDL_GetTicks64() - desiredFrameTime;

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
    world = new Physics::World(glm::vec2(0.0f, 0.0f));

    // test objects
    // srand(time(NULL));

    // for (int i = 0; i < 50; i++)
    // {
    //     float x = rand() % windowWidth;
    //     float y = rand() % windowHeight;
    //     float r = rand() % 15 + 10;

    //     auto c = new Physics::Circle(glm::vec2(x, y), r, r * 0.1f);

    //     world->addObject(c);
    // }

    auto c1 = new Physics::Circle(glm::vec2(50, windowHeight / 2.0f), 25, 10);
    auto c2 = new Physics::Circle(glm::vec2(windowWidth - 50, windowHeight / 2.0f), 25, 100);

    c1->applyForce(glm::vec2(500000, 0), c1->getCentre());
    c2->applyForce(glm::vec2(-500000 * 4, 0), c2->getCentre());

    world->addObject(c1);
    world->addObject(c2);

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
        if (o->getType() == Physics::ObjectType::CircleObject)
        {
            Physics::Circle *c = static_cast<Physics::Circle *>(o);

            const Renderer::Circle circle{
                centre : c->getCentre(),
                radius : c->getRadius()
            };

            renderer->circle(circle, color);
        }
    }

    // render
    renderer->present();
}
