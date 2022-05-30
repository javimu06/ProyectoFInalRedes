#ifndef BOAT_H_
#define BOAT_H_

#include "Casilla.h"

#include <vector>
#include <string>
#include "GameObject.h"

class Player;

class Boat : public GameObject
{
public:
    enum direccionBarco : Uint8
    {
        norte = 0,
        este = 1,
        sur = 2,
        oeste = 3
    };

    bool colocado;

    Boat(Player *pl, Vector2D Icoord, int tam, direccionBarco dir);
    void ActualizaBarco();
    ~Boat();

    void handleInput(const SDL_Event &) override;
    void update() override;

    Vector2D InitCord_;
    Vector2D EndCord_;
    std::vector<Casilla *> casillasBarco;
    int tamano;

    // Devuelve si la coordenada esta contenida en el barco para que posteriormente se modifique el tablero en consecuencia
    bool coordenadaTocaBarco(Vector2D coordenada);
    bool Colocable();
    direccionBarco barcodir;

    bool estaHundido();

private:
    Player *player;
};
#endif