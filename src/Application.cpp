#include "../include/Application.h"
#include "../include/Renderer/SDLRenderer.h"
#include "../include/Physics/Objects/Circle.h"
#include "../include/Physics/Objects/Rect.h"
#include "../include/Globals.h"

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
    world = new Physics::World(windowWidth, windowHeight, glm::vec2(0.0f, 200.0f), 0.1f);

    testObjectsGrid(100, Physics::ObjectType::PolygonObject, 30.0f, 20000, 1.0f, 0.1f, 0.0f);

    return 0;
}

void Application::destroy()
{
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    delete this;
}

void Application::testObjectsGrid(int count, Physics::ObjectType type, float size, float force, float restitution, float friction, float drag)
{
    int padding = size;
    int x = padding;
    int y = padding;

    for (int i = 0; i < count; i++)
    {
        Physics::Object *o;
        if (type == Physics::ObjectType::CircleObject)
        {
            o = new Physics::Circle(glm::vec2(x, y), size / 2.0f, size * 0.1f, restitution, friction, drag);
        }
        else if (type == Physics::ObjectType::PolygonObject)
        {
            o = new Physics::Rect(glm::vec2(x, y), size, size, size * 0.1f, restitution, friction, drag);
        }

        o->applyForce(glm::vec2(force, force) * float(int(x + y) % 7), o->getCentre());

        world->addObject(o);

        // update x and y
        x += size * 1.5f;
        if (x + size > windowWidth - padding)
        {
            x = padding;
            y += size * 1.5f;
        }
    }
}

void Application::testObjectsCollision(Physics::ObjectType type, float sizeA, float sizeB, float force, float restitution, float friction, float drag)
{
    float x = 150;
    float mA = sizeA * 0.1f;
    float mB = sizeB * 0.1f;

    Physics::Object *a;
    Physics::Object *b;

    if (type == Physics::ObjectType::CircleObject)
    {
        a = new Physics::Circle(glm::vec2(x, windowHeight / 2.0f), sizeA, mA, restitution, friction, drag);
        b = new Physics::Circle(glm::vec2(x, windowHeight / 2.0f), sizeB, mB, restitution, friction, drag);
    }
    else if (type == Physics::ObjectType::PolygonObject)
    {
        a = new Physics::Rect(glm::vec2(x, windowHeight / 2.0f), sizeA, sizeA, mA, restitution, friction, drag);
        b = new Physics::Rect(glm::vec2(x, windowHeight / 2.0f), sizeB, sizeB, mB, restitution, friction, drag);
    }

    a->applyForce(glm::vec2(force, 0), a->getCentre());
    b->applyForce(glm::vec2(-force * (mB / mA), 0), b->getCentre());

    world->addObject(a);
    world->addObject(b);
}

void Application::update(float dt)
{
    float physicsDt = std::min(dt, 0.02f);

    // update physics
    int startPhysics = SDL_GetTicks64();
    world->step(physicsDt, 8, renderer);
    int endPhysics = SDL_GetTicks64();

    // print timestep info
    // std::cout << "\rke: " << 0 << ", physics (ms): " << endPhysics - startPhysics << ", physics dt: " << physicsDt << ", dt: " << dt << "                  ";
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

        // draw aabb
        if (Globals::DEBUG_MODE)
        {
            auto aabb = o->getAABB();
            const Renderer::Rect rect{
                topLeft : glm::vec2(aabb.min.x, aabb.min.y),
                w : aabb.max.x - aabb.min.x,
                h : aabb.max.y - aabb.min.y
            };
            renderer->rect(rect, Renderer::Color{r : 0, g : 255, b : 0, a : 125});
        }
    }

    // render
    renderer->present();
}
