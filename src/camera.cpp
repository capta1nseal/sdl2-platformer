class Camera
{
public:
    Camera()
    {
        position.zero();
        scale = 0.1;
        targetScale = 1.0;
        positionApproachQuotient = 5.0;
        baseScaleApproachQuotient = 2.5;
        scaleApproachQuotient = baseScaleApproachQuotient;

        zoomFactor = 5.0;
        minScale = 0.1;
        maxScale = 10.0;
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
        targetPosition.set(newPosition);
        position.set(newPosition);
    }

    void setTargetPosition(Vec2 newTargetPosition)
    {
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

    Vec2 mapCoordinate(Vec2 coordinate)
    {
        return addVec2(
            Vec2(displayWidth / 2.0, displayHeight / 2.0), // vector to centre of screen / camera, same diff innit
            scaleVec2(subtractVec2(coordinate, position), scale) // vector from centre to coordinate scaled by scale
        ); // which added together make the vector from the top-left corner to the screen-space position of the coordinate
    }

    void tick(double delta)
    {
        if (input->zoomInPressed()) zoomIn(delta);
        if (input->zoomOutPressed()) zoomOut(delta);

        position.add(scaleVec2(subtractVec2(targetPosition, position), positionApproachQuotient * delta));
        scale += (targetScale - scale) * scaleApproachQuotient * delta;
    }

private:
    int displayWidth; // width of display in pixels
    int displayHeight; // height of display in pixels
    Vec2 position; // centre of drawn region
    Vec2 targetPosition; // position to move camera to
    double scale; // pixel length / in-game length
    double targetScale; // scale to zoom to
    double baseScaleApproachQuotient; // base rate to approach target scale, modified by eg. speed of movement
    double scaleApproachQuotient; // rate at which to approach the target scale per second
    double positionApproachQuotient; // rate at which to approach the target position per second
    double zoomFactor;
    double minScale;
    double maxScale;

    Input *input; // pointer to input object

    void zoomIn(double delta)
    {
        targetScale = clamp(targetScale + zoomFactor * delta, minScale, maxScale);
    }

    void zoomOut(double delta)
    {
        targetScale = clamp(targetScale - zoomFactor * delta, minScale, maxScale);
    }
};
