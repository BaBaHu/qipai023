#include "MEShake.h"

// not really useful, but I like clean default constructors
MEShake::MEShake() : _strength_x(0), _strength_y(0), _initial_x(0), _initial_y(0)
{
}

MEShake* MEShake::create(float d, float strength )
{
    // call other construction method with twice the same strength
    return create( d, strength, strength );
}

MEShake* MEShake::create(float duration, float strength_x, float strength_y)
{
    MEShake *p_action = new MEShake();
    p_action->initWithDuration(duration, strength_x, strength_y);
    p_action->autorelease();
    
    return p_action;
}

bool MEShake::initWithDuration(float duration, float strength_x, float strength_y)
{
	//CCLOG("MEShake::initWithDuration = %f,%f,%f", duration, strength_x, strength_y);
    if (CCActionInterval::initWithDuration(duration))
    {
        _strength_x = strength_x;
        _strength_y = strength_y; 
        return true;
    }
    return false;
}

// Helper function. I included it here so that you can compile the whole file
// it returns a random value between min and max included
float fgRangeRand( float min, float max )
{
     float rnd = ((float)rand()/(float)RAND_MAX);
     return rnd*(max-min)+min;
}

void MEShake::update(float time)
{
     float randx = fgRangeRand( -_strength_x, _strength_x );
     float randy = fgRangeRand( -_strength_y, _strength_y );
    
     // move the target to a shaked position
     _target->setPosition(Vec2(_initial_x + randx,_initial_y + randy));
}

MEShake* MEShake::clone(void) const
{
    auto a = new MEShake();
    a->initWithDuration(_duration, _strength_x, _strength_y);
    a->autorelease();
    return a;
}

MEShake* MEShake::reverse() const
{
    return MEShake::create(_duration, -_strength_x, -_strength_y);
}

void MEShake::startWithTarget(Node *target)
{
    CCActionInterval::startWithTarget(target);
    
    // save the initial position
    _initial_x = target->getPosition().x;
    _initial_y = target->getPosition().y;
}

void MEShake::stop(void)
{
    // Action is done, reset clip position
    _target->setPosition(Vec2( _initial_x, _initial_y ) );
    
    CCActionInterval::stop();
}