
#include "glrender.h"
#include <Box2D/Box2D.h>
#include <freeglut/GL/freeglut.h>


void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.75f);
    glBegin(GL_TRIANGLE_FAN);
    for (int32 i = 0; i < vertexCount; ++i)
    {
        glVertex2f(vertices[i].x, vertices[i].y);
    }
    glEnd();
    glDisable(GL_BLEND);

    glColor4f(color.r, color.g, color.b, 1.0f);
    glBegin(GL_LINE_LOOP);
    for (int32 i = 0; i < vertexCount; ++i)
    {
        glVertex2f(vertices[i].x, vertices[i].y);
    }
    glEnd();
}

void GLRenderCallback::Draw(Entity* entity)
{
    for (b2Fixture* fixture = entity->GetBody()->GetFixtureList(); fixture; fixture = fixture->GetNext())
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

                DrawSolidPolygon(vertices, vertexCount, entity->GetColor());
            }
            case b2Shape::e_circle:
            case b2Shape::e_unknown:
            default:
                break;
        }
    }
}
