#include "Game.h"
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Environment.h"
#include "GameObject.h"

#include "Button.h"
#include "Menu.h"

void GameMessage::to_bin()
{
	if (type == MessageType::MESSAGE)
	{

		alloc_data(MESSAGE_SIZE);
		char *tmp = _data;

		memcpy(tmp, &type, sizeof(type));
		tmp += sizeof(type);

		memcpy(tmp, nick.c_str(), sizeof(char) * NICK_SIZE);
		tmp += sizeof(char) * NICK_SIZE;

		memcpy(tmp, message.c_str(), sizeof(char) * message.length());
	}
	else if (type == MessageType::CHECKTILE)
	{

		alloc_data(sizeof(type) + sizeof(char) * NICK_SIZE + sizeof(int) * 2);
		char *tmp = _data;
		memcpy(tmp, &type, sizeof(type));
		tmp += sizeof(type);
		memcpy(tmp, nick.c_str(), sizeof(char) * NICK_SIZE);
		tmp += sizeof(char) * NICK_SIZE;
		memcpy(tmp, &x, sizeof(int16_t));
		tmp += sizeof(int16_t);
		memcpy(tmp, &y, sizeof(int16_t));
	}
	else if (type == MessageType::CHECKEDTILE)
	{

		alloc_data(sizeof(type) + sizeof(char) * NICK_SIZE + sizeof(int16_t) * 3);
		char *tmp = _data;
		memcpy(tmp, &type, sizeof(type));
		tmp += sizeof(type);
		memcpy(tmp, nick.c_str(), sizeof(char) * NICK_SIZE);
		tmp += sizeof(char) * NICK_SIZE;
		memcpy(tmp, &x, sizeof(int16_t));
		tmp += sizeof(int16_t);
		memcpy(tmp, &y, sizeof(int16_t));
		tmp += sizeof(int16_t);
		memcpy(tmp, &b, sizeof(int16_t));
	}
	else // Login, loggout
	{

		alloc_data(sizeof(type) + sizeof(char) * NICK_SIZE); // solo lleva el tipo de mensaje y el nick
		char *tmp = _data;
		// type
		memcpy(tmp, &type, sizeof(type));
		tmp += sizeof(type);
		// nick
		memcpy(tmp, nick.c_str(), sizeof(char) * NICK_SIZE);
		tmp += sizeof(char) * NICK_SIZE;
	}
}

int GameMessage::from_bin(char *data)
{

	// memcpy(static_cast<void *>(_data), bobj, MESSAGE_SIZE);
	char *tmp = data;
	memcpy(&type, tmp, sizeof(type));
	tmp += sizeof(type);

	if (type == MessageType::MESSAGE)
	{

		nick.resize(sizeof(char) * 8, '\0');

		memcpy(&nick[0], tmp, sizeof(char) * 8);
		tmp += sizeof(char) * 8;

		message.resize(sizeof(char) * 80, '\0');

		memcpy(&message[0], tmp, sizeof(char) * 80);
	}
	else if (type == MessageType::CHECKTILE)
	{

		nick.resize(sizeof(char) * 8, '\0');

		memcpy(&nick[0], tmp, sizeof(char) * 8);
		tmp += sizeof(char) * 8;

		// coordenadas
		memcpy(&x, tmp, sizeof(int16_t));
		tmp += sizeof(int16_t);
		memcpy(&y, tmp, sizeof(int16_t));
	}
	else if (type == MessageType::CHECKEDTILE)
	{

		nick.resize(sizeof(char) * 8, '\0');

		memcpy(&nick[0], tmp, sizeof(char) * 8);
		tmp += sizeof(char) * 8;
		// coordenadas
		memcpy(&x, tmp, sizeof(int16_t));
		tmp += sizeof(int16_t);
		memcpy(&y, tmp, sizeof(int16_t));
		tmp += sizeof(int16_t);
		// acierto o fallo
		memcpy(&b, tmp, sizeof(int16_t));
	}
	else // login Logout, etc
	{

		nick.resize(sizeof(char) * 8, '\0');

		memcpy(&nick[0], tmp, sizeof(char) * 8);
		tmp += sizeof(char) * 8;
	}
	return 0;
}

void GameClient::init(int w, int h)
{
	Environment::init("My Game", w, h);
	setup();
}

void GameClient::setup()
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
	player2->interactuable = true;

	// Background
	turnIndicator = new Image();
	turnIndicator->setTransform(0, 0);
	turnIndicator->setDimensions(240 * scale, 361 * scale);
	turnIndicator->setTexture("./resources/images/RedTurn.png");
	objs_.push_back(turnIndicator);
}

void GameClient::run()
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
			else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				restart();
				return;
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

				//#Controllar input por turnos
				if (turno)
				{
				}
				// player->handleInput(event);
				// else
				// player2->handleInput(event);
			}
		}

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
			if (turno)
				turnIndicator->setTexture("./resources/images/RedTurn.png");
			else
				turnIndicator->setTexture("./resources/images/GreenTurn.png");

			// Actualizacion de mapas y barcos
			for (auto &o : objs_)
				o->update();
			for (auto &o : objs_2)
				o->update();

			// ACTUALIZACION DE PLAYER
			if (ActualState == gameStates::puttingBoats)
			{

				if (!turno)
				{
					player->poniendoBarcos();
					//# Enviar mensaje a servidor de que estas listo para empezar la partida
					//# Enviar mensaje al servidor con tu array de barcos
					//# Controlar input por turnos
					//! Quitar el if/else de !turno y eliminar player2->poniendoBarcos();
				}
				else
				{
					// player2->poniendoBarcos();
				}
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

			// if (!turno)
			player->render();
			// else
			player2->render();

			if (ActualState == gameStates::winPlayer1)
			{
				Image *playerWin = new Image();
				playerWin->setTransform(0, 0);
				playerWin->setDimensions(1920 * scale, 1080 * scale);
				playerWin->setTexture("./resources/images/PlayerOneWins.png");
				objs_2.push_back(playerWin);
			}
			else if (ActualState == gameStates::winPlayer2)
			{
				Image *playerWin = new Image();
				playerWin->setTransform(0, 0);
				playerWin->setDimensions(1920 * scale, 1080 * scale);
				playerWin->setTexture("./resources/images/PlayerTwoWins.png");
				objs_2.push_back(playerWin);
			}
		}

		environment().presentRenderer();
		Uint32 frameTime = environment().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

	// se ha salido de la aplicacion

	logout();
}

void GameClient::shutdown()
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

void GameClient::restart()
{
	// shutdown();
	// setup();
}

// void Game::setGameClient(GameClient* gc_){
// 	gc = gc_;
// }

void GameClient::changeGameState(gameStates newGS)
{
	ActualState = newGS;
}

void GameClient::addObjectList(GameObject *a) { objs_2.push_back(a); }
void GameClient::addObjectMenuList(GameObject *a) { MainMenuObjs_2.push_back(a); }

void GameServer::do_games()
{

	while (true)
	{
		Socket *client;
		GameMessage msg;

		int r = socket.recv(msg, client);

		if (r < 0)
		{

			continue;
		}

		// while (true)

		//{

		int count = 0;

		std::unique_ptr<Socket> soc(client);

		if (msg.type == GameMessage::LOGIN)
		{
			// soc = std::unique_ptr<Socket>(client) ;
			clients.push_back(std::move(soc));
			std::cout << msg.nick.c_str() << " logeado " << std::endl;
		}
		else if (msg.type == GameMessage::LOGOUT)
		{
			for (auto &&sock : clients)
			{
				if ((*sock == *client))
				{
					clients.erase(clients.begin() + count);
					break;
				}
				count++;
			}
			std::cout << msg.nick.c_str() << " desconectado" << std::endl;
		}
		else if (msg.type == GameMessage::READY)
		{
			for (auto &&sock : clients)
			{
				if ((*sock == *client))
				{
					std::cout << msg.nick.c_str() << " esta listo" << std::endl;
					// clients.erase(clients.begin() + count);
					break;
				}
			}
		}
		else if (msg.type == GameMessage::MESSAGE)
		{
			for (auto &&sock : clients)
			{
				if (!(*sock == *client))
					socket.send(msg, *sock);
			}
			std::cout << msg.nick.c_str() << " mensaje enviado" << std::endl;
		}
		else if (msg.type == GameMessage::CHECKTILE){
			for (auto &&sock : clients)
			{
				if (!(*sock == *client))
					socket.send(msg, *sock);
			}
			std::cout << msg.nick.c_str() << " CHECKTILE enviado" << std::endl;
		}
		else if (msg.type == GameMessage::CHECKEDTILE){
			for (auto &&sock : clients)
			{
				if (!(*sock == *client))
					socket.send(msg, *sock);
			}
			std::cout << msg.nick.c_str() << " CHECKTILE2 enviado" << std::endl;
		}

		std::cout << "Conectado: " << clients.size() << std::endl;
	}
}

// el cliente
void GameClient::login()
{
	GameMessage em(nick);
	em.type = GameMessage::LOGIN;
	socket.send(em, socket);
}

void GameClient::logout()
{
	GameMessage em(nick);
	em.type = GameMessage::LOGOUT;
	socket.send(em, socket);
}
void GameClient::listo()
{
	GameMessage em(nick);
	em.type = GameMessage::READY;
	socket.send(em, socket);
}
void GameClient::WriteMesage(std::string msg)
{
	GameMessage em(nick, msg);
	em.type = GameMessage::MESSAGE;
	socket.send(em, socket);
}

void GameClient::CheckTile(int x, int y)
{
	std::cout << x << " " << y << " "
			  << "tile1\n";
	GameMessage em(nick, x, y);
	em.type = GameMessage::CHECKTILE;
	socket.send(em, socket);
}

void GameClient::CheckTile2(int x, int y, int a)
{
	std::cout << x << " " << y << " " << a << "tile2\n";
	GameMessage em(nick, x, y, a);
	em.type = GameMessage::CHECKEDTILE;
	socket.send(em, socket);
}

void GameClient::input_thread()
{
	// este es el ciclo del juego principal, aqui vamso a iniciar el game
	// abrir el game
	init(1920 * scale, 1080 * scale);
	// g->setGameClient(this*);
	run();
	shutdown();
}

void GameClient::net_thread()

{

	while (true)

	{
		// Recibir Mensajes de red
		// Mostrar en pantalla el mensaje de la forma "nick: mensaje"
		GameMessage em;
		socket.recv(em);

		if (em.type == GameMessage::MessageType::MESSAGE)
		{
			if (em.nick != nick)
			{
				std::cout << em.nick << ": " << em.message << " procesado 1\n";
			}
		}
		else if (em.type == GameMessage::MessageType::CHECKTILE)
		{
			player->actualizaCasilla(Vector2D(em.x, em.y));
		}
		else if (em.type == GameMessage::MessageType::CHECKEDTILE)
		{
			std::cout << em.x << " " << em.y << " " << em.b << "  procesado 2\n";
			if (em.b == 1)
			{
				player2->cambiaCasilla(Vector2D(em.x, em.y), Casilla::tocado);
			}
			else if (em.b == 0)
			{
				player2->cambiaCasilla(Vector2D(em.x, em.y), Casilla::agua);
				turno = !turno;
			}
		}
		else
		{
			std::cout << em.message << "\n";
		}
	}
}
