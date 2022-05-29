#ifndef IMAGE_H_
#define IMAGE_H_

#include "GameObject.h"
#include "Image.h"


class Image : public GameObject
{
public:
    Image();
    virtual ~Image();

    void handleInput(const SDL_Event &) override;
    void update() override;

};
#endif