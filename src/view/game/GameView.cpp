#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "GameView.h"
#include "../../ProximaCentauri.h"

GameView::GameView()
{
    initialized = false;
}

void GameView::init(SDL_Renderer *renderer)
{
    if (initialized)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game view is already initialized.\n";
    }
    else
    {
        this->renderer = renderer;

        TTF_Font *munro = TTF_OpenFont("resources/munro.ttf", 64);
        if (munro == nullptr)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Resource munro.ttf could not be loaded.\n";
            exit(EXIT_FAILURE);
        }

        SDL_Surface *victorySurface = TTF_RenderText_Blended(munro, "VICTORY", SDL_Color {255, 255, 255, 255});
        SDL_Surface *defeatSurface = TTF_RenderText_Blended(munro, "DEFEAT", SDL_Color {255, 255, 255, 255});
        SDL_Surface *replaySurface = TTF_RenderText_Blended(munro, "REPLAY", SDL_Color {0, 0, 0, 255});
        SDL_Surface *resumeSurface = TTF_RenderText_Blended(munro, "RESUME", SDL_Color {0, 0, 0, 255});
        SDL_Surface *quitSurface = TTF_RenderText_Blended(munro, "QUIT", SDL_Color {0, 0, 0, 255});

        victory = SDL_CreateTextureFromSurface(renderer, victorySurface);
        defeat = SDL_CreateTextureFromSurface(renderer, defeatSurface);
        replay = SDL_CreateTextureFromSurface(renderer, replaySurface);
        resume = SDL_CreateTextureFromSurface(renderer, resumeSurface);
        quit = SDL_CreateTextureFromSurface(renderer, quitSurface);

        victorySrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, victorySurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), victorySurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};
        defeatSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, defeatSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), defeatSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};
        replaySrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, replaySurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), replaySurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};
        resumeSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, resumeSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), resumeSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};
        quitSrcRect = {SDL_ttfDumbLeftMargin_64, SDL_ttfDumbTopMargin_64, quitSurface->w - static_cast<int_fast32_t>(SDL_ttfDumbRightMargin_64 + SDL_ttfDumbLeftMargin_64), quitSurface->h - static_cast<int_fast32_t>(SDL_ttfDumbTopMargin_64 + SDL_ttfDumbBottomMargin_64)};

        SDL_FreeSurface(victorySurface);
        SDL_FreeSurface(defeatSurface);
        SDL_FreeSurface(replaySurface);
        SDL_FreeSurface(resumeSurface);
        SDL_FreeSurface(quitSurface);

        TTF_CloseFont(munro);

        initialized = true;
    }
}

GameView::~GameView()
{
    SDL_DestroyTexture(victory);
    SDL_DestroyTexture(defeat);
    SDL_DestroyTexture(replay);
    SDL_DestroyTexture(resume);
    SDL_DestroyTexture(quit);
}

void GameView::render(const Player &player, std::vector<Entity *> entities, std::vector<Plasmaball> plasma, std::vector<Laserbeam> laser) const
{
    static auto spriteIndex = 0u;
    if (initialized)
    {
        if (ProximaCentauri::getInstance()->getBackgroundOffset() < WINDOW_HEIGHT)
        {
            SDL_Rect backgroundSrcRect{0, static_cast<int_fast32_t>((WINDOW_HEIGHT - 1) - ProximaCentauri::getInstance()->getBackgroundOffset()), WINDOW_WIDTH, WINDOW_HEIGHT};
            SDL_Rect backgroundDstRect{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
            SDL_RenderCopy(renderer, ProximaCentauri::getInstance()->getStarBackground(), &backgroundSrcRect, &backgroundDstRect);
        }
        else
        {
            SDL_Rect backgroundSrcRect1{0, 0, WINDOW_WIDTH, static_cast<int_fast32_t>(WINDOW_HEIGHT * 2 - ProximaCentauri::getInstance()->getBackgroundOffset())};
            SDL_Rect backgroundDstRect1{0, static_cast<int_fast32_t>(ProximaCentauri::getInstance()->getBackgroundOffset() - WINDOW_HEIGHT), WINDOW_WIDTH, backgroundSrcRect1.h};
            SDL_RenderCopy(renderer, ProximaCentauri::getInstance()->getStarBackground(), &backgroundSrcRect1, &backgroundDstRect1);

            SDL_Rect backgroundSrcRect2{0, static_cast<int_fast32_t>(WINDOW_HEIGHT) + backgroundSrcRect1.h, WINDOW_WIDTH, static_cast<int_fast32_t>(WINDOW_HEIGHT) - backgroundSrcRect1.h};
            SDL_Rect backgroundDstRect2{0, 0, WINDOW_WIDTH, backgroundSrcRect2.h};
            SDL_RenderCopy(renderer, ProximaCentauri::getInstance()->getStarBackground(), &backgroundSrcRect2, &backgroundDstRect2);
        }

        for (const Plasmaball plasmaball : plasma)
        {
            SDL_Rect plasmaballDstRect{static_cast<int_fast32_t>(plasmaball.getX() + PROJECTILE_EDGE / 2), static_cast<int_fast32_t>(plasmaball.getY() + PROJECTILE_EDGE / 2), PROJECTILE_EDGE, PROJECTILE_EDGE};
            SDL_Rect plasmaballSrcRect{0, 0, plasmaballDstRect.w, plasmaballDstRect.y};
            SDL_RenderCopy(renderer, ProximaCentauri::getInstance()->getPlasmaball(), &plasmaballSrcRect, &plasmaballDstRect);
        }

        for (const Laserbeam laserbeam : laser)
        {
            SDL_Rect laserRect{static_cast<int_fast32_t>(laserbeam.getX()), static_cast<int_fast32_t>(laserbeam.getY()), 3, static_cast<int_fast32_t>(laserbeam.getL())};
            SDL_SetRenderDrawColor(renderer, 0, 63, 255, 255);
            SDL_RenderFillRect(renderer, &laserRect);
        }

        SDL_Rect playerDstRect{static_cast<int_fast32_t >(player.getX()), static_cast<int_fast32_t >(player.getY()), SPACESHIP_WIDTH, SPACESHIP_HEIGHT};
        SDL_Rect playerSrcRect{static_cast<int_fast32_t>(spriteIndex / TICK_PER_SPRITE_SPACESHIP) * playerDstRect.w, 0, playerDstRect.w, playerDstRect.h};
        SDL_RenderCopy(renderer, ProximaCentauri::getInstance()->getSpaceshipSprite(), &playerSrcRect, &playerDstRect);

        for (const Entity *entity : entities)
        {
            SDL_Rect entityDstRect{entity->getX(), entity->getY(), SPACESHIP_WIDTH, SPACESHIP_HEIGHT};
            SDL_Rect entitySrcRect{static_cast<int_fast32_t>(spriteIndex / TICK_PER_SPRITE_SPACESHIP) * entityDstRect.w, static_cast<int_fast32_t>((entity->getSprite() - 1) * SPACESHIP_HEIGHT), entityDstRect.w, entityDstRect.h};
            SDL_RenderCopy(renderer, ProximaCentauri::getInstance()->getEnemySprite(), &entitySrcRect, &entityDstRect);
        }

        SDL_Rect playerHPBackground = {};
        SDL_Rect playerCurrentHPBackground = {};

        if (playerDstRect.y + playerDstRect.h + static_cast<int_fast32_t>(PLAYER_BAR_HEIGHT) + 2 < static_cast<int_fast32_t>(WINDOW_HEIGHT))
        {
            playerHPBackground = {playerDstRect.x, playerDstRect.y + playerDstRect.h + static_cast<int_fast32_t>(PLAYER_BAR_HEIGHT) + 2, playerDstRect.w, PLAYER_BAR_HEIGHT};
            playerCurrentHPBackground = {playerDstRect.x, playerDstRect.y + playerDstRect.h + static_cast<int_fast32_t>(PLAYER_BAR_HEIGHT) + 2, static_cast<int_fast32_t>(player.getHP() * playerDstRect.w / PLAYER_HEALTH), PLAYER_BAR_HEIGHT};
        }
        else
        {
            playerHPBackground = {playerDstRect.x, playerDstRect.y - static_cast<int_fast32_t>(PLAYER_BAR_HEIGHT) - 2, playerDstRect.w, PLAYER_BAR_HEIGHT};
            playerCurrentHPBackground = {playerHPBackground.x, playerHPBackground.y - 2, static_cast<int_fast32_t>(player.getHP() * playerDstRect.w / PLAYER_HEALTH), PLAYER_BAR_HEIGHT};
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 25);
        SDL_RenderFillRect(renderer, &playerHPBackground);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &playerCurrentHPBackground);

        if (++spriteIndex == 3 * TICK_PER_SPRITE_SPACESHIP)
        {
            spriteIndex = 0;
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game view is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void GameView::renderPause(uint_fast32_t selectedIndex) const
{
    if (initialized)
    {
        SDL_Rect resumeDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - resumeSrcRect.w) / 2, static_cast<int_fast32_t>(WINDOW_HEIGHT - 3 * resumeSrcRect.h) / 2, resumeSrcRect.w, resumeSrcRect.h};
        SDL_Rect quitDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - quitSrcRect.w) / 2, static_cast<int_fast32_t>(WINDOW_HEIGHT + quitSrcRect.h) / 2, quitSrcRect.w, quitSrcRect.h};

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);
        SDL_Rect menuBackgroundRect{resumeDstRect.x - static_cast<int_fast32_t>(MENU_SPACEING), resumeDstRect.y - static_cast<int_fast32_t>(MENU_SPACEING), resumeDstRect.w + 2 * static_cast<int_fast32_t>(MENU_SPACEING), 2 * static_cast<int_fast32_t>(MENU_SPACEING) + (3 * resumeDstRect.h + 3 * quitDstRect.h) / 2};
        SDL_RenderFillRect(renderer, &menuBackgroundRect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect underlineRect{};

        switch (selectedIndex)
        {
            case 0:
                underlineRect = {resumeDstRect.x, resumeDstRect.y + resumeDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), resumeDstRect.w, UNDERLINE_THICKNESS};
                break;
            case 1:
                underlineRect = {quitDstRect.x, quitDstRect.y + quitDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), quitDstRect.w, UNDERLINE_THICKNESS};
                break;
            default:
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected index: " << selectedIndex << "\n";
                exit(EXIT_FAILURE);
        }

        SDL_RenderFillRect(renderer, &underlineRect);

        SDL_RenderCopy(renderer, resume, &resumeSrcRect, &resumeDstRect);
        SDL_RenderCopy(renderer, quit, &quitSrcRect, &quitDstRect);
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game view is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void GameView::renderDefeat(uint_fast32_t selectedIndex) const
{
    if (initialized)
    {
        SDL_Rect replayDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - replaySrcRect.w) / 2, static_cast<int_fast32_t>(WINDOW_HEIGHT - 3 * replaySrcRect.h) / 2, replaySrcRect.w, replaySrcRect.h};
        SDL_Rect quitDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - quitSrcRect.w) / 2, static_cast<int_fast32_t>(WINDOW_HEIGHT + quitSrcRect.h) / 2, quitSrcRect.w, quitSrcRect.h};

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 127);
        SDL_Rect menuBackgroundRect{replayDstRect.x - static_cast<int_fast32_t>(MENU_SPACEING), replayDstRect.y - static_cast<int_fast32_t>(MENU_SPACEING), replayDstRect.w + 2 * static_cast<int_fast32_t>(MENU_SPACEING), 2 * static_cast<int_fast32_t>(MENU_SPACEING) + (3 * replayDstRect.h + 3 * quitDstRect.h) / 2};
        SDL_RenderFillRect(renderer, &menuBackgroundRect);

        SDL_Rect defeatDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - defeatSrcRect.w) / 2, menuBackgroundRect.y - defeatSrcRect.h - static_cast<int_fast32_t>(MENU_SPACEING), defeatSrcRect.w, defeatSrcRect.h};
        SDL_RenderCopy(renderer, defeat, &defeatSrcRect, &defeatDstRect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect underlineRect{};

        switch (selectedIndex)
        {
            case 0:
                underlineRect = {replayDstRect.x, replayDstRect.y + replayDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), replayDstRect.w, UNDERLINE_THICKNESS};
                break;
            case 1:
                underlineRect = {quitDstRect.x, quitDstRect.y + quitDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), quitDstRect.w, UNDERLINE_THICKNESS};
                break;
            default:
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected index: " << selectedIndex << "\n";
                exit(EXIT_FAILURE);
        }

        SDL_RenderFillRect(renderer, &underlineRect);

        SDL_RenderCopy(renderer, replay, &replaySrcRect, &replayDstRect);
        SDL_RenderCopy(renderer, quit, &quitSrcRect, &quitDstRect);
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game view is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void GameView::renderVictory(uint_fast32_t selectedIndex) const
{
    if (initialized)
    {
        SDL_Rect replayDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - replaySrcRect.w) / 2, static_cast<int_fast32_t>(WINDOW_HEIGHT - 3 * replaySrcRect.h) / 2, replaySrcRect.w, replaySrcRect.h};
        SDL_Rect quitDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - quitSrcRect.w) / 2, static_cast<int_fast32_t>(WINDOW_HEIGHT + quitSrcRect.h) / 2, quitSrcRect.w, quitSrcRect.h};

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 127);
        SDL_Rect menuBackgroundRect{replayDstRect.x - static_cast<int_fast32_t>(MENU_SPACEING), replayDstRect.y - static_cast<int_fast32_t>(MENU_SPACEING), replayDstRect.w + 2 * static_cast<int_fast32_t>(MENU_SPACEING), 2 * static_cast<int_fast32_t>(MENU_SPACEING) + (3 * replayDstRect.h + 3 * quitDstRect.h) / 2};
        SDL_RenderFillRect(renderer, &menuBackgroundRect);

        SDL_Rect victoryDstRect = {static_cast<int_fast32_t>(WINDOW_WIDTH - victorySrcRect.w) / 2, menuBackgroundRect.y - victorySrcRect.h - static_cast<int_fast32_t>(MENU_SPACEING), victorySrcRect.w, victorySrcRect.h};
        SDL_RenderCopy(renderer, victory, &victorySrcRect, &victoryDstRect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect underlineRect{};

        switch (selectedIndex)
        {
            case 0:
                underlineRect = {replayDstRect.x, replayDstRect.y + replayDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), replayDstRect.w, UNDERLINE_THICKNESS};
                break;
            case 1:
                underlineRect = {quitDstRect.x, quitDstRect.y + quitDstRect.h + static_cast<int_fast32_t>(UNDERLINE_SPACING), quitDstRect.w, UNDERLINE_THICKNESS};
                break;
            default:
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected index: " << selectedIndex << "\n";
                exit(EXIT_FAILURE);
        }

        SDL_RenderFillRect(renderer, &underlineRect);

        SDL_RenderCopy(renderer, replay, &replaySrcRect, &replayDstRect);
        SDL_RenderCopy(renderer, quit, &quitSrcRect, &quitDstRect);
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game view is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}

void GameView::reset() const
{
    if (initialized)
    {

    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Game view is not initialized.\n";
        exit(EXIT_FAILURE);
    }
}