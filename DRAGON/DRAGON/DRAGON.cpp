#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

void Print(const char* text ,int s, int n);
void DragonCurve(const char* text, int n);
void precalc();
char expand(const string& dragonCurve, int generatrions, int skip);

static string dragon;
const int MAX = 1000000000 + 1;
int length[51];

const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";

int main()
{
    int count = 0;

    while (1)
    {
        cin >> count;
        if (count > 0 && count <= 50) break;
    }

    vector<int*> testCase;

    for (int i = 0; i < count; i++)
    {
        int input[3];

        for (int j = 0; j < 3; j++)
        {
            cin >> input[j];
        }
        testCase.push_back(new int[3] {input[0] ,input[1] , input[2]});
    }

    //cout << endl;

    precalc();

    for (int i = 0; i < count; i++)
    {
        /*dragon = "";
        DragonCurve("FX", testCase[i][0]);
        Print(dragon, testCase[i][1], testCase[i][2]);*/
                            //l
        for (int j = 0; j < testCase[i][2]; j++)
        {                        //n             p
            cout << expand("FX", testCase[i][0], testCase[i][1] + j - 1);
        }
        cout << endl;
    }
}

void Print(const char* text, int s, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << text[s - 1 + i];
    }
    cout << endl;
}
void DragonCurve(const char* text, int n)
{
    if (n == 0)
    {
        dragon += text;
        return;
    }
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 'X')
            DragonCurve("X+YF", n - 1);
        else if (text[i] == 'Y')
            DragonCurve("FX-Y", n - 1);
        else
            dragon += text[i];
    }
}

//X와 Y를 n세대 진화시킨 만큼 치환했을때 길이를 미리 계산하여 저장하는 함수
void precalc()
{
    length[0] = 1;
    for (int i = 1; i <= 50; i++)
        length[i] = min(MAX, length[i - 1] * 2 + 2);
}

char expand(const string& dragonCurve, int generatrions, int skip)
{
    if (generatrions == 0)
    {
        assert(skip < dragonCurve.size());
        return dragonCurve[skip];
    }
    //한글자씩 탐색해 skip을 하나씩 감소 시킨다
    for (int i = 0; i < dragonCurve.size(); i++)
    {
        //X나 Y를 만나고 
        if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y')
        {
            //skip이 총문자의 길이보다 길다면 현재 세대의 문자가 있음
            if (skip >= length[generatrions])
                skip -= length[generatrions];

            //그렇지 않으면 다음 세대에 있으므로 재귀 호출
            else if (dragonCurve[i] == 'X')
                return expand(EXPAND_X, generatrions - 1, skip);
            else if (dragonCurve[i] == 'Y')
                return expand(EXPAND_Y, generatrions - 1, skip);
        }
        else if (skip > 0)
            skip--;
        else
            return dragonCurve[i];
    }

    //실행된다면 오류가 난것
    return '#';
}

