
#include "entity.h"
#include "asteroid.h"
#include "bullet.h"
#include "ship.h"


Entity::Entity(b2World* world, RenderCallback* render) :
    _entityID(-1),
    _body(NULL),
    _world(world),
    _render(render)
{
}

Entity::~Entity()
{
}

Entity* Create(EntityType type, b2World* world, RenderCallback* render)
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
            entity = new Ship(world, render);
            break;

        default:
            break;
    }

    return entity;
}
