#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "Player.h"

#include "Boat.h"
#include "Casilla.h"

#include <vector>
class Game;
class Player : public GameObject
{
public:
    Player(Game *GM_);
    virtual ~Player();

    void handleInput(const SDL_Event &) override;
    void update() override;
    void render() override;

    Casilla* mapa[8][8];
    std::vector<Boat *> boats;

    Game *getGM() { return gameManager_; }

private:
    int mapaSize = 8;
    Game* gameManager_;
};
#endif