struct Vec2
{
    double x = 0.0;
    double y = 0.0;

    void zero()
    {
        x = 0.0;
        y = 0.0;
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
};
