int factorial_iter(int n)
{
    int k;
    int v = 1;

    for (k = n; k > 0; k--) {
        v = v * k;
    }
    return v;
}
