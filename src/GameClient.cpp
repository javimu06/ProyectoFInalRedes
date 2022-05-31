#include "GameClient.h"
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

// el cliente

void GameClient::login()

{

	std::string msg;
	GameMessage em(nick, msg);

	em.type = GameMessage::LOGIN;

	socket.send(em, socket);
}

void GameClient::logout()

{

	std::string msg;

	GameMessage em(nick, msg);

	em.type = GameMessage::LOGOUT;

	socket.send(em, socket);
}

void GameClient::input_thread()

{

	while (true)
	{
		SDL_Event event;

		// animation loop
		while (g->ActualState != Game::gameStates::quit)
		{
			Uint32 startTime = environment().currRealTime();

			// handle input
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				{
					g->ActualState = Game::gameStates::quit;
					continue;
				}
				else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					g->restart();
					return;
				}
				if (g->ActualState == Game::gameStates::mainMenu)
				{
					for (auto &o : g->MainMenuObjs_)
						o->handleInput(event);
					for (auto &u : g->MainMenuObjs_2)
						u->handleInput(event);
				}
				else
				{
					for (auto &o : g->objs_)
						o->handleInput(event);
					for (auto &o : g->objs_2)
						o->handleInput(event);

					//#Controllar input por turnos
					if (!g->turno)
						g->player->handleInput(event);
					else
						g->player2->handleInput(event);
				}
			}

			g->actualiza();
			environment().clearRenderer();

			// render

			if (g->ActualState == Game::gameStates::mainMenu)
			{
				for (auto &o : g->MainMenuObjs_)
					o->render();
				for (auto &u : g->MainMenuObjs_2)
					u->render();
			}
			else
			{
				for (auto &o : g->objs_)
					o->render();
				for (auto &o : g->objs_2)
					o->render();

				// if (!turno)
				g->player->render();
				// else
				g->player2->render();

				if (g->ActualState == Game::gameStates::winPlayer1)
				{
					Image *playerWin = new Image();
					playerWin->setTransform(0, 0);
					playerWin->setDimensions(1920 * g->scale, 1080 * g->scale);
					playerWin->setTexture("./resources/images/PlayerOneWins.png");
					g->objs_2.push_back(playerWin);
				}
				else if (g->ActualState == Game::gameStates::winPlayer2)
				{
					Image *playerWin = new Image();
					playerWin->setTransform(0, 0);
					playerWin->setDimensions(1920 * g->scale, 1080 * g->scale);
					playerWin->setTexture("./resources/images/PlayerTwoWins.png");
					g->objs_2.push_back(playerWin);
				}
			}

			environment().presentRenderer();
			Uint32 frameTime = environment().currRealTime() - startTime;

			if (frameTime < 20)
				SDL_Delay(20 - frameTime);
		}

		// // Leer stdin con std::getline
		// std::string msg;
		// std::getline(std::cin, msg);
		// // Enviar al servidor usando socket
		// GameMessage em(nick, msg);
		// em.type = GameMessage::MESSAGE;
		// socket.send(em, socket);
	}
}

void GameClient::net_thread()

{

	while (true)

	{

		// Recibir Mensajes de red

		// Mostrar en pantalla el mensaje de la forma "nick: mensaje"

		GameMessage em;

		socket.recv(em);

		if (em.nick != nick)
		{

			std::cout << em.nick << ": " << em.message << "\n";
		}

		else
		{

			std::cout << em.message << "\n";
		}
	}
}
