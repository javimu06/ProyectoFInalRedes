#include <unistd.h>
#include <iostream>
#include <thread>

#include "Game.h"

void start(){
    // char buffer[256];    
    // getcwd( buffer, 256 );
    // printf("%s\n", buffer);

    Game g;

    g.init(1920*g.scale, 1080*g.scale);
    g.run();
    g.shutdown();
}



int main(int argc, char *argv[]){


if ((*argv[1]) == '1'){

    GameServer server("127.0.0.1", "7777");
    server.do_games();
}
if ((*argv[1]) == '2'){
    GameClient ec("127.0.0.1", "7777", "marco");


    //std::thread net_thread(&GameClient::net_thread, &ec);
    std::thread net_thread([&ec](){ ec.net_thread(); });
    //net_thread.join();

    ec.login();

    ec.input_thread();

}

    try {
        start();
    }
    catch(const std::string& e)
    {
        std::cerr << e << '\n';
    }
    catch(const char* e)
    {
        std::cerr << e << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "Caught an exception ok unknown type...\n";
    }
    
    return 0;
}