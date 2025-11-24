#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include "glad.h"
#include <glm/glm.hpp>

#include "object.h"
#include "textures.h"


// BallObject holds the state of the Ball object inheriting
// relevant state data from Object. Contains some extra
class BallObject : public Object
{
public:
    // ball state	
    float   Radius;
    bool    Stuck;
    bool    Sticky, PassThrough;
    // constructor(s)
    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);
    // moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    glm::vec2 Move(float theta0, float L, unsigned int window_width, unsigned int window_height);
    // resets the ball to original state with given position and velocity
    void      Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif