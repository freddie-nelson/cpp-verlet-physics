#include "../include/Application.h"
#include "../include/Renderer/SDLRenderer.h"
#include "../include/Physics/Objects/Circle.h"
#include "../include/Physics/Objects/Rect.h"

#include <math.h>
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

    // simulate 10 seconds of perfect step physics
    // for (int i = 0; i < 4 * desiredFps; i++)
    // {
    //     update(1.0f / desiredFps);
    // }

    // // count balls on screen
    // int balls = 0;
    // float slop = 0.5f;

    // for (auto o : world->getObjects())
    // {
    //     auto c = static_cast<Physics::Circle *>(o);

    //     auto centre = c->getCentre();
    //     auto radius = c->getRadius();

    //     if (centre.x - radius + slop >= 0 && centre.x + radius - slop <= windowWidth && centre.y - radius + slop >= 0 && centre.y + radius - slop <= windowHeight)
    //     {
    //         balls++;
    //     }
    // }

    // std::cout << "balls: " << balls << std::endl;

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

        // clear renderer first so that update functions can draw to the screen
        renderer->clear();

        update(dt);
        render(false);

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
    world = new Physics::World(windowWidth, windowHeight, glm::vec2(0.0f, 200.0f), 0.0f, 0.1f);

    // lots of circles
    // float r = 10.0f;
    // float x = 50.0f;
    // float y = 100.0f;
    // int fMag = 5000;

    // for (int i = 0; i < 300; i++)
    // {
    //     auto c = new Physics::Circle(glm::vec2(x, y), r, r * 0.1f, 0.0f);
    //     c->applyForce(glm::vec2(fMag, fMag) * float(int(x + y) % 7), c->getCentre());

    //     world->addObject(c);

    //     // update x and y
    //     x += r * 3;
    //     if (x + r > windowWidth - 50)
    //     {
    //         x = 50.0f;
    //         y += r * 3;
    //     }
    // }

    // 2 circles
    // float r = 25;
    // float m1 = 10;
    // float m2 = 10;
    // float restitution = 1.0f;

    // float force = 50000;

    // auto c1 = new Physics::Circle(glm::vec2(50, windowHeight / 2.0f), r, m1, restitution);
    // auto c2 = new Physics::Circle(glm::vec2(windowWidth - 50, windowHeight / 2.0f), r, m2, restitution);

    // c1->applyForce(glm::vec2(force, 0), c1->getCentre());
    // c2->applyForce(glm::vec2(-force * (m2 / m1), 0), c2->getCentre());

    // world->addObject(c1);
    // world->addObject(c2);

    // 2 rectangles
    float w = 50;
    float h = 50;
    float m1 = 10;
    float m2 = 10;
    float restitution = 1.0f;

    float force = 50000;

    auto r1 = new Physics::Rect(glm::vec2(50, windowHeight / 2.0f), w, h, m1, restitution);
    auto r2 = new Physics::Rect(glm::vec2(windowWidth - 50, windowHeight / 2.0f), w, h, m2, restitution);

    r1->applyForce(glm::vec2(force, 0), r1->getCentre());
    r2->applyForce(glm::vec2(-force * (m2 / m1), 0), r2->getCentre());

    world->addObject(r1);
    world->addObject(r2);

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
    float physicsDt = std::min(dt, 0.02f);

    // update physics
    int startPhysics = SDL_GetTicks64();
    world->step(physicsDt, 8, renderer);
    int endPhysics = SDL_GetTicks64();

    // print debug info
    std::cout << "\rke: " << world->calculateKineticEnergy() << ", physics (ms): " << endPhysics - startPhysics << ", physics dt: " << physicsDt << ", dt: " << dt << "                     ";
}

void Application::render(bool clear)
{
    // clear last frame
    if (clear)
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
        else if (o->getType() == Physics::ObjectType::PolygonObject)
        {
            auto points = o->getPoints();

            auto pVecs = std::vector<glm::vec2>{};
            for (auto p : points)
            {
                pVecs.push_back(p->getPosition());
            }

            renderer->polygon(pVecs, color);
        }
    }

    // render
    renderer->present();
}
