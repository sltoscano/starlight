
#include "simulation.h"


void DestructionListener::SayGoodbye(b2Joint* joint)
{
    if (_simulation->_mouseJoint == joint)
    {
        _simulation->_mouseJoint = NULL;
    }
    else
    {
        _simulation->JointDestroyed(joint);
    }
}

Simulation::Simulation(Settings* settings)
{
    _settings = settings;

    b2Vec2 gravity;
    gravity.Set(0.0f, 0.0f);
    bool doSleep = true;
    _world = new b2World(gravity, doSleep);

    _textLine = 30;
    _mouseJoint = NULL;
    _pointCount = 0;

    _destructionListener._simulation = this;
    _world->SetDestructionListener(&_destructionListener);
    _world->SetContactListener(this);
    // TODO: Use different drawing func
    //_world->SetDebugDraw(&_debugDraw);

    _stepCount = 0;

    b2BodyDef bodyDef;
    bodyDef.position.Set(0, 0); // bottom-left corner
    _groundBody = _world->CreateBody(&bodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    float32 x = _settings->worldExtents.x;
    float32 y = _settings->worldExtents.y;

    // bottom
    groundBox.SetAsEdge(b2Vec2(0,0), b2Vec2(x,0));
    _groundBody->CreateFixture(&groundBox,0);

    // top
    groundBox.SetAsEdge(b2Vec2(0,y), b2Vec2(x,y));
    _groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.SetAsEdge(b2Vec2(0,y), b2Vec2(0,0));
    _groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.SetAsEdge(b2Vec2(x,y), b2Vec2(x,0));
    _groundBody->CreateFixture(&groundBox,0);
}

Simulation::~Simulation()
{
    /// By deleting the world, we delete the bomb, mouse joint, etc.
    delete _world;
    _world = NULL;
}

void Simulation::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    const b2Manifold* manifold = contact->GetManifold();

    if (manifold->pointCount == 0)
    {
        return;
    }

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
    b2GetPointStates(state1, state2, oldManifold, manifold);

    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);

    for (int32 i = 0; i < manifold->pointCount && _pointCount < k_maxContactPoints; ++i)
    {
        ContactPoint* cp = _points + _pointCount;
        cp->fixtureA = fixtureA;
        cp->fixtureB = fixtureB;
        cp->position = worldManifold.points[i];
        cp->normal = worldManifold.normal;
        cp->state = state2[i];
        ++_pointCount;
    }
}

class QueryCallback : public b2QueryCallback
{
public:
    QueryCallback(const b2Vec2& point)
    {
        _point = point;
        _fixture = NULL;
    }

    bool ReportFixture(b2Fixture* fixture)
    {
        b2Body* body = fixture->GetBody();
        if (body->GetType() == b2_dynamicBody)
        {
            bool inside = fixture->TestPoint(_point);
            if (inside)
            {
                _fixture = fixture;

                // We are done, terminate the query.
                return false;
            }
        }

        // Continue the query.
        return true;
    }

    b2Vec2 _point;
    b2Fixture* _fixture;
};

void Simulation::Step()
{
    float32 timeStep = _settings->hz > 0.0f ? 1.0f / _settings->hz : float32(0.0f);

    if (_settings->pause)
    {
        if (_settings->singleStep)
        {
            _settings->singleStep = 0;
        }
        else
        {
            timeStep = 0.0f;
        }

        //_debugDraw.DrawString(5, _textLine, "****PAUSED****");
        _textLine += 15;
    }

    /*
    uint32 flags = 0;
    flags += _settings->drawShapes  * b2DebugDraw::e_shapeBit;
    flags += _settings->drawJoints  * b2DebugDraw::e_jointBit;
    flags += _settings->drawAABBs   * b2DebugDraw::e_aabbBit;
    flags += _settings->drawPairs   * b2DebugDraw::e_pairBit;
    flags += _settings->drawCOMs    * b2DebugDraw::e_centerOfMassBit;
    _debugDraw.SetFlags(flags);
    */

    _world->SetWarmStarting(_settings->enableWarmStarting > 0);
    _world->SetContinuousPhysics(_settings->enableContinuous > 0);

    _pointCount = 0;

    _world->Step(timeStep, _settings->velocityIterations, _settings->positionIterations);

    // TODO: Instead of this
    // _world->DrawDebugData();
    // Do this
    // Walk vector of entities
    // for each entity
    //   entity->step()
    //   entity->drawcallback()

    if (timeStep > 0.0f)
    {
        ++_stepCount;
    }

    if (_settings->drawStats)
    {
        /*
        _debugDraw.DrawString(5, _textLine, "bodies/contacts/joints/proxies = %d/%d/%d",
                               _world->GetBodyCount(), _world->GetContactCount(), _world->GetJointCount(), _world->GetProxyCount());
        _textLine += 15;
        */
    }
}
