
#ifndef SHIP_H
#define SHIP_H

#include "entity.h"
#include "../util.h"

#define  GLUT_KEY_LEFT                      0x0064
#define  GLUT_KEY_UP                        0x0065
#define  GLUT_KEY_RIGHT                     0x0066
#define  GLUT_KEY_DOWN                      0x0067


class Ship : public Entity
{
public:
    Ship(b2World* world) : Entity(world)
    {
        _entityID = 0;
        _color.Set(0.5f, 0.5f, 0.5f);

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

    void Keyboard(int key)
    {
		switch (key)
		{
            case GLUT_KEY_UP:
                if (_body)
                {
                    _thrust += 0.5f;
                    _thrust = b2Clamp(_thrust, 0.0f, 50.0f);
                    b2Vec2 vec(Util::Rad2Vec(_body->GetAngle(), _thrust));
                    _body->SetLinearVelocity(vec);

                    _body->SetAngularVelocity(0.0f);
                }
                break;
            case GLUT_KEY_DOWN:
                if (_body)
                {
                    _thrust -= 0.5f;
                    _thrust = b2Clamp(_thrust, 0.0f, 50.0f);
                    b2Vec2 vec(Util::Rad2Vec(_body->GetAngle(), _thrust));
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

    const b2Color& GetColor()
    {
        return _color;
    }

    ~Ship()
    {
        _world->DestroyBody(_body);
        _body = NULL;
    }

private:
    b2Color _color;
    b2PolygonShape _polygon;
    float _thrust;
};

#endif
