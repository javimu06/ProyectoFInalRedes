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

	alloc_data(MESSAGE_SIZE);

	memset(_data, 0, MESSAGE_SIZE);

	// Serializar los campos type, nick y message en el buffer _data

	char *tmp = _data;

	memcpy(tmp, &type, sizeof(type));

	tmp += sizeof(type);

	memcpy(tmp, nick.c_str(), sizeof(char) * NICK_SIZE);

	tmp += sizeof(char) * NICK_SIZE;

	memcpy(tmp, message.c_str(), sizeof(char) * message.length());

	tmp += sizeof(char) * MSG_SIZE;

	memcpy(tmp, &x, sizeof(int));

	tmp += sizeof(int);
	
	memcpy(tmp, &y, sizeof(int));

	// no ahce falta ya que no vamos a continuar serializando
}

int GameMessage::from_bin(char *bobj)
{
	alloc_data(MESSAGE_SIZE);

	memcpy(static_cast<void *>(_data), bobj, MESSAGE_SIZE);

	// Reconstruir la clase usando el buffer _data

	char *tmp = _data;

	memcpy(&type, tmp, sizeof(int8_t));

	tmp += sizeof(int8_t);

	nick.resize(sizeof(char) * 8, '\0');

	memcpy(&nick[0], tmp, sizeof(char) * 8);

	tmp += sizeof(char) * 8;

	message.resize(sizeof(char) * 80, '\0');

	memcpy(&message[0], tmp, sizeof(char) * 80);

	tmp += sizeof(char) * 80;

	memcpy(&x, tmp, sizeof(int));

	tmp += sizeof(int);
	
	memcpy(&y, tmp, sizeof(int));

	return 0;
}

