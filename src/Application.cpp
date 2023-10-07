#include "../include/Application.h"
#include "../include/Renderer/SDLRenderer.h"
#include "../include/Physics/Objects/Circle.h"
#include "../include/Physics/Objects/Rect.h"
#include "../include/Physics/Objects/RegularPolygon.h"
#include "../include/Physics/Collision/NarrowPhase.h"
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
    world = new Physics::World(windowWidth, windowHeight, glm::vec2(0.0f, 0.0f), 0.1f);

    // testObjectsGrid(100, Physics::ObjectType::PolygonObject, 30.0f, 20000, 1.0f, 0.1f, 0.0f);
    testObjectsGridMix(100, 30.0f, 20000, 1.0f, 0.1f, 0.0f);
    // testChain(glm::vec2(windowWidth / 2, 100), 5, 50, 1);

    // float force = 0;

    // Physics::RegularPolygon *a = new Physics::RegularPolygon(glm::vec2(150, windowHeight / 2), 20, 32, 10);
    // Physics::Rect *a = new Physics::Rect(glm::vec2(windowWidth - 150, windowHeight / 2), 40, 40, 10);
    // Physics::Rect *b = new Physics::Rect(glm::vec2(windowWidth - 150, windowHeight / 2), 40, 40, 10);

    // a->applyForce(glm::vec2(force, 0), a->getCentre());
    // b->applyForce(glm::vec2(-force, 0), b->getCentre());

    // world->addObject(a);
    // world->addObject(b);

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

void Application::testObjectsGridMix(int count, float size, float force, float restitution, float friction, float drag)
{
    int padding = size;
    int x = padding;
    int y = padding;

    for (int i = 0; i < count; i++)
    {
        Physics::Object *o;
        if (rand() % 2 == 0)
        {
            // o = new Physics::Circle(glm::vec2(x, y), size / 2.0f, size * 0.1f, restitution, friction, drag);
            o = new Physics::RegularPolygon(glm::vec2(x, y), size * 0.5f, size * 0.75f, size * 0.1f, restitution, friction, drag);
        }
        else
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

void Application::testChain(glm::vec2 start, int links, float linkLength, float linkStiffness)
{
    Physics::Point *last = new Physics::Point(start, 0);

    for (int i = 0; i < links; i++)
    {
        Physics::Circle *c = new Physics::Circle(glm::vec2(start.x, start.y + linkLength * i), 10, 1, 1, 0.1, 0);
        Physics::DistanceConstraintPoints *d = new Physics::DistanceConstraintPoints(last, c->getPoints()[0], linkStiffness);

        world->addObject(c);
        world->addConstraint(d);

        last = c->getPoints()[0];
    }

    last->applyForce(glm::vec2(20000, 0));
}

void Application::updateMouseConstraint(float grabRadius)
{
    int mouseX, mouseY;
    Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);
    bool leftMouseDown = buttons & SDL_BUTTON(1);

    if (leftMouseDown && mouseConstraint != nullptr)
    {
        // update position of mouse constraint
        auto points = mouseConstraint->getA()->getPoints();
        auto c = points[0];

        c->setPosition(glm::vec2(mouseX, mouseY));
    }
    else if (leftMouseDown)
    {
        // find new object to grab
        auto mousePoint = new Physics::Circle(glm::vec2(mouseX, mouseY), grabRadius, 0, 0, 0, 0);
        Physics::Object *grab = nullptr;

        for (auto o : world->getObjects())
        {
            Physics::CollisionPair p{a : mousePoint, b : o};

            auto m = Physics::narrowPhasePair(&p);
            if (m == nullptr)
                continue;

            grab = o;
            break;
        }

        // user didnt grab any object
        if (grab == nullptr)
            return;

        // create distance constraint
        mouseConstraint = new Physics::DistanceConstraintObjects(mousePoint, grab, 1, 0);
        world->addConstraint(mouseConstraint);
    }
    else if (mouseConstraint != nullptr)
    {
        world->removeConstraint(mouseConstraint);

        delete mouseConstraint->getA();
        delete mouseConstraint;
        mouseConstraint = nullptr;
    }
}

void Application::update(float dt)
{
    float physicsDt = std::min(dt, 0.02f);

    // update physics
    int startPhysics = SDL_GetTicks64();
    world->step(physicsDt, 8, renderer);
    int endPhysics = SDL_GetTicks64();

    // update mouse constraint
    updateMouseConstraint(5.0f);

    // print timestep info
    // std::cout << "\rke: " << 0 << ", physics (ms): " << endPhysics - startPhysics << ", physics dt: " << physicsDt << ", dt: " << dt << "                  ";
}

void Application::render(bool clear)
{
    // clear last frame
    if (clear)
        renderer->clear();

    // add physics constraints to renderer
    for (auto c : world->getConstraints())
    {
        if (typeid(*c) == typeid(Physics::DistanceConstraintPoints))
        {
            Physics::DistanceConstraintPoints *dc = static_cast<Physics::DistanceConstraintPoints *>(c);

            renderer->line(dc->getP1()->getPosition(), dc->getP2()->getPosition(), Renderer::Color{r : 150, g : 150, b : 150, a : 255});
        }
    }

    // add physics objects to renderer
    const Renderer::Color color{r : 255, g : 255, b : 255, a : 255};

    for (auto o : world->getObjects())
    {
        // draw braces
        if (Globals::DEBUG_MODE && o->getType() == Physics::ObjectType::PolygonObject)
        {
            for (auto e : o->getEdges())
            {
                if (e->getIsBrace())
                {
                    renderer->line(e->getP1()->getPosition(), e->getP2()->getPosition(), Renderer::Color{r : 0, g : 0, b : 180, a : 255});
                }
            }
        }

        // draw object
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
            renderer->rect(rect, Renderer::Color{r : 0, g : 180, b : 0, a : 255});
        }
    }

    // render
    renderer->present();
}
