#include <iostream>
#include <vector>
#include <dirent.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ProximaCentauri.h"
#include "controller/menu/TitleScreenController.h"
#include "controller/menu/OptionsController.h"
#include "controller/menu/MapSelectionController.h"
#include "controller/game/GameController.h"

ProximaCentauri::ProximaCentauri()
{
    initialized = false;
    mapNumber = 0;
    currentMap = 0;
    backgroundOffset = 0;
    paused = false;
    looping = false;
    state = TITLE_SCREEN;

    maps = nullptr;
    starBackground = nullptr;
    spaceshipSprite = nullptr;
    enemySprite = nullptr;
    upArrow = nullptr;
    downArrow = nullptr;
    window = nullptr;
    renderer = nullptr;

    controllers[TITLE_SCREEN] = nullptr;
    controllers[OPTIONS] = nullptr;
    controllers[MAP_SELECTION] = nullptr;
    controllers[IN_GAME] = nullptr;
}

ProximaCentauri *ProximaCentauri::getInstance()
{
    static auto *const instance = new ProximaCentauri;
    return instance;
}

void ProximaCentauri::init()
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is already initialized.\n";
    }
    else
    {
        if (SDL_Init(SDL_INIT_VIDEO) == -1)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]SDL was not initialized properly.";
            exit(EXIT_FAILURE);
        }

        if (IMG_Init(IMG_INIT_PNG) == -1)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]SDL_image was not initialized properly.\n";
            exit(EXIT_FAILURE);
        }

        if (TTF_Init() == -1)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]SDL_ttf was not initialized properly.\n";
            exit(EXIT_FAILURE);
        }

        controllers[TITLE_SCREEN] = new TitleScreenController;
        controllers[OPTIONS] = new OptionsController;
        controllers[MAP_SELECTION] = new MapSelectionController;
        controllers[IN_GAME] = new GameController;

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);

        if (window == nullptr)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]SDL could not initialize the window.\n";
            exit(EXIT_FAILURE);
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (renderer == nullptr)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]SDL could not initialize the renderer.\n";
            exit(EXIT_FAILURE);
        }

        if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND))
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]SDL could set renderer blend mode.\n";
            exit(EXIT_FAILURE);
        }

        SDL_Surface *starBackgroundSurface = IMG_Load("resources/background.png");
        if (starBackgroundSurface == nullptr)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]background.png could not be loaded.\n";
            exit(EXIT_FAILURE);
        }
        starBackground = SDL_CreateTextureFromSurface(renderer, starBackgroundSurface);
        SDL_FreeSurface(starBackgroundSurface);

        SDL_Surface *spaceshipSpriteSurface = IMG_Load("resources/spaceship.png");
        if (spaceshipSpriteSurface == nullptr)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]spaceship.png could not be loaded.\n";
            exit(EXIT_FAILURE);
        }
        spaceshipSprite = SDL_CreateTextureFromSurface(renderer, spaceshipSpriteSurface);
        SDL_FreeSurface(spaceshipSpriteSurface);

        SDL_Surface *enemySpriteSurface = IMG_Load("resources/enemies.png");
        if (enemySpriteSurface == nullptr)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]enemies.png could not be loaded.\n";
            exit(EXIT_FAILURE);
        }
        enemySprite = SDL_CreateTextureFromSurface(renderer, enemySpriteSurface);
        SDL_FreeSurface(enemySpriteSurface);

        SDL_Surface *upArrowSurface = IMG_Load("resources/up.png");
        if (upArrowSurface == nullptr)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]up.png could not be loaded.\n";
            exit(EXIT_FAILURE);
        }
        upArrow = SDL_CreateTextureFromSurface(renderer, upArrowSurface);
        SDL_FreeSurface(upArrowSurface);

        SDL_Surface *downArrowSurface = IMG_Load("resources/down.png");
        if (downArrowSurface == nullptr)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]down.png could not be loaded.\n";
            exit(EXIT_FAILURE);
        }
        downArrow = SDL_CreateTextureFromSurface(renderer, downArrowSurface);
        SDL_FreeSurface(downArrowSurface);

        struct dirent *ep;
        std::vector<std::string> temp;
        DIR *dp;

        dp = opendir("maps/");

        if (dp != nullptr)
        {
            while ((ep = readdir(dp)))
            {
                if (ep->d_name[0] == '.')
                {
                    continue;
                }
                mapNumber++;
                temp.push_back(static_cast<std::string>(ep->d_name));
            }
            closedir(dp);
        }
        else
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Could not count maps.\n";
            exit(EXIT_FAILURE);
        }

        if (mapNumber == 0)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]No map to be loaded.\n";
            exit(EXIT_FAILURE);
        }

        maps = new Map[mapNumber];

        for (uint_fast32_t i = 0; i < mapNumber; i++)
        {
            maps[i].loadName(temp[i]);
        }

        backgroundOffset = 0;
        paused = false;

        initialized = true;

        controllers[TITLE_SCREEN]->init(renderer);
        controllers[OPTIONS]->init(renderer);
        controllers[MAP_SELECTION]->init(renderer);
        controllers[IN_GAME]->init(renderer);
    }
}

uint_fast32_t ProximaCentauri::getMapNumber() const
{
    if (initialized)
    {
        return mapNumber;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

uint_fast32_t ProximaCentauri::getBackgroundOffset() const
{
    if (initialized)
    {
        return (backgroundOffset / TICK_PER_SPRITE_BACKGROUND) % (WINDOW_HEIGHT * 2);
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

Map *ProximaCentauri::getMaps() const
{
    if (initialized)
    {
        return maps;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

const Map ProximaCentauri::getCurrentMap() const
{
    if (initialized)
    {
        return maps[currentMap];
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

SDL_Texture *ProximaCentauri::getStarBackground() const
{
    if (initialized)
    {
        return starBackground;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

SDL_Texture *ProximaCentauri::getSpaceshipSprite() const
{
    if (initialized)
    {
        return spaceshipSprite;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

SDL_Texture *ProximaCentauri::getEnemySprite() const
{
    if (initialized)
    {
        return enemySprite;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

SDL_Texture *ProximaCentauri::getUpArrow() const
{
    if (initialized)
    {
        return upArrow;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

SDL_Texture *ProximaCentauri::getDownArrow() const
{
    if (initialized)
    {
        return downArrow;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

Uint8 ProximaCentauri::getMoveUpKey()
{
    if (initialized)
    {
        return upKey;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

Uint8 ProximaCentauri::getMoveDownKey()
{
    if (initialized)
    {
        return downKey;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

Uint8 ProximaCentauri::getMoveLeftKey()
{
    if (initialized)
    {
        return leftKey;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

Uint8 ProximaCentauri::getMoveRightKey()
{
    if (initialized)
    {
        return rightKey;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void ProximaCentauri::setLayout(OptionsModel::KeyboardLayout layout)
{
    if (initialized)
    {
        switch (layout)
        {

            case OptionsModel::WASD:
                upKey = SDL_SCANCODE_W;
                downKey = SDL_SCANCODE_S;
                leftKey = SDL_SCANCODE_A;
                rightKey = SDL_SCANCODE_D;
                break;
            case OptionsModel::ZQSD:
                upKey = SDL_SCANCODE_W;
                downKey = SDL_SCANCODE_S;
                leftKey = SDL_SCANCODE_A;
                rightKey = SDL_SCANCODE_D;
                break;
            case OptionsModel::ARROWS:
                upKey = SDL_SCANCODE_UP;
                downKey = SDL_SCANCODE_DOWN;
                leftKey = SDL_SCANCODE_LEFT;
                rightKey = SDL_SCANCODE_RIGHT;
                break;
            default:
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected layout: " << layout << "\n";
                exit(EXIT_FAILURE);
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void ProximaCentauri::setPaused(bool paused)
{
    if (initialized)
    {
        this->paused = paused;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void ProximaCentauri::setState(ProximaCentauri::GameState state)
{
    if (initialized)
    {
        ProximaCentauri::state = state;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void ProximaCentauri::setCurrentMap(uint_fast32_t index)
{
    if (initialized)
    {
        currentMap = index;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void ProximaCentauri::stopGame()
{
    if (initialized)
    {
        looping = false;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void ProximaCentauri::start()
{
    if (initialized)
    {
        looping = true;
        loop();
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void ProximaCentauri::shutdown()
{
    if (initialized)
    {
        mapNumber = 0;
        currentMap = 0;

        delete controllers[TITLE_SCREEN];
        delete controllers[OPTIONS];
        delete controllers[MAP_SELECTION];
        delete controllers[IN_GAME];

        delete[] maps;

        SDL_DestroyTexture(starBackground);
        SDL_DestroyTexture(spaceshipSprite);
        SDL_DestroyTexture(upArrow);
        SDL_DestroyTexture(downArrow);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();

        initialized = false;
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game is not initialized.\n";
    }
}

void ProximaCentauri::loop()
{
    uint_fast64_t lastTime = 0;
    uint_fast64_t lastRenderTime = 0;
    uint_fast64_t currentTime = 0;
    uint_fast64_t elapsedTime = 0;

    while (looping)
    {
        currentTime = getTicks();
        elapsedTime = currentTime - lastTime;
        lastTime = currentTime;

        controllers[state]->tick(static_cast<long double>(elapsedTime) / static_cast<long double>(TARGET_MS_PER_TICK));

        if (getTicks() - lastRenderTime < TARGET_MS_PER_FRAME)
        {
            SDL_Delay(static_cast<Uint32>(TARGET_MS_PER_FRAME - currentTime + lastRenderTime));
        }

        lastRenderTime = getTicks();

        SDL_RenderClear(renderer);
        controllers[state]->render();
        SDL_RenderPresent(renderer);

        if (!paused)
        {
            backgroundOffset++;
        }
    }
}