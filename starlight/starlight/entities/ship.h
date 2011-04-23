
#ifndef SHIP_H
#define SHIP_H

#include "entity.h"
#include "../util.h"


class Ship : public Entity
{
public:
    Ship(b2World* world, RenderCallback* render) : Entity(world, render)
    {
        b2BodyDef bd;
        bd.type = b2_dynamicBody;

        bd.position.Set(1.0f, 1.0f);
        bd.angle = 0;

        _body = _world->CreateBody(&bd);

        b2FixtureDef fd;

        // Shape of ship
		{
			b2Vec2 vertices[3];

			vertices[0].Set(-0.75f, -0.4f);
			vertices[1].Set(0.5f, 0.0f);
			vertices[2].Set(-0.75f, 0.4f);

            _polygon.Set(vertices, 3);
            fd.shape = &_polygon;
		}

        fd.density = 1.0f;
        fd.friction = 0.3f;
        _body->CreateFixture(&fd);
    }

    void Step()
    {
    }
    
    void Draw()
    {
        for (b2Fixture* f = _body->GetFixtureList(); f; f = f->GetNext())
		{
            const b2Color& color = b2Color(0.5f, 0.5f, 0.5f);
            Util::DrawFixture(f, color, _render);
        }
    }

    void Keyboard()
    {
    }

    ~Ship()
    {
        _world->DestroyBody(_body);
        _body = NULL;
    }

private:
    b2PolygonShape _polygon;
};

#endif
