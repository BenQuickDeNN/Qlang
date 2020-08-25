#include <cstdlib>
#include <vector>
using namespace std;
const size_t I = 10;
const size_t J = 10;
int main()
{
    vector<vector<double>> a(I, vector<double>(J)), b(I, vector<double>(J));
    const size_t _I = I - 1;
    const size_t _J = J - 1;
#pragma scope
    /* single-step jacobi-2d demo */
    for (size_t i = 1; i < _I; ++i)
    {
        for (size_t j = 1; j < _J; ++j)
        {
            b[i][j] = 0.25 * (a[i-1][j] + a[i+1][j] +
                a[i][j-1]+a[i][j+1]);
        }
    }
#pragma endscope
    return 0;
}