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
    SDL_Renderer *renderer;

    int init();
    void destroy();

    void update(float dt);
    void render();
};