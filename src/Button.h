#ifndef BUTTON_H_
#define BUTTON_H_

#include "GameObject.h"

class GameClient;

class Button: public GameObject {
public:
    Button(GameClient* G, std::string fc);
    virtual ~Button();

    void handleInput(const SDL_Event &) override;
    void update() override;


private:
    GameClient* actualGame_;
    std::string function;

};
#endif