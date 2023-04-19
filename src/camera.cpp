#include <iostream> // debugging

#include <chrono> // time delta

#include "vec2.cpp" // 2D vector values

using namespace std;

Vec2 subtractVec2(Vec2 first, Vec2 second)
{
    Vec2 returnVector;
    returnVector.x = first.x - second.x;
    returnVector.y = first.y - second.y;
    return returnVector;
}

class Camera
{
public:
    Camera()
    {
        position.zero();
        scale = 1.0;
        approachQuotient = 0.25;
    }

    void setTarget(Vec2 newTargetPosition)
    {
        targetPosition = newTargetPosition;
    }

    void tick(double delta)
    {
        position.add(subtractVec2(targetPosition, position).scale(approachQuotient * delta));
    }

private:
    Vec2 position; // centre of drawn region
    Vec2 targetPosition; // position to move camera to
    double scale; // pixel length / in-game length
    double approachQuotient; // rate at which to approach the target position
};
