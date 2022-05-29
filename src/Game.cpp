#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Environment.h"
#include "GameObject.h"

#include "Tank.h"
#include "Button.h"
#include "Menu.h"
#include "Image.h"
#include "Player.h"

Game::Game()
{
	ActualState = gameStates::mainMenu;
}

Game::~Game() {}

void Game::init(int w, int h)
{
	Environment::init("My Game", w, h);

	Menu *m = new Menu(this);
	m->setTransform(0, 0);
	m->setDimensions(1920 * scale, 1080 * scale);
	m->setTexture("./resources/images/MainMenuBackground.png");

	MainMenuObjs_.push_back(m);

	 Tank *t = new Tank(this);
	 t->setTransform(environment().width() / 2, environment().height() / 2);
	// t->setDimensions(100 * scale, 100 * scale);
	// t->setTexture("./resources/images/tank.png");
	// t->setKeys(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D);
	// t->setSpeed(1);

	// objs_.push_back(t);

	Image *background = new Image();
	background->setTransform(0, 0);
	background->setDimensions(1920 * scale, 1080 * scale);
	background->setTexture("./resources/images/Background2.png");
	objs_.push_back(background);

	Player *player = new Player(this);
	player->setTransform(0, 0);
	objs_2.push_back(player);
}

void Game::run()
{
	SDL_Event event;

	// animation loop
	while (ActualState != gameStates::quit)
	{
		Uint32 startTime = environment().currRealTime();

		// handle input
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				ActualState = gameStates::quit;
				continue;
			}
			if (ActualState == gameStates::mainMenu)
			{
				for (auto &o : MainMenuObjs_)
					o->handleInput(event);
				for (auto &u : MainMenuObjs_2)
					u->handleInput(event);
			}
			else
			{
				for (auto &o : objs_)
					o->handleInput(event);
				for (auto &o : objs_2)
					o->handleInput(event);
			}
		}

		// update
		if (ActualState == gameStates::mainMenu)
		{
			for (auto &o : MainMenuObjs_)
				o->update();
			for (auto &u : MainMenuObjs_2)
				u->update();
		}
		else
		{
			for (auto &o : objs_)
				o->update();
			for (auto &o : objs_2)
				o->update();
		}
		environment().clearRenderer();

		// render

		if (ActualState == gameStates::mainMenu)
		{
			for (auto &o : MainMenuObjs_)
				o->render();
			for (auto &u : MainMenuObjs_2)
				u->render();
		}
		else
		{
			for (auto &o : objs_)
				o->render();
			for (auto &o : objs_2)
				o->render();
		}

		environment().presentRenderer();
		Uint32 frameTime = environment().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}
}

void Game::shutdown()
{
	for (unsigned int i = 0; i < objs_.size(); i++)
		delete objs_[i];
	for (unsigned int i = 0; i < objs_2.size(); i++)
		delete objs_2[i];
	for (unsigned int i = 0; i < MainMenuObjs_.size(); i++)
		delete MainMenuObjs_[i];
	for (unsigned int i = 0; i < MainMenuObjs_2.size(); i++)
		delete MainMenuObjs_2[i];
}

void Game::changeGameState(gameStates newGS)
{

	ActualState = newGS;
}

void Game::addObjectList(GameObject *a) { objs_2.push_back(a); }
void Game::addObjectMenuList(GameObject *a) { MainMenuObjs_2.push_back(a); }