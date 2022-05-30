#ifndef GAME_H_
#define GAME_H_

#include <vector>

#include <SDL2/SDL.h>

#include "macros.h"
#include "Player.h"

class GameObject;
class SDL_Renderer;

class Game
{
public:
    Game();
    virtual ~Game();

    void init(int w, int h);
    void setup();
    void run();
    void shutdown();
    void restart();

    float scale = 0.74f;

    enum gameStates
    {
        playing,
        mainMenu,
        quit,
        puttingBoats,
        winPlayer1,
        winPlayer2
    };

    gameStates ActualState;

    void changeGameState(gameStates newGS);

    void addObjectList(GameObject *a);
    void addObjectMenuList(GameObject *a);

    bool turno;

private:
    std::vector<GameObject *> objs_;
    std::vector<GameObject *> objs_2;
    std::vector<GameObject *> MainMenuObjs_;
    std::vector<GameObject *> MainMenuObjs_2;

    Player *player;
    Player *player2;
};
#endif