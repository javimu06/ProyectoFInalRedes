#include "Boat.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include "Environment.h"

Boat::Boat(Player *pl, Vector2D Icoord, int tamano, direccionBarco dir)
{
    player = pl;

    InitCord_ = Icoord;
    barcodir = dir;

    switch (dir)
    {
    case direccionBarco::norte:
        for (int j = InitCord_.getY(); j > InitCord_.getY() - tamano; --j)
        {
            int i = (int)InitCord_.getX();
            casillasBarco.push_back(player->mapa[j][i]);
            EndCord_ = Vector2D(i, j);
        }
        setTransform(InitCord_.getX() * 131 * player->getGM()->scale + environment().width() / 4.4f, (InitCord_.getY() - (tamano - 1)) * 131 * player->getGM()->scale + environment().height() * 0.02f);
        setDimensions(131 * player->getGM()->scale, 131 * tamano * player->getGM()->scale);
        break;
    case direccionBarco::sur:
        for (int j = InitCord_.getY(); j < InitCord_.getY() + tamano; ++j)
        {
            int i = (int)InitCord_.getX();
            casillasBarco.push_back(player->mapa[j][i]);
            EndCord_ = Vector2D(i, j);
        }
        setTransform(InitCord_.getX() * 131 * player->getGM()->scale + environment().width() / 4.4f, InitCord_.getY() * 131 * player->getGM()->scale + environment().height() * 0.02f);
        setDimensions(131 * player->getGM()->scale, 131 * tamano * player->getGM()->scale);
        break;
    case direccionBarco::este:
        for (int i = InitCord_.getX(); i < InitCord_.getX() + tamano; ++i)
        {
            int j = (int)InitCord_.getY();
            casillasBarco.push_back(player->mapa[j][i]);
            EndCord_ = Vector2D(i, j);
        }
        setTransform(InitCord_.getX() * 131 * player->getGM()->scale + environment().width() / 4.4f, InitCord_.getY() * 131 * player->getGM()->scale + environment().height() * 0.02f);
        setDimensions(131 * tamano * player->getGM()->scale, 131 * player->getGM()->scale);

        break;
    case direccionBarco::oeste:
        for (int i = InitCord_.getX(); i > InitCord_.getX() - tamano; --i)
        {
            int j = (int)InitCord_.getY();
            casillasBarco.push_back(player->mapa[j][i]);
            EndCord_ = Vector2D(i, j);
        }
        setTransform((InitCord_.getX() - (tamano - 1)) * 131 * player->getGM()->scale + environment().width() / 4.4f, InitCord_.getY() * 131 * player->getGM()->scale + environment().height() * 0.02f);
        setDimensions(131 * tamano * player->getGM()->scale, 131 * player->getGM()->scale);

        break;
    };

    std::string aux = "./resources/images/Barco" + std::to_string(tamano) + std::to_string(dir) + ".png";
    setTexture(aux);
    // rotateTexture(90.0f);
}

Boat::~Boat() {}

void Boat::handleInput(const SDL_Event &e)
{
}

void Boat::update()
{
}

bool Boat::coordenadaTocaBarco(Vector2D coordenada)
{
    if (InitCord_.getX() == EndCord_.getX() == coordenada.getX())
    {
        if ((coordenada.getY() < InitCord_.getY() && coordenada.getY() > EndCord_.getY()) ||
            coordenada.getY() > InitCord_.getY() && coordenada.getY() < EndCord_.getY())
        {
            return true;
        }
        else
            return false;
    }
    else if (InitCord_.getY() == EndCord_.getY() == coordenada.getY())
    {
        if ((coordenada.getX() < InitCord_.getX() && coordenada.getX() > EndCord_.getX()) ||
            coordenada.getX() > InitCord_.getX() && coordenada.getX() < EndCord_.getX())
        {
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
