
#include "entity.h"
#include "asteroid.h"
#include "bullet.h"
#include "ship.h"


Entity::Entity(b2World* world) :
    _entityID(-1),
    _body(NULL),
    _world(world)
{
}

Entity::~Entity()
{
}

Entity* Create(EntityType type, b2World* world)
{
    Entity* entity = NULL;

    switch (type)
    {
        /*
        case e_asteroid:
            entity = new Asteroid;
            break;
        case e_bullet:
            entity = new Bullet;
            break;
        */
        case e_ship:
            entity = new Ship(world);
            break;

        default:
            break;
    }

    return entity;
}
