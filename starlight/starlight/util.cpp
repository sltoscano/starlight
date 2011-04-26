
#include "util.h"


namespace Util
{
    b2Vec2 Rad2Vec(float r, float m)
    {
        return b2Vec2(cosf(r) * m, sinf(r) * m);
    }
}
