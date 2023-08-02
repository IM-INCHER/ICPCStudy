#include <iostream>
#include <string>
#include <vector>

#define MAXSIZE 16

using namespace std;

int main();

void print();
void descompress(string::iterator& it, int y, int x, int size);
string compress(int x, int y, int size);
string Reverse(string::iterator& it);

void Reverse();

static char descompressed[MAXSIZE][MAXSIZE];

int main()
{
	int count;

	//테스트 케이스 수 입력
	while (1)
	{
		cin >> count;
		if (count > 0 && count <= 50) break;
	}

	//쿼드트리 입력
	string input;
	vector<string> testCase;
	for(int i = 0; i < count; i++)
	{
		cin >> input;
		testCase.push_back(input);
	}
	
	//cout << endl;

	for (int i = 0; i < count; i++)
	{
		string::iterator it = testCase[i].begin();
	
		//쿼드트리 압축해제
		/*descompress(it, 0, 0, MAXSIZE);
		Reverse();
		cout << compress(0, 0, MAXSIZE) << endl;;*/

		//print();

		it = testCase[i].begin();

		//뒤집어서 출력
		cout << Reverse(it);
		cout << endl;

		//descompress(it, 0, 0, MAXSIZE);

		//Reverse();
		//print();
		
	}
}

string Reverse(string::iterator& it)
{
	char head = *it;
	++it;
	if (head == 'b' || head == 'w')
		return string(1, head);

	//왼쪽 위
	string upperLeft = Reverse(it);
	//오른쪽 위
	string upperRight = Reverse(it);
	//왼쪽 아래
	string lowerLeft = Reverse(it);
	//오른쪽 아래
	string lowerRight = Reverse(it);

	//위아래 순서를 바꾸어 뒤집는 효과를 줌
	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

void Reverse()
{
	char temp;

	for (int i = 0; i < MAXSIZE / 2; i++)
	{
		for (int j = 0; j < MAXSIZE; j++)
		{
			temp = descompressed[i][j];
			descompressed[i][j] = descompressed[MAXSIZE - 1 - i][j];
			descompressed[MAXSIZE - 1 - i][j] = temp;
		}
	}
}

void print()
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int j = 0; j < MAXSIZE; j++)
		{
			if (descompressed[i][j] == 'b')
				cout << "■";
			else if (descompressed[i][j] == 'w')
				cout << "□";
		}
		cout << endl;
	}
	cout << endl;
}

void descompress(string::iterator& it, int y, int x, int size)
{
	char head = *(it++);
	if (head == 'b' || head == 'w')
	{
		for (int dy = 0; dy < size; ++dy)
		{
			for (int dx = 0; dx < size; ++dx)
				descompressed[y + dy][x + dx] = head;
		}
	}
	else
	{
		int half = size / 2;
		descompress(it, y, x, half);
		descompress(it, y, x + half, half);
		descompress(it, y + half, x, half);
		descompress(it, y + half, x + half, half);
	}
}

string compress(int x, int y, int size)
{
	char first = descompressed[x][y];
	bool oneColor = true;

	for (int i = y; i < y + size; i++)
	{
		for (int j = x; j < x + size; j++)
		{
			if (first != descompressed[i][j])
			{
				oneColor = false;
			}
		}

		if (!oneColor) break;
	}
	if (oneColor) return string(1 ,first);

	int half = size / 2;
	//왼쪽 위
	string upperLeft = compress(x, y, half);
	//오른쪽 위
	string upperRight = compress(x + half, y, half);
	//왼쪽 아래
	string lowerLeft = compress(x, y + half, half);
	//오른쪽 아래
	string lowerRight = compress(x + half, y + half, half);

	return string("x") + upperLeft + upperRight + lowerLeft + lowerRight;
}

