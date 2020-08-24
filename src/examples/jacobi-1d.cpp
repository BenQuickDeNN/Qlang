#include <cstdlib>
#include <vector>
using namespace std;
const size_t I = 10;
int main()
{
    vector<double> a(I), b(I);
    int d;
    int *p = & d;
    *p = d * *p;
#pragma scope
    /* single-step jacobi-2d demo */
    for (size_t i = 1; i < 9; ++i)
    {
        b[i] = 0.5 * (a[i-1] + a[i+1]);
    }
#pragma endscope
    return 0;
}