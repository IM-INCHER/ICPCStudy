
#include <iostream>
#include <vector>

using namespace std;

int FanceCut(const vector<int>& h);
int solve(int left, int right, const vector<int>& h);

int main()
{
    int count = 0;

    while (1)
    {
        cin >> count;
        if (count > 0 && count <= 50) break;
    }

    vector<int> testCase;
    vector<vector<int>> wood;

    for (int i = 0; i < count; i++)
    {
        int input;
        cin >> input;
        testCase.push_back(input);

        vector<int> woods;

        for (int j = 0; j < testCase[i]; j++)
        {
            cin >> input;
            
            woods.push_back(input);
        }

        wood.push_back(woods);
    }

    for (int i = 0; i < count; i++)
    {
        //cout << FanceCut(wood[i]) << endl;
        cout << solve(0, testCase[i] - 1, wood[i]) << endl;
    }

}

int FanceCut(const vector<int>& woods)
{
    int ret = 0;
    int count = woods.size();

    for (int left = 0; left < count; ++left)
    {
        int minHeight = woods[left];
        for (int right = left; right < count; ++right)
        {
            minHeight = min(minHeight, woods[right]);
            ret = max(ret, (right - left + 1) * minHeight);
        }
    }

    return ret;
}

int solve(int left, int right, const vector<int>& h)
{
    if (left == right) return h[left]; 

    int mid = (left + right) / 2;
    int ret = max(solve(left, mid, h), solve(mid + 1, right, h));

    int lo = mid, hi = mid + 1;
    int height = min(h[lo], h[hi]);
    ret = max(ret, height * 2);
    while (left < lo || hi < right)
    {
        if (hi < right && (lo == left || h[lo - 1] < h[hi + 1]))
        {
            ++hi;
            height = min(height, h[hi]);
        }
        else
        {
            --lo;
            height = min(height, h[lo]);
        }

        ret = max(ret, height * (hi - lo + 1));
    }

    return ret;
}