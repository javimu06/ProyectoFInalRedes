#ifndef GAMEMESSAGE_H_
#define GAMEMESSAGE_H_

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

#include "Game.h"

class GameMessage: public Serializable{

    public:
static const size_t MESSAGE_SIZE = sizeof(char) * 88 + sizeof(uint8_t) + sizeof(int) * 2;

    static const size_t NICK_SIZE = 8;

    static const size_t MSG_SIZE = 80;

    enum MessageType
    {
        LOGIN   = 0,
        MESSAGE = 1,
        LOGOUT  = 2,
        ACTUALIZACASILLA = 3
    };

    GameMessage(){};

    GameMessage(const std::string& n, const std::string& m):nick(n),message(m){};

    void to_bin();

    int from_bin(char * bobj);

    uint8_t type;

    std::string nick;
    std::string message;
    int x, y;

};



#endif