#ifndef GAME_H_
#define GAME_H_

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

class GameObject;
class SDL_Renderer;

class Game
{
public:
    Game();
    virtual ~Game();

    void init(int w, int h);
    void setup();
    void run();
    void shutdown();
    void restart();

    float scale = 0.74f;

    enum gameStates
    {
        playing,
        mainMenu,
        quit,
        puttingBoats,
        winPlayer1,
        winPlayer2
    };

    gameStates ActualState;

    void changeGameState(gameStates newGS);

    void addObjectList(GameObject *a);
    void addObjectMenuList(GameObject *a);

    bool turno;

private:
    std::vector<GameObject *> objs_;
    std::vector<GameObject *> objs_2;
    std::vector<GameObject *> MainMenuObjs_;
    std::vector<GameObject *> MainMenuObjs_2;

    Player *player;
    Player *player2;
};

class GameMessage: public Serializable{

    public:
static const size_t MESSAGE_SIZE = sizeof(char) * 88 + sizeof(uint8_t);

    static const size_t NICK_SIZE = 8;

    static const size_t MSG_SIZE = 80;

    enum MessageType
    {
        LOGIN   = 0,
        MESSAGE = 1,
        LOGOUT  = 2
    };

    GameMessage(){};

    GameMessage(const std::string& n, const std::string& m):nick(n),message(m){};

    void to_bin();

    int from_bin(char * bobj);

    uint8_t type;

    std::string nick;
    std::string message;

};




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

class GameClient{

 public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    GameClient(const char * s, const char * p, const char * n):socket(s, p),
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