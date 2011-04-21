
#ifndef RENDER_H
#define RENDER_H

#include <Box2D/Box2D.h>


class RenderCallback
{
public:

    RenderCallback() {}
	virtual ~RenderCallback() {}

    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) = 0;
};

#endif
