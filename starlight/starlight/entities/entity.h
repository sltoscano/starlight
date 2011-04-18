
#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>
#include <vector>


class Entity
{
public:
    Entity(b2World* world);

    virtual void Step() = 0;
    virtual void Keyboard() = 0;

    virtual ~Entity();

protected:
    int _entityID;
    b2Body* _body;
    b2World* _world;
};

typedef std::vector<Entity*> EntityList;

enum EntityType
{
    e_asteroid,
    e_bullet,
    e_ship
};

Entity* Create(EntityType type, b2World* world);

#endif
