double clamp(double n, double min, double max)
{
    if (n >= max) return max;
    if (n <= min) return min;
    return n;
}