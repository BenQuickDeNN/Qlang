#include <cstdlib>
#include <vector>
using namespace std;
const size_t I = 10;
const size_t J = 10;
int main()
{
    vector<vector<double>> a(I, vector<double>(J)), b(I, vector<double>(J));
#pragma scope
    /* single-step jacobi-2d demo */
    for (size_t i = 1; i < I - 1; ++i)
    {
        for (size_t j = 1; j < J - 1; ++j)
        {
            b[i][j] = 0.25 * (a[i-1][j] + a[i+1][j] +
                a[i][j-1]+a[i][j+1]);
        }
    }
#pragma endscope
    return 0;
}