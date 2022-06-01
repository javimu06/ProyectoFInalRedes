#include "Game.h"
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Environment.h"
#include "GameObject.h"

#include "Tank.h"
#include "Button.h"
#include "Menu.h"
#include "Image.h"

//#include "../servidores/Chat.h"

Game::Game()
{
}

Game::~Game() {}

void Game::init(int w, int h)
{
	Environment::init("My Game", w, h);
	setup();
}

void Game::setup()
{
	ActualState = gameStates::mainMenu;

	// Menu
	Menu *m = new Menu(this);
	m->setTransform(0, 0);
	m->setDimensions(1920 * scale, 1080 * scale);
	m->setTexture("./resources/images/MainMenuBackground.png");
	MainMenuObjs_.push_back(m);

	// Background
	Image *background = new Image();
	background->setTransform(0, 0);
	background->setDimensions(1920 * scale, 1080 * scale);
	background->setTexture("./resources/images/Background2.png");
	objs_.push_back(background);

	// Players
	player = new Player(this, 0);
	player->setTransform(0, 0);

	player2 = new Player(this, 1);
	player2->setTransform(0, 0);

	// ChatClient ec("127.0.0.1", "1500", "antonio");

	// std::thread net_thread([&ec](){ ec.net_thread(); });

	// ec.login();

	// ec.input_thread();
}

void Game::run()
{
}

void Game::actualiza()
{
	// Actualizacion del menu
	if (ActualState == gameStates::mainMenu)
	{
		for (auto &o : MainMenuObjs_)
			o->update();
		for (auto &u : MainMenuObjs_2)
			u->update();
	}
	else
	{
		// Actualizacion de mapas y barcos
		for (auto &o : objs_)
			o->update();
		for (auto &o : objs_2)
			o->update();

		// ACTUALIZACION DE PLAYER
		if (ActualState == gameStates::puttingBoats)
		{
			player->poniendoBarcos();
			//# Enviar mensaje a servidor de que estas listo para empezar la partida
		}
		else if (ActualState == gameStates::playing)
		{
			// Control fin de juego
			//#Enviar que jugador gano
			if (!player->tieneBarcos())
			{
				changeGameState(winPlayer2);
			}
		}
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

	delete player;
	delete player2;
}

void Game::restart()
{
	// shutdown();
	// setup();
}

void Game::changeGameState(gameStates newGS)
{
	ActualState = newGS;


}

void Game::addObjectList(GameObject *a) { objs_2.push_back(a); }
void Game::addObjectMenuList(GameObject *a) { MainMenuObjs_2.push_back(a); }
