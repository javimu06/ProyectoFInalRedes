#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <cassert>

#include <SDL2/SDL.h>

#include "Vector2D.h"

class GameObject
{
public:
	GameObject() : tr_(), dim_(), rotation(0), text_(nullptr), textDim_() {}

	virtual ~GameObject();

	virtual void handleInput(const SDL_Event &event) = 0;
	virtual void update() = 0;

	virtual void render();

	void setTransform(const int x, const int y);
	void setDimensions(const int w, const int h);

	void setTexture(const std::string &path);
	void rotateTexture(float rotationAngle);

	SDL_Rect *getSrcRect() { return &src; }
	SDL_Rect *getDestRect() { return &dest; }
	Vector2D getDimensions();

protected:
	Vector2D tr_;
	Vector2D dim_;

	float rotation;

	SDL_Texture *text_;
	Vector2D textDim_;

	SDL_Rect src;
	SDL_Rect dest;

	void render(const SDL_Rect &src, const SDL_Rect &dest,
				const SDL_Point *p = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
};
#endif