int main()
{
    int a, b, c;
#pragma scope
    c = a;
#pragma endscope
    return 0;
}