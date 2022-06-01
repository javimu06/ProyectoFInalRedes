#include "GameMessage.h"

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

void GameMessage::to_bin()

{

	if (type == MessageType::MESSAGE){

		alloc_data(MESSAGE_SIZE);
		char *tmp = _data;

		memcpy(tmp, &type, sizeof(type));
		tmp += sizeof(type);
		
		memcpy(tmp, nick.c_str(), sizeof(char) * NICK_SIZE);
		tmp += sizeof(char) * NICK_SIZE;

		memcpy(tmp, message.c_str(), sizeof(char) * message.length());
	}
	else //Login, loggout
	{

		alloc_data(sizeof(type) + sizeof(char) * NICK_SIZE); //solo lleva el tipo de mensaje y el nick
		char *tmp = _data;
		//type
		memcpy(tmp, &type, sizeof(type));
		tmp += sizeof(type);
		//nick
		memcpy(tmp, nick.c_str(), sizeof(char) * NICK_SIZE);
		tmp += sizeof(char) * NICK_SIZE;

	}
}

int GameMessage::from_bin(char *data)
{

	//memcpy(static_cast<void *>(_data), bobj, MESSAGE_SIZE);
	char *tmp = data;
	std::cout << "from bin\n";
	memcpy(&type, tmp, sizeof(type));
	std::cout << "from bin\n";
	tmp += sizeof(type);

	if (type == MessageType::MESSAGE){
		std::cout << "message from bin\n";
		
		nick.resize(sizeof(char) * 8, '\0');

		memcpy(&nick[0], tmp, sizeof(char) * 8);
		tmp += sizeof(char) * 8;	

		message.resize(sizeof(char) * 80, '\0');

		memcpy(&message[0], tmp, sizeof(char) * 80);
	}
	else //login Logout, etc
	{
		std::cout << "login or logout from bin\n";

		nick.resize(sizeof(char) * 8, '\0');

		memcpy(&nick[0], tmp, sizeof(char) * 8);
		tmp += sizeof(char) * 8;	
	}



	//alloc_data(MESSAGE_SIZE);


	// Reconstruir la clase usando el buffer _data


	//memcpy(static_cast<void *>(_data), bobj, MESSAGE_SIZE);




	// tmp += sizeof(char) * 80;

	// memcpy(&x, tmp, sizeof(int));

	// tmp += sizeof(int);
	
	// memcpy(&y, tmp, sizeof(int));

	return 0;
}

