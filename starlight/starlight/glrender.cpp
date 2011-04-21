
#include "glrender.h"
#include <freeglut/GL/freeglut.h>


void GLRenderCallback::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
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
