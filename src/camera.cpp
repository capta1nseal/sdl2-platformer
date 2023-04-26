class Camera
{
public:
    Camera()
    {
        scale = 0.1;
        targetScale = 1.0;
        positionApproachQuotient = 5.0;
        scaleApproachQuotient = 2.5;

        zoomFactor = 2.5;
        minScale = 0.1;
        maxScale = 10.0;
    }

    void initializeResolution(int initialDisplayWidth, int initialDisplayHeight)
    {
        displayWidth = initialDisplayWidth;
        displayHeight = initialDisplayHeight;
        centreVector = Vec2(static_cast<double>(displayWidth) / 2.0, static_cast<double>(displayHeight) / 2.0);
    }

    void setInput(Input *inputPtr)
    {
        input = inputPtr;
    }

    void setPosition(Vec2 newPosition)
    {
        targetPosition.set(&newPosition);
        position.set(&newPosition);
    }

    void setTargetPosition(Vec2 newTargetPosition)
    {
        targetPosition.set(&newTargetPosition);
    }

    Vec2 *getPosition()
    {
        return &position;
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
            &centreVector,
            scaleVec2(subtractVec2(&coordinate, &position), scale)
        );
    }
    Vec2 mapCoordinate(Vec2 *coordinate)
    {
        return addVec2(
            &centreVector,
            scaleVec2(subtractVec2(coordinate, &position), scale)
        );
    }

    void tick(double delta)
    {
        if (input->zoomInPressed())
            zoomIn(delta);
        if (input->zoomOutPressed())
            zoomOut(delta);

        position.add(scaleVec2(subtractVec2(targetPosition, position), positionApproachQuotient * delta));
        scale += (targetScale - scale) * scaleApproachQuotient * delta;
    }

private:
    int displayWidth;                // width of display in pixels
    int displayHeight;               // height of display in pixels
    Vec2 centreVector;               // vector from top left to centre of screen
    Vec2 position;                   // centre of drawn region
    Vec2 targetPosition;             // position to move camera to
    double scale;                    // screenspace length / ingame length
    double targetScale;              // scale to zoom to
    double scaleApproachQuotient;    // rate at which to approach the target scale per second
    double positionApproachQuotient; // rate at which to approach the target position per second
    double velocityZoomOut;          // amount velocity makes the camera zoom out
    double zoomFactor;               // rate at which zoom keys zoom
    double minScale;                 // minimum scale that can be zoomed out to
    double maxScale;                 // maximum scale that can be zoomed in to

    Input *input; // pointer to input object

    void zoomIn(double delta)
    {
        targetScale = clamp(targetScale * (1 + (zoomFactor - 1) * delta), minScale, maxScale);
    }

    void zoomOut(double delta)
    {
        targetScale = clamp(targetScale / (1 + (zoomFactor - 1) * delta), minScale, maxScale);
    }
};
