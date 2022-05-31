#include "Boat.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include "Environment.h"

Boat::Boat(Player *pl, Vector2D Icoord, int tam, direccionBarco dir)
{
    player = pl;

    InitCord_ = Icoord;
    barcodir = dir;
    tamano = tam;

    ActualizaBarco();
    std::string aux = "./resources/images/Barco" + std::to_string(tamano) + std::to_string(barcodir) + ".png";
    setTexture(aux);
    // rotateTexture(90.0f);
}

void Boat::ActualizaBarco()
{
    casillasBarco.clear();
    switch (barcodir)
    {
    case direccionBarco::norte:
        for (int j = InitCord_.getY(); j > InitCord_.getY() - tamano; --j)
        {
            int i = (int)InitCord_.getX();
            if (j < 0)
            {
                InitCord_.setY(InitCord_.getY() + 1);
                ActualizaBarco();
                break;
            }
            casillasBarco.push_back(player->mapa[j][i]);
            EndCord_ = Vector2D(i, j);
        }
        setTransform(InitCord_.getX() * 131 * player->getGM()->scale + environment().width() / 4.4f, (InitCord_.getY() - (tamano - 1)) * 131 * player->getGM()->scale + environment().height() * 0.02f + player->nJugador * 525 * player->getGM()->scale);
        setDimensions(131 * player->getGM()->scale, 131 * tamano * player->getGM()->scale);
        break;
    case direccionBarco::sur:
        for (int j = InitCord_.getY(); j < InitCord_.getY() + tamano; ++j)
        {
            int i = (int)InitCord_.getX();
            if (j > player->mapaSizeY - 1)
            {
                InitCord_.setY(InitCord_.getY() - 1);
                ActualizaBarco();
                break;
            }
            casillasBarco.push_back(player->mapa[j][i]);
            EndCord_ = Vector2D(i, j);
        }
        setTransform(InitCord_.getX() * 131 * player->getGM()->scale + environment().width() / 4.4f, InitCord_.getY() * 131 * player->getGM()->scale + environment().height() * 0.02f + player->nJugador * 525 * player->getGM()->scale);
        setDimensions(131 * player->getGM()->scale, 131 * tamano * player->getGM()->scale);
        break;
    case direccionBarco::este:
        for (int i = InitCord_.getX(); i < InitCord_.getX() + tamano; ++i)
        {
            int j = (int)InitCord_.getY();
            if (i > player->mapaSizeX - 1)
            {
                InitCord_.setX(InitCord_.getX() - 1);
                ActualizaBarco();
                break;
            }
            casillasBarco.push_back(player->mapa[j][i]);
            EndCord_ = Vector2D(i, j);
        }
        setTransform(InitCord_.getX() * 131 * player->getGM()->scale + environment().width() / 4.4f, InitCord_.getY() * 131 * player->getGM()->scale + environment().height() * 0.02f + player->nJugador * 525 * player->getGM()->scale);
        setDimensions(131 * tamano * player->getGM()->scale, 131 * player->getGM()->scale);

        break;
    case direccionBarco::oeste:
        for (int i = InitCord_.getX(); i > InitCord_.getX() - tamano; --i)
        {
            int j = (int)InitCord_.getY();
            if (i < 0)
            {
                InitCord_.setX(InitCord_.getX() + 1);
                ActualizaBarco();
                break;
            }
            casillasBarco.push_back(player->mapa[j][i]);
            EndCord_ = Vector2D(i, j);
        }
        setTransform((InitCord_.getX() - (tamano - 1)) * 131 * player->getGM()->scale + environment().width() / 4.4f, InitCord_.getY() * 131 * player->getGM()->scale + environment().height() * 0.02f + player->nJugador * 525 * player->getGM()->scale);
        setDimensions(131 * tamano * player->getGM()->scale, 131 * player->getGM()->scale);

        break;
    };
}

Boat::~Boat() {}

void Boat::handleInput(const SDL_Event &e)
{
    if (!colocado)
    {
        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.scancode == SDL_SCANCODE_W || e.key.keysym.scancode == SDL_SCANCODE_S || e.key.keysym.scancode == SDL_SCANCODE_A || e.key.keysym.scancode == SDL_SCANCODE_D || e.key.keysym.scancode == SDL_SCANCODE_R || e.key.keysym.scancode == SDL_SCANCODE_T)
            {
                if (e.key.keysym.scancode == SDL_SCANCODE_W)
                {
                    if (InitCord_.getY() - 1 > -1)
                        InitCord_.setY(InitCord_.getY() - 1);
                }
                else if (e.key.keysym.scancode == SDL_SCANCODE_S)
                {
                    if (InitCord_.getY() + 1 < player->mapaSizeY)
                        InitCord_.setY(InitCord_.getY() + 1);
                }
                else if (e.key.keysym.scancode == SDL_SCANCODE_A)
                {
                    if (InitCord_.getX() - 1 > -1)
                        InitCord_.setX(InitCord_.getX() - 1);
                }
                else if (e.key.keysym.scancode == SDL_SCANCODE_D)
                {
                    if (InitCord_.getX() + 1 < player->mapaSizeX)
                        InitCord_.setX(InitCord_.getX() + 1);
                }
                else if (e.key.keysym.scancode == SDL_SCANCODE_R)
                {
                    if (barcodir % 2)
                        setDimensions(131 * player->getGM()->scale, 131 * tamano * player->getGM()->scale);
                    else
                        setDimensions(131 * tamano * player->getGM()->scale, 131 * player->getGM()->scale);

                    int a = barcodir + 1;
                    barcodir = (direccionBarco)(a % 4);
                    std::string aux = "./resources/images/Barco" + std::to_string(tamano) + std::to_string(barcodir) + ".png";
                    setTexture(aux);
                }
                else if (e.key.keysym.scancode == SDL_SCANCODE_T)
                {
                    if (Colocable())
                        colocado = true;
                }

                switch (barcodir)
                {
                case direccionBarco::norte:
                    setTransform(InitCord_.getX() * 131 * player->getGM()->scale + environment().width() / 4.4f, (InitCord_.getY() - (tamano - 1)) * 131 * player->getGM()->scale + environment().height() * 0.02f + player->nJugador * 525 * player->getGM()->scale);
                    break;
                case direccionBarco::sur:
                    setTransform(InitCord_.getX() * 131 * player->getGM()->scale + environment().width() / 4.4f, InitCord_.getY() * 131 * player->getGM()->scale + environment().height() * 0.02f + player->nJugador * 525 * player->getGM()->scale);
                    break;
                case direccionBarco::este:
                    setTransform(InitCord_.getX() * 131 * player->getGM()->scale + environment().width() / 4.4f, InitCord_.getY() * 131 * player->getGM()->scale + environment().height() * 0.02f + player->nJugador * 525 * player->getGM()->scale);
                    break;
                case direccionBarco::oeste:
                    setTransform((InitCord_.getX() - (tamano - 1)) * 131 * player->getGM()->scale + environment().width() / 4.4f, InitCord_.getY() * 131 * player->getGM()->scale + environment().height() * 0.02f + player->nJugador * 525 * player->getGM()->scale);
                    break;
                };
            }
            ActualizaBarco();
        }
    }
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

bool Boat::Colocable()
{

    bool finded = false;
    bool seSale = false;

    // Comprueba que ninguna casilla de las que contiene el barco coincide con las de alguno ya colocado
    for (auto &casillaBarco : casillasBarco)
    {
        for (auto &b : player->boats)
        {
            if (b != this)
            {
                for (auto &c : b->casillasBarco)
                {
                    if (casillaBarco == c)
                    {
                        return false;
                    }
                    if (casillaBarco->posicion.getX() < 0 || casillaBarco->posicion.getX() > player->mapaSizeX || casillaBarco->posicion.getY() < 0 || casillaBarco->posicion.getY() > player->mapaSizeY)
                        seSale = true;
                }
            }
        }
    }
    if (!seSale)
        return true;
    else
        return false;
}

// Recorre todas las casillas del barco y si encuentra una que no esta tocada es que no se ha hundido
bool Boat::estaHundido()
{
    for (auto &c : casillasBarco)
    {
        if (c->estadoActual == Casilla::estado::predeterminado)
            return false;
    }
    return true;
}