
#ifndef UTIL_H
#define UTIL_H

#include <Box2D/Box2D.h>
#include "render.h"


namespace Util
{
    void DrawFixture(const b2Fixture* fixture, const b2Color& color, RenderCallback* render);
}

#endif
