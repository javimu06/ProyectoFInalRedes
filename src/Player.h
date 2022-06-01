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
    Player(Game *GM_, int jug);
    virtual ~Player();

    void handleInput(const SDL_Event &) override;
    void update() override;
    void render() override;

    void poniendoBarcos();

    //# metodos red
    bool tieneBarcos();
    void actualizaCasilla(Vector2D pos);                    //Se ejecuta en el cliente al que se envia (cliente 2)
    void cambiaCasilla(Vector2D pos, Casilla::estado est);  //Se ejecuta en el cliente al que se envia (que seria el primer cliente que realizo la primera llamada)


    int mapaSizeX = 8;
    int mapaSizeY = 4;
    Casilla *mapa[4][8];
    std::vector<Boat *> boats;

    Game *getGM() { return gameManager_; }

    int nJugador;
    bool alive = true;

private:
    Game *gameManager_;
    int numBarcos = 4;
    int numBarcosColocados = 0;
    Boat *aux = nullptr;
};
#endif