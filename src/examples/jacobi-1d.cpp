#include <cstdlib>
#include <vector>
using namespace std;
const size_t I = 10;
int main()
{
    vector<double> a(I), b(I);
#pragma scope
    /* single-step jacobi-2d demo */
    for (size_t i = 1; i < I - 1; ++i)
    {
        b[i] = 0.5 * (a[i-1] + a[i+1]);
    }
#pragma endscope
    return 0;
}