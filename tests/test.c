int add(int x, int y)
{
    if (x == 0)
        return y;
    else
        return add(x - 1, y + 1);
}
