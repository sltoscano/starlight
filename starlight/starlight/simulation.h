
#ifndef SIMULATION_H
#define SIMULATION_H

#include "common.h"
#include "render.h"
#include "entities/entity.h"
#include <Box2D/Box2D.h>


class Simulation;

struct Settings
{
    Settings() :
    hz(60.0f),
    velocityIterations(8),
    positionIterations(3),
    drawStats(1),
    drawShapes(1),
    drawJoints(1),
    drawAABBs(0),
    drawPairs(0),
    drawContactPoints(0),
    drawContactNormals(0),
    drawContactForces(0),
    drawFrictionForces(0),
    drawCOMs(0),
    enableWarmStarting(1),
    enableContinuous(1),
    pause(0),
    singleStep(0),
    worldExtents()
    {}

    float32 hz;
    int32 velocityIterations;
    int32 positionIterations;
    int32 drawStats;
    int32 drawShapes;
    int32 drawJoints;
    int32 drawAABBs;
    int32 drawPairs;
    int32 drawContactPoints;
    int32 drawContactNormals;
    int32 drawContactForces;
    int32 drawFrictionForces;
    int32 drawCOMs;
    int32 enableWarmStarting;
    int32 enableContinuous;
    int32 pause;
    int32 singleStep;
    b2Vec2 worldExtents;
};

/// This is called when a joint in the world is implicitly destroyed
/// because an attached body is destroyed. This gives us a chance to
/// nullify the mouse joint.
class DestructionListener : public b2DestructionListener
{
public:
    void SayGoodbye(b2Fixture* fixture) { REF(fixture); }
    void SayGoodbye(b2Joint* joint);

    Simulation* _simulation;
};

const int32 k_maxContactPoints = 2048;

struct ContactPoint
{
    b2Fixture* fixtureA;
    b2Fixture* fixtureB;
    b2Vec2 normal;
    b2Vec2 position;
    b2PointState state;
};

class Simulation : public b2ContactListener
{
public:
    Simulation(Settings* settings, RenderCallback* render);
    virtual ~Simulation();

    void SetTextLine(int32 line) { _textLine = line; }
    //void DrawTitle(int x, int y, const char *string);
    virtual void Step();
    virtual void Keyboard(int key) { REF(key); }
    //void ShiftMouseDown(const b2Vec2& p);
    //virtual void MouseDown(const b2Vec2& p);
    //virtual void MouseUp(const b2Vec2& p);
    //void MouseMove(const b2Vec2& p);

    /// Let derived tests know that a joint was destroyed.
    virtual void JointDestroyed(b2Joint* joint) { REF(joint); }

    /// Callbacks for derived classes.
    virtual void BeginContact(b2Contact* contact) { REF(contact); }
    virtual void EndContact(b2Contact* contact) { REF(contact); }
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
    {
        REF(contact);
        REF(impulse);
    }

protected:
    friend class DestructionListener;
    friend class BoundaryListener;
    friend class ContactListener;

    b2Body* _groundBody;
    b2World* _world;
    b2AABB _worldAABB;
    ContactPoint _points[k_maxContactPoints];
    int32 _pointCount;
    DestructionListener _destructionListener;
    //DebugDraw _debugDraw;
    int32 _textLine;
    b2MouseJoint* _mouseJoint;
    b2Vec2 _mouseWorld;
    int32 _stepCount;
    Settings* _settings;

    EntityList entities;
};

#endif
