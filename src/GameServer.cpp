#include "GameServer.h"
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

void GameServer::do_games()
{

	while (true)
	{

		/*

		 * NOTA: los clientes están definidos con "smart pointers", es necesario

		 * crear un unique_ptr con el objeto socket recibido y usar std::move

		 * para añadirlo al vector

		 */

		// Recibir Mensajes en y en función del tipo de mensaje

		// - LOGIN: Añadir al vector clients

		// - LOGOUT: Eliminar del vector clients

		// - MESSAGE: Reenviar el mensaje a todos los clientes (menos el emisor)

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

		switch (msg.type) // LOGIN = 0, MESSAGE = 1, LOGOUT = 2

		{

		case GameMessage::LOGIN:

			// soc = std::unique_ptr<Socket>(client) ;

			clients.push_back(std::move(soc));

			std::cout << msg.nick.c_str() << " logeado " << std::endl;

			break;

		case GameMessage::LOGOUT:

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

			break;

		case GameMessage::MESSAGE:

			for (auto &&sock : clients)

			{

				if (!(*sock == *client))

					socket.send(msg, *sock);
			}

			std::cout << msg.nick.c_str() << " mensaje enviado" << std::endl;

			break;

		case GameMessage::ACTUALIZACASILLA:

			for (auto &&sock : clients)
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
