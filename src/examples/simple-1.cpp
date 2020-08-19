int main()
{
    int a, b, c;
#pragma scope
    c = a + b - c / a* b;
    ++c;
#pragma endscope
    return 0;
}