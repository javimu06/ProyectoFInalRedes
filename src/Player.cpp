#include "Player.h"
#include "Game.h"

#include <iostream>
#include <string>

Player::Player(GameClient *gm, int jug) : GameObject()
{
    gameManager_ = gm;
    nJugador = jug;

    for (int j = 0; j < mapaSizeY; ++j)
    {
        for (int i = 0; i < mapaSizeX; ++i)
        {
            mapa[j][i] = new Casilla(this, Vector2D(i, j));
            gameManager_->addObjectList(mapa[j][i]);
        }
    }
}

Player::~Player() {}

void Player::handleInput(const SDL_Event &e) {}
void Player::update() {}
void Player::render() {}

void Player::poniendoBarcos()
{
    if (gameManager_->ActualState == GameClient::gameStates::puttingBoats)
    {
        if (numBarcosColocados != numBarcos)
        {
            if (aux == nullptr)
            {
                aux = new Boat(this, Vector2D(0, 0), 1 + numBarcosColocados, Boat::direccionBarco::este);
                boats.push_back(aux);
                gameManager_->addObjectList(aux);
            }
            else if (aux->colocado)
            {
                numBarcosColocados++;
                aux = nullptr;
            }
        }
        else
        {
            // if (!gameManager_->turno)
            // {
            //     gameManager_->cambiaTurno();
            // }
            // else
            // {
            //# Avisar al servidor de que pusiste tus barcos y estas listo para empezar el juego
            gameManager_->ActualState = GameClient::gameStates::playing;
            gameManager_->ready();
            //}
        }
    }
}

// Si tiene algun barco que no este hundido es devuelve true
bool Player::tieneBarcos()
{
    for (auto &b : boats)
    {
        if (!b->estaHundido())
            return true;
    }
    return false;
}

// Pregunta
void Player::actualizaCasilla(Vector2D pos)
{
    int x, y;
    x = pos.getX();
    y = pos.getY();
    std::cout << pos.getX() << " " << pos.getY() << "\n";

    if (mapa[y][x]->estadoActual == Casilla::predeterminado)
    {
        bool finded = false;
        for (auto &b : boats)
        {
            for (auto &c : b->casillasBarco)
            {
                if (pos.getX() == c->posicion.getX() && pos.getY() == c->posicion.getY())
                {
                    //#Actualizacion de casilla
                    cambiaCasilla(pos, Casilla::tocado);
                    getGM()->CheckTile2(x, y, 1);
                    finded = true;
                    break;
                }
            }
        }
        if (!finded)
        {
            //#Cambio de turno y actualizacion de casilla
            getGM()->CheckTile2(x, y, 0);
            cambiaCasilla(pos, Casilla::agua);
            getGM()->turno = !getGM()->turno;
        }
    }
}

// Respuesta
void Player::cambiaCasilla(Vector2D pos, Casilla::estado est)
{
    int y = pos.getY();
    int x = pos.getX();
    mapa[y][x]->estadoActual = est;
}