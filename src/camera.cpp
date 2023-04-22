class Camera
{
public:
    Camera()
    {
        position.zero();
        scale = 1.0;
        positionApproachQuotient = 3.5;
        scaleApproachQuotient = 1.0;
    }

    void initializeResolution(int initialDisplayWidth, int initialDisplayHeight)
    {
        displayWidth = initialDisplayWidth;
        displayHeight = initialDisplayHeight;
    }

    void setInput(Input *inputPtr)
    {
        input = inputPtr;
    }

    void setPosition(Vec2 newPosition)
    {
        newPosition.x -= displayWidth / 2.0;
        newPosition.y -= displayHeight / 2.0;
        targetPosition.set(newPosition);
        position.set(newPosition);
    }

    void setTargetPosition(Vec2 newTargetPosition)
    {
        newTargetPosition.x -= displayWidth / 2.0;
        newTargetPosition.y -= displayHeight / 2.0;
        targetPosition = newTargetPosition;
    }

    Vec2 getPosition()
    {
        return position;
    }

    void setScale(double newScale)
    {
        scale = newScale;
    }

    void setTargetScale(double newTargetScale)
    {
        targetScale = newTargetScale;
    }

    double getScale()
    {
        return scale;
    }

    void tick(double delta)
    {
        position.add(scaleVec2(subtractVec2(targetPosition, position), positionApproachQuotient * delta));
        scale += (targetScale - scale) * scaleApproachQuotient * delta;
    }

private:
    int displayWidth; // width of display in pixels
    int displayHeight; // height of display in pixels
    Vec2 position; // centre of drawn region
    Vec2 targetPosition; // position to move camera to
    double positionApproachQuotient; // rate at which to approach the target position per second
    double scale; // pixel length / in-game length
    double targetScale; // scale to zoom to
    double scaleApproachQuotient; // rate at which to approach the target scale per second

    Input *input; // pointer to input object
};
