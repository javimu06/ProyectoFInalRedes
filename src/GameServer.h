#ifndef GAMESERVER_H_
#define GAMESERVER_H_

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

class GameServer{
    public:
    GameServer(const char * s, const char * p): socket(s, p)
    {
        socket.bind();
    };
    /**
     *  Thread principal del servidor recive mensajes en el socket y
     *  lo distribuye a los clientes. Mantiene actualizada la lista de clientes
     */
    void do_games();
    private:
    /**
     *  Lista de clientes conectados al servidor de Chat, representados por
     *  su socket
     */
    std::vector<std::unique_ptr<Socket>> clients;

    /**
     * Socket del servidor
     */
    Socket socket;
};

#endif