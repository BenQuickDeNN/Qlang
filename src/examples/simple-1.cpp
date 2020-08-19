#include <cstdlib>
using namespace std;
const size_t _size = 10;
int main()
{
    double *a, *b;
    a = (double*)malloc(_size * sizeof(double));
    b = (double*)malloc(_size * sizeof(double));
#pragma scope
    for (size_t i = 1; ; ++i)
    {
        b[i] = 0.5 * a[i];
    }
#pragma endscope
    return 0;
}