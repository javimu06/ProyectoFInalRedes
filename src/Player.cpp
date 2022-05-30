#include "Player.h"
#include "Game.h"

#include <iostream>
#include <string>

Player::Player(Game *gm, int jug) : GameObject()
{
    gameManager_ = gm;
    nJugador = jug;

    for (int i = 0; i < mapaSizeY; ++i)
    {
        for (int j = 0; j < mapaSizeX; ++j)
        {
            mapa[i][j] = new Casilla(this, Vector2D(j, i));
            gameManager_->addObjectList(mapa[i][j]);
        }
    }
}

Player::~Player() {}

void Player::handleInput(const SDL_Event &e) {}
void Player::update() {}
void Player::render(){}

void Player::poniendoBarcos()
{
    if (gameManager_->ActualState == Game::gameStates::puttingBoats)
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
            //#Pasar al otro jugador
            if (!gameManager_->turno)
                gameManager_->turno = true;
            else
                gameManager_->ActualState = Game::gameStates::playing;
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

