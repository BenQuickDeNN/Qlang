int main()
{
    int a, b, c;
#pragma scope
    a = b + c;
#pragma endscope
    return 0;
}