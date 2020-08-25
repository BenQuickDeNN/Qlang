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
    const size_t Istart = 1;
    const size_t Iend = I - 1;
    const size_t len = 1;
#pragma scope
    /* single-step jacobi-2d demo */
    for (size_t i = Istart; i < Iend; i+=len)
    {
        b[i] = 0.5 * (a[i-1] + a[i+1]);
    }
#pragma endscope
    return 0;
}