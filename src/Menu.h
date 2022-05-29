#ifndef MENU_H_
#define MENU_H_

#include "GameObject.h"
#include "Button.h"

class Game;

class Menu : public GameObject
{
public:
    Menu(Game *GM);
    virtual ~Menu();

    void handleInput(const SDL_Event &) override;
    void update() override;

private:
    Game *gameManager;

    Button *a;
    Button *b;
};
#endif