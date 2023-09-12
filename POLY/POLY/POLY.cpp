//#define MOD 10*1000*1000

#include <iostream>
#include <vector>

using namespace std;

int Solve(int prev, int square);
int Poly(int n, int first);

int cache[101][101];
const int MOD = 10 * 1000 * 1000;

int main()
{

    int count = 0;

    while (1)
    {
        cin >> count;
        if (count > 0 && count <= 50) break;
    }

    vector<int> testCase;

    for (int i = 0; i < count; i++)
    {
        int input;
        cin >> input;
        testCase.push_back(input);
    }

    cout << endl;

    for (int i = 0; i < count; i++)
    {
        memset(cache, -1, sizeof(cache));

        int sum = 0;
        for (int j = 1; j <= testCase[i]; j++) 
        {
            sum = (sum + Poly(testCase[i], j)) % MOD;
        }

        cout << sum << endl;
    }

}

int Solve(int prev, int square)
{
    int res = 0;

    if (square == 0) return 1;

    if (prev == 0) res = 1;
    else
        res += square + (prev - 1);

    for (int i = 1; i < square; i++)
    {
        res += Solve(square - i, i);
    }

    return res;
}

int Poly(int n, int first)
{
    if (n == first) return 1;

    int& res = cache[n][first];
    if (res != -1) return res;
    res = 0;

    for (int second = 1; second <= n - first; second++)
    {
        int add = second + first - 1;
        add *= Poly(n - first, second);
        add %= MOD;
        res += add;
        res %= MOD;
    }

    return res;
    
}
