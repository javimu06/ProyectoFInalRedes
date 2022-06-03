#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "Player.h"

#include "Boat.h"
#include "Casilla.h"

#include <vector>
class GameClient;
class Player : public GameObject
{
public:
    Player(GameClient *GM_, int jug);
    virtual ~Player();

    void handleInput(const SDL_Event &) override;
    void update() override;
    void render() override;

    void poniendoBarcos();

    //# metodos red
    bool tieneBarcos();
    void actualizaCasilla(Vector2D pos);
    void cambiaCasilla(Vector2D pos, Casilla::estado est);


    int mapaSizeX = 8;
    int mapaSizeY = 4;
    Casilla *mapa[4][8];
    std::vector<Boat *> boats;

    GameClient *getGM() { return gameManager_; }

    int nJugador;
    bool alive = true;
    bool interactuable = false;

private:
    GameClient *gameManager_;
    int numBarcos = 4;
    int numBarcosColocados = 0;
    Boat *aux = nullptr;
};
#endif