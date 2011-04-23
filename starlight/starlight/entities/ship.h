
#ifndef SHIP_H
#define SHIP_H

#include "entity.h"
#include "../util.h"

#define  GLUT_KEY_LEFT                      0x0064
#define  GLUT_KEY_UP                        0x0065
#define  GLUT_KEY_RIGHT                     0x0066
#define  GLUT_KEY_DOWN                      0x0067


static b2Vec2 rad2vec(float r, float m = 1) {
    return b2Vec2(cosf(r)*m,sinf(r)*m);
}

class Ship : public Entity
{
public:
    Ship(b2World* world, RenderCallback* render) : Entity(world, render)
    {
        _entityID = 0;

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

    void Keyboard(int key)
    {
		switch (key)
		{
            case GLUT_KEY_UP:
                if (_body)
                {
                    _thrust += 0.5f;
                    _thrust = b2Clamp(_thrust, 0.0f, 50.0f);
                    b2Vec2 vec(rad2vec(_body->GetAngle(), _thrust));
                    _body->SetLinearVelocity(vec);

                    _body->SetAngularVelocity(0.0f);
                }
                break;
            case GLUT_KEY_DOWN:
                if (_body)
                {
                    _thrust -= 0.5f;
                    _thrust = b2Clamp(_thrust, 0.0f, 50.0f);
                    b2Vec2 vec(rad2vec(_body->GetAngle(), _thrust));
                    _body->SetLinearVelocity(vec);

                    _body->SetAngularVelocity(0.0f);
                }
                break;
            case GLUT_KEY_LEFT:
                if (_body)
                {
                    _body->SetAngularVelocity(1.5f);
                }
                break;
            case GLUT_KEY_RIGHT:
                if (_body)
                {
                    _body->SetAngularVelocity(-1.5f);
                }
                break;
		}
    }

    ~Ship()
    {
        _world->DestroyBody(_body);
        _body = NULL;
    }

private:
    b2PolygonShape _polygon;
    float _thrust;
};

#endif
