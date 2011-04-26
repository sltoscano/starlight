
#ifndef GLRENDER_H
#define GLRENDER_H

#include "render.h"


class GLRenderCallback : public RenderCallback
{
public:
    void Draw(Entity* entity);
};

#endif
