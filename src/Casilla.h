#ifndef CASILLA_H_
#define CASILLA_H_

#include <vector>
#include "GameObject.h"

class Player;

class Casilla : public GameObject
{
public:
    enum estado
    {
        predeterminado,
        agua,
        tocado
    };
    Casilla(Player* pl, Vector2D pos);
    ~Casilla();

    void handleInput(const SDL_Event &) override;
    void update() override;

    estado estadoActual = predeterminado;
    Vector2D posicion;

private:
    Player *player;
};
#endif