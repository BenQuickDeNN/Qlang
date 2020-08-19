#include <cstdlib>
using namespace std;
const size_t _size = 10;
int main()
{
    double *a, *b;
    a = (double*)malloc(_size * sizeof(double));
    b = (double*)malloc(_size * sizeof(double));
    size_t i = 1;
    while (i < _size)
    {
#pragma scope
        b[i] = 0.5*a[i-1];
        // a[i] = 0.5*b[i-1];
        ++i;
#pragma endscope
    }
    return 0;
}