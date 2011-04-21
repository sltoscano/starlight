
#ifndef GLRENDER_H
#define GLRENDER_H

#include "render.h"
#include <Box2D/Box2D.h>


class GLRenderCallback : public RenderCallback
{
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
};

#endif
