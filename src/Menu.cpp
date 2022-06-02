#include "Menu.h"
#include "Environment.h"
#include "Game.h"

Menu::Menu(GameClient *GM) : GameObject()
{
	gameManager = GM;

	a = new Button(gameManager, "play");
	a->setTexture("./resources/images/PlayButton.png");
	a->setDimensions(680 * gameManager->scale, 184 * gameManager->scale);
	a->setTransform(environment().width() / 2 - a->getDimensions().getX() / 2, environment().height() / 2 - a->getDimensions().getY() / 2 - a->getDimensions().getY() / 2);

	gameManager->addObjectMenuList(a);

	b = new Button(GM, "quit");
	b->setTexture("./resources/images/QuitButton.png");
	b->setDimensions(680 * GM->scale, 184 * GM->scale);
	b->setTransform(environment().width() / 2 - b->getDimensions().getX() / 2, environment().height() / 2 - b->getDimensions().getY() / 2 + b->getDimensions().getY() / 2);

	gameManager->addObjectMenuList(b);
}

Menu::~Menu() {}

void Menu::handleInput(const SDL_Event &e)
{
}

void Menu::update()
{
}