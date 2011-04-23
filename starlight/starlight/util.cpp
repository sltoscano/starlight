
#include "util.h"


namespace Util
{
    void DrawFixture(const b2Fixture* fixture, const b2Color& color, RenderCallback* render)
    {
        const b2Transform& xf = fixture->GetBody()->GetTransform();
        
        switch (fixture->GetType())
        {
            case b2Shape::e_polygon:
            {
                b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
                int32 vertexCount = poly->m_vertexCount;
                b2Assert(vertexCount <= b2_maxPolygonVertices);
                b2Vec2 vertices[b2_maxPolygonVertices];
                
                for (int32 i = 0; i < vertexCount; ++i)
                {
                    vertices[i] = b2Mul(xf, poly->m_vertices[i]);
                }
                
                render->DrawSolidPolygon(vertices, vertexCount, color);
            }
            case b2Shape::e_circle:
            case b2Shape::e_unknown:
            default:
                break;
        }
    }
}
