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
				if (!turno)
					player->handleInput(event);
				else
					player2->handleInput(event);
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
				}
				else
				{
					player2->poniendoBarcos();
				}
			}
			else if (ActualState == gameStates::playing)
			{
				// Control fin de juego
				if (!player->tieneBarcos())
					ActualState = gameStates::winPlayer2;
				if (!player2->tieneBarcos())
					ActualState = gameStates::winPlayer1;
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






void GameMessage::to_bin()

{

	alloc_data(MESSAGE_SIZE);



	memset(_data, 0, MESSAGE_SIZE);



	//Serializar los campos type, nick y message en el buffer _data

	char* tmp = _data;

	memcpy(tmp, &type, sizeof(type));

	tmp += sizeof(type);



	memcpy(tmp, nick.c_str(), sizeof(char) * NICK_SIZE);

	tmp += sizeof(char) * NICK_SIZE;



	memcpy(tmp, message.c_str(), sizeof(char) * message.length());

	//tmp += sizeof(char) * MSG_SIZE;

	//no ahce falta ya que no vamos a continuar serializando



}



int GameMessage::from_bin(char * bobj){
alloc_data(MESSAGE_SIZE);

	memcpy(static_cast<void*>(_data), bobj, MESSAGE_SIZE);



	//Reconstruir la clase usando el buffer _data

	char* tmp = _data;



	memcpy(&type, tmp, sizeof(int8_t));

	tmp += sizeof(int8_t);

	nick.resize(sizeof(char) * 8, '\0');

	memcpy(&nick[0], tmp, sizeof(char) * 8);

	tmp += sizeof(char) * 8;

	message.resize(sizeof(char) * 80, '\0');

	memcpy(&message[0], tmp, sizeof(char) * 80);



	return 0;



}





void GameServer::do_games(){

	while(true){
		std::cout <<"funciono\n";

		/*

		 * NOTA: los clientes están definidos con "smart pointers", es necesario

		 * crear un unique_ptr con el objeto socket recibido y usar std::move

		 * para añadirlo al vector

		 */



		 //Recibir Mensajes en y en función del tipo de mensaje

		 // - LOGIN: Añadir al vector clients

		 // - LOGOUT: Eliminar del vector clients

		 // - MESSAGE: Reenviar el mensaje a todos los clientes (menos el emisor)
		std::cout <<"funciono1\n";

		Socket* client;
		std::cout <<"funciono2\n";

		GameMessage msg;
		std::cout <<"funciono3\n";

		int r = socket.recv(msg, client);

		std::cout <<"funciono4\n";


		if (r < 0) {
			std::cout <<"funciono5\n";

			continue;

		}
		std::cout <<"funciono\n";

		//while (true)

		//{



		int count = 0;

		std::unique_ptr<Socket> soc(client);



		switch (msg.type)		// LOGIN = 0, MESSAGE = 1, LOGOUT = 2

		{

		case GameMessage::LOGIN:

			//soc = std::unique_ptr<Socket>(client) ;

			clients.push_back(std::move(soc));

			std::cout << msg.nick.c_str() << " logeado " << std::endl;

			break;

		case  GameMessage::LOGOUT:

			for (auto&& sock : clients)

			{

				if ((*sock == *client))

				{

					clients.erase(clients.begin() + count);

					break;

				}

				count++;

			}

			std::cout << msg.nick.c_str() << " desconectado" << std::endl;



			break;

		case GameMessage::MESSAGE:

			for (auto&& sock : clients)

			{

				if (!(*sock == *client))

					socket.send(msg, *sock);

			}

			std::cout << msg.nick.c_str() << " mensaje enviado" << std::endl;

			break;

		default:

			break;

		}

		std::cout << "Conectado: " << clients.size() << std::endl;

		//	}

	}
}



//el cliente


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

		// Leer stdin con std::getline

		std::string msg;

		std::getline(std::cin, msg);



		//mensaje para desconectarse del servidor

		if (msg == "LOGOUT")

		{

			logout();

			break;

		}

		else

		{

			// Enviar al servidor usando socket

			GameMessage em(nick, msg);

			em.type = GameMessage::MESSAGE;

			socket.send(em, socket);

		}

	}

}


void GameClient::net_thread()

{

	while (true)

	{

		//Recibir Mensajes de red

		//Mostrar en pantalla el mensaje de la forma "nick: mensaje"

		GameMessage em;



		socket.recv(em);



		if (em.nick != nick) {



			std::cout << em.nick << ": " << em.message << "\n";

		}

		else {

			std::cout << em.message << "\n";

		}

	}

}
