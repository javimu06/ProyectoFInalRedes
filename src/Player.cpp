#include "Player.h"
#include "Game.h"

#include <iostream>
#include <string>

Player::Player(Game *gm) : GameObject()
{
    gameManager_ = gm;

    for (int i = 0; i < mapaSize; ++i)
    {
        for (int j = 0; j < mapaSize; ++j)
        {
            mapa[i][j] = new Casilla(this, Vector2D(j, i));
            gameManager_->addObjectList(mapa[i][j]);
        }
    }

    // BARCOS DIRECCION ESTE
    Boat *miBarquitoChikito0 = new Boat(this, Vector2D(0, 0), 1, Boat::direccionBarco::este);
    boats.push_back(miBarquitoChikito0);
    gameManager_->addObjectList(miBarquitoChikito0);
    Boat *miBarquitoChikito1 = new Boat(this, Vector2D(0, 1), 2, Boat::direccionBarco::este);
    boats.push_back(miBarquitoChikito1);
    gameManager_->addObjectList(miBarquitoChikito1);
    Boat *miBarquitoChikito2 = new Boat(this, Vector2D(0, 2), 3, Boat::direccionBarco::este);
    boats.push_back(miBarquitoChikito2);
    gameManager_->addObjectList(miBarquitoChikito2);
    Boat *miBarquitoChikito3 = new Boat(this, Vector2D(0, 3), 4, Boat::direccionBarco::este);
    boats.push_back(miBarquitoChikito3);
    gameManager_->addObjectList(miBarquitoChikito3);
    // BARCOS DIRECCION OESTE
    Boat *miBarquitoChikito4 = new Boat(this, Vector2D(7, 0), 1, Boat::direccionBarco::oeste);
    boats.push_back(miBarquitoChikito4);
    gameManager_->addObjectList(miBarquitoChikito4);
    Boat *miBarquitoChikito5 = new Boat(this, Vector2D(7, 1), 2, Boat::direccionBarco::oeste);
    boats.push_back(miBarquitoChikito5);
    gameManager_->addObjectList(miBarquitoChikito5);
    Boat *miBarquitoChikito6 = new Boat(this, Vector2D(7, 2), 3, Boat::direccionBarco::oeste);
    boats.push_back(miBarquitoChikito6);
    gameManager_->addObjectList(miBarquitoChikito6);
    Boat *miBarquitoChikito7 = new Boat(this, Vector2D(7, 3), 4, Boat::direccionBarco::oeste);
    boats.push_back(miBarquitoChikito7);
    gameManager_->addObjectList(miBarquitoChikito7);
    // BARCOS DIRECCION NORTE
    Boat *miBarquitoChikito8 = new Boat(this, Vector2D(0, 7), 1, Boat::direccionBarco::norte);
    boats.push_back(miBarquitoChikito8);
    gameManager_->addObjectList(miBarquitoChikito8);
    Boat *miBarquitoChikito9 = new Boat(this, Vector2D(1, 7), 2, Boat::direccionBarco::norte);
    boats.push_back(miBarquitoChikito9);
    gameManager_->addObjectList(miBarquitoChikito9);
    Boat *miBarquitoChikito10 = new Boat(this, Vector2D(2, 7), 3, Boat::direccionBarco::norte);
    boats.push_back(miBarquitoChikito10);
    gameManager_->addObjectList(miBarquitoChikito10);
    Boat *miBarquitoChikitO11 = new Boat(this, Vector2D(3, 7), 4, Boat::direccionBarco::norte);
    boats.push_back(miBarquitoChikitO11);
    gameManager_->addObjectList(miBarquitoChikitO11);
     // BARCOS DIRECCION SUR
    Boat *miBarquitoChikito12 = new Boat(this, Vector2D(4, 4), 1, Boat::direccionBarco::sur);
    boats.push_back(miBarquitoChikito12);
    gameManager_->addObjectList(miBarquitoChikito12);
    Boat *miBarquitoChikito13 = new Boat(this, Vector2D(5, 4), 2, Boat::direccionBarco::sur);
    boats.push_back(miBarquitoChikito13);
    gameManager_->addObjectList(miBarquitoChikito13);
    Boat *miBarquitoChikito14 = new Boat(this, Vector2D(6, 4), 3, Boat::direccionBarco::sur);
    boats.push_back(miBarquitoChikito14);
    gameManager_->addObjectList(miBarquitoChikito14);
    Boat *miBarquitoChikitO15 = new Boat(this, Vector2D(7, 4), 4, Boat::direccionBarco::sur);
    boats.push_back(miBarquitoChikitO15);
    gameManager_->addObjectList(miBarquitoChikitO15);
}

Player::~Player() {}

void Player::handleInput(const SDL_Event &e)
{
}

void Player::update()
{
}

void Player::render()
{
}