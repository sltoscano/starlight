
#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>
#include <vector>
#include "../render.h"


class Entity
{
public:
    Entity(b2World* world, RenderCallback* render);

    int GetID() { return _entityID; }

    virtual void Step() = 0;
    virtual void Draw() = 0;
    virtual void Keyboard(int key) = 0;

    virtual ~Entity();

protected:
    int _entityID;
    b2Body* _body;
    b2World* _world;
    RenderCallback* _render;
};

typedef std::vector<Entity*> EntityList;

enum EntityType
{
    e_asteroid,
    e_bullet,
    e_ship
};

Entity* Create(EntityType type, b2World* world, RenderCallback* render);

#endif
