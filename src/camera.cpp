#include <iostream> // debugging

#include <chrono> // time delta

using namespace std;

class Camera
{
public:
    Camera()
    {
        position.zero();
        scale = 1.0;
        approachQuotient = 2.0;
    }

    void setPosition(Vec2 newPosition)
    {
        targetPosition.set(newPosition);
        position.set(newPosition);
    }

    Vec2 getPosition()
    {
        return position;
    }

    void setTarget(Vec2 newTargetPosition)
    {
        targetPosition = newTargetPosition;
    }

    void tick(double delta)
    {
        position.add(scaleVec2(subtractVec2(targetPosition, position), approachQuotient * delta));
    }

private:
    Vec2 position; // centre of drawn region
    Vec2 targetPosition; // position to move camera to
    double scale; // pixel length / in-game length
    double approachQuotient; // rate at which to approach the target position per second
};
