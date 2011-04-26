
#ifndef RENDER_H
#define RENDER_H

#include "entities/entity.h"


class RenderCallback
{
public:
    RenderCallback() {}
    virtual ~RenderCallback() {}

    virtual void Draw(Entity* entity) = 0;
};

#endif
