#ifndef BUTTON_H_
#define BUTTON_H_

#include "GameObject.h"

class Game;

class Button: public GameObject {
public:
    Button(Game* G, std::string fc);
    virtual ~Button();

    void handleInput(const SDL_Event &) override;
    void update() override;


private:
    Game* actualGame_;
    std::string function;

};
#endif