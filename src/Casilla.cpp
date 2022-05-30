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

Casilla::~Casilla() {}

void Casilla::handleInput(const SDL_Event &e)
{
    if (player->getGM()->ActualState == Game::gameStates::playing)
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
                    bool finded = false;
                    for (auto &b : player->boats)
                    {
                        for (auto &c : b->casillasBarco)
                        {
                            if (this == c)
                            {
                                estadoActual = tocado;
                                finded = true;
                                break;
                            }
                        }
                    }
                    if (!finded)
                    {
                        estadoActual = agua;

                        //#Cambio de turno
                        player->getGM()->turno = !player->getGM()->turno;
                    }
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