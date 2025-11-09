#include "ball_object.h"

BallObject::BallObject() : Object(), Radius(12.5f) { }
BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite)
    : Object(pos, glm::vec2(radius*2, radius*2), sprite, glm::vec3(1.0f), velocity) { }
// moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position

glm::vec2 BallObject::Move(float dt, unsigned int window_width, unsigned int window_height){
    this->Position += this->Velocity *dt;
    // then check if outside window bounds and if so, reverse velocity and restore at correct position
    if (this->Position.x <= 0.0f)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = 0.0f;
        }
        else if (this->Position.x + this->Size.x >= window_width)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = window_width - this->Size.x;
        }
        if (this->Position.y <= 0.0f)
        {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 0.0f;
        }
        else if (this->Position.y + this->Size.y >= window_height)
        {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = window_height - this->Size.y;
        }
    return this->Position;
}

// resets the ball to initial Stuck Position (if ball is outside window bounds)
void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
    this->Sticky = false;
    this->PassThrough = false;

}