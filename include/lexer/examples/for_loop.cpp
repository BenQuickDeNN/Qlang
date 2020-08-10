#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;
const size_t LEN = 10;
vector<int> a;
vector<int> b;
int main()
{
    a.resize(LEN); b.resize(LEN);
#pragma omp parallel
    for (int i = 1; i < LEN - 1; i++)
    {
        b[i] = 0.5 * (a[i - 1] + a[i + 1]);
        cout << b[i] << endl;
    }
    return 0;
}