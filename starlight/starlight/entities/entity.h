
#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>
#include <vector>


class Entity
{
public:
    int GetID() { return _entityID; }
    b2Body* GetBody() { return _body; }

    virtual void Step() = 0;
    virtual void Keyboard(int key) = 0;
    virtual const b2Color& GetColor() = 0;

    virtual ~Entity();

protected:
    Entity(b2World* world);
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
