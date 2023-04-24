struct Vec2
{
    double x = 0.0;
    double y = 0.0;

    Vec2()
    {
    }

    Vec2(double initialX, double initialY)
        : x(initialX), y(initialY)
    {
    }

    void zero()
    {
        x = 0.0;
        y = 0.0;
    }

    void set(Vec2 other)
    {
        x = other.x;
        y = other.y;
    }

    void add(Vec2 other)
    {
        x += other.x;
        y += other.y;
    }

    void scale(double scalar)
    {
        x *= scalar;
        y *= scalar;
    }

    double magnitude()
    {
        return sqrt(x * x + y * y);
    }
};

Vec2 addVec2(Vec2 first, Vec2 second)
{
    Vec2 returnVector;

    returnVector.x = first.x + second.x;
    returnVector.y = first.y + second.y;

    return returnVector;
}

Vec2 subtractVec2(Vec2 first, Vec2 second)
{
    Vec2 returnVector;

    returnVector.x = first.x - second.x;
    returnVector.y = first.y - second.y;

    return returnVector;
}

Vec2 scaleVec2(Vec2 vector, double scalar)
{
    Vec2 returnVector;

    returnVector.x = vector.x * scalar;
    returnVector.y = vector.y * scalar;

    return returnVector;
}
