#include "Casilla.h"
#include <iostream>
#include <string>
#include "Player.h"
#include "Game.h"
#include "Environment.h"

Casilla::Casilla(Player *pl, Vector2D pos)
{
    posicion = pos;
    player = pl;

    setTransform(posicion.getX() * 131 * player->getGM()->scale + environment().width() / 4.4f, posicion.getY() * 131 * player->getGM()->scale + environment().height() * 0.02f + player->nJugador * 525 * player->getGM()->scale);
    setDimensions(131 * player->getGM()->scale, 131 * player->getGM()->scale);
    setTexture("./resources/images/Casilla.png");
}

Casilla::Casilla() {}

Casilla::~Casilla() {}

void Casilla::handleInput(const SDL_Event &e)
{
    if(player->interactuable)
    if (player->getGM()->ActualState == GameClient::gameStates::playing)
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            //#Comprobador de turno para seleccionar las del contrario
            if (player->nJugador != player->getGM()->turno)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Point mousePoint = {x, y};
                if (SDL_PointInRect(&mousePoint, &dest))
                {
                    //# Enviar actualizaCasilla al servidor para que lo mande al cliente 1

                    player->getGM()->CheckTile(posicion.getX(),posicion.getY());
                    //player->actualizaCasilla(posicion);

                    std::cout << posicion.getX() << " " << posicion.getY() << "\n";
                }
            }
        }
    }
}

void Casilla::update()
{
    if (estadoActual == estado::agua)
        setTexture("./resources/images/CruzVerde.png");
    else if (estadoActual == estado::tocado)
        setTexture("./resources/images/CruzRoja.png");
}