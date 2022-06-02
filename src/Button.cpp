#include "Button.h"
#include "Environment.h"
#include "Game.h"

Button::Button(GameClient *G, std::string fct) : GameObject()
{
	actualGame_ = G;
	function = fct;
}

Button::~Button() {}

void Button::handleInput(const SDL_Event &e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (function == "play")
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			SDL_Point mousePoint = {x, y};
			if (SDL_PointInRect(&mousePoint, &dest))
				actualGame_->changeGameState(GameClient::gameStates::puttingBoats);
		} else if (function == "quit")
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			SDL_Point mousePoint = {x, y};
			if (SDL_PointInRect(&mousePoint, &dest))
				actualGame_->changeGameState(GameClient::gameStates::quit);
		}
	}
}

void Button::update()
{
}