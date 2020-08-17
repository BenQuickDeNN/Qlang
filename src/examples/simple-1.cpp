int main()
{
    int a, b, c;
#pragma scope
    c = a + b - a;
#pragma endscope
    return 0;
}