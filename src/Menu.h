#ifndef MENU_H_
#define MENU_H_

#include "GameObject.h"
#include "Button.h"

class GameClient;

class Menu : public GameObject
{
public:
    Menu(GameClient *GM);
    virtual ~Menu();

    void handleInput(const SDL_Event &) override;
    void update() override;

private:
    GameClient *gameManager;

    Button *a;
    Button *b;
};
#endif