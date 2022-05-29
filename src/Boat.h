#ifndef BOAT_H_
#define BOAT_H_

#include "Casilla.h"

#include <vector>
#include <string>
#include "GameObject.h"

class Player;

class Boat: public GameObject
{
public:
    enum direccionBarco
    {
        norte,
        sur,
        este,
        oeste
    };

    Boat(Player *pl, Vector2D Icoord, int tamano, direccionBarco dir);
    ~Boat();

    void handleInput(const SDL_Event &) override;
    void update() override;

    Vector2D InitCord_;
    Vector2D EndCord_;
    std::vector<Casilla *> casillasBarco;

    // Devuelve si la coordenada esta contenida en el barco para que posteriormente se modifique el tablero en consecuencia
    bool coordenadaTocaBarco(Vector2D coordenada);

    direccionBarco barcodir;

private:
    Player *player;
};
#endif