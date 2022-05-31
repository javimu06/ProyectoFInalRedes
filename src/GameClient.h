#ifndef GAMECLIENT_H_
#define GAMECLIENT_H_

#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "macros.h"
#include "Player.h"

#include "Serializable.h"
#include "Socket.h"

#include "GameMessage.h"
#include "Game.h"

class GameObject;
class SDL_Renderer;

class GameClient
{

public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    GameClient(const char *s, const char *p, const char *n) : socket(s, p),
                                                              nick(n){};

    /**
     *  Envía el mensaje de login al servidor
     */
    void login();

    /**
     *  Envía el mensaje de logout al servidor
     */
    void logout();

    /**
     *  Rutina principal para el Thread de E/S. Lee datos de STDIN (std::getline)
     *  y los envía por red vía el Socket.
     */
    void input_thread();

    /**
     *  Rutina del thread de Red. Recibe datos de la red y los "renderiza"
     *  en STDOUT
     */
    void net_thread();

    Game *g;

private:
    /**
     * Socket para comunicar con el servidor
     */
    Socket socket;

    /**
     * Nick del usuario
     */
    std::string nick;
};

#endif